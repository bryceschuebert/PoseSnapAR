// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2023, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// You may use this file under the terms of the BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ****************************************************************************


#include "BaseViewerApplication.hxx"
#include "ImportRunnable.hxx"
#include "CustomEvents.hxx"

#include <cadex/ModelData_RepresentationSelector.hxx>
#include <cadex/ModelPrs_Scene.hxx>
#include <cadex/ModelPrs_SceneNodeFactory.hxx>
#include <cadex/ModelPrsQtQuick_ViewPort.hxx>
#include <cadex/STEP_ReaderParameters.hxx>

#include <QtCore/QFileInfo>
#include <QtCore/QThreadPool>
#include <QtGui/QOpenGLContext>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

using namespace cadex;

#if __ANDROID__
#include <QtAndroidExtras/QtAndroid>
#endif

#if __ANDROID__ && __ANDROID_DEBUG
#include <android/log.h>

namespace {
//! Redirects qDebug(), qWarning(), qCritical(), qFatal(), qInfo() to android log.
void QMessageToAndroidLogRedirector (QtMsgType theType, const QMessageLogContext& /*theContext*/, const QString& theMsg)
{
    QString aText;
    switch (theType) {
    case QtDebugMsg:    aText += "qDebug(): "; break;
    case QtWarningMsg:  aText += "qWarning(): "; break;
    case QtCriticalMsg: aText += "qCritical(): "; break;
    case QtFatalMsg:    aText += "qFatal(): "; break;
    case QtInfoMsg:     aText += "qInfo(): "; break;
    default: break;
    }
    aText += theMsg;
    for (const QString& line : aText.split ('\n')) {
        __android_log_print (ANDROID_LOG_DEBUG, "baseviewer", "%s", qPrintable (line));
    }
}
}
#endif

BaseViewerApplication::BaseViewerApplication()
    : myRoot (ModelPrs_SceneNode::initialized()), myReaderParameters (STEP_ReaderParameters())
{
    myScene.AddRoot (myRoot);

    qApp->setOrganizationName ("CAD Exchanger");
    qApp->setOrganizationDomain ("cadexchanger.com");
}

namespace {
//! Returns detected OpenGl version.
#if !__ANDROID__
QPair<int, int> OpenGlVersion()
{
    auto aVersion = qMakePair (-1, -1);

    QOpenGLContext aTestOpenGLContext;
    aTestOpenGLContext.create();

    if (aTestOpenGLContext.isValid()) {
        aVersion = aTestOpenGLContext.format().version();
    }
    return aVersion;
}
#endif
} // end of unnamed namespace

//! Initializes the main window and attaches View Port to Scene.
bool BaseViewerApplication::Initialize (const QUrl& theUrl, const QString& theViewPortName)
{
#if __ANDROID__ && __ANDROID_DEBUG
    // Register custom message handler.
    qInstallMessageHandler (QMessageToAndroidLogRedirector);
#endif

#if !__ANDROID__
    auto anOpenGlVersion        = OpenGlVersion();
    auto aRequiredOpenGlVersion = qMakePair (2, 1);

    // Check OpenGl version.
    if (anOpenGlVersion < aRequiredOpenGlVersion) {
        QMessageBox::critical (nullptr,
                               QCoreApplication::applicationName(),
                               tr ("%1 requires graphic card with drivers supporting OpenGL %2.%3 or later.\n"
                                   "Detected driver supports OpenGL %4.%5.\n"
                                   "Please make sure you don't run %1 inside virtual machine "
                                   "and your graphic card driver is upgraded to the latest version "
                                   "Visit your graphic card manufacturer web-site to download the latest drivers.")
                               .arg (QCoreApplication::applicationName())
                               .arg (aRequiredOpenGlVersion.first).arg (aRequiredOpenGlVersion.second)
                               .arg (anOpenGlVersion.first).arg (anOpenGlVersion.second)
                               );
        return false;
    }
#endif

    // Register types for qml.
    ModelPrsQtQuick_ViewPort::RegisterQtTypes();

    myMainWindow = CreateMainWindow (theUrl);

    Q_ASSERT (myMainWindow);

#if __ANDROID__
    // Request read permission on Android.
    if (!QtAndroid::shouldShowRequestPermissionRationale("android.permission.READ_EXTERNAL_STORAGE")) {
        QtAndroid::requestPermissions({{ "android.permission.READ_EXTERNAL_STORAGE" }},
        [] (const QtAndroid::PermissionResultMap & theResult) {
            if (theResult["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied) {
                qWarning ("User refused request to allow access to sdcard for reading.");
            }
        });
    }
#endif

    // Connect slot to signal about clicked "Import" button.
    connect (myMainWindow, SIGNAL (importFile (const QVariant&)),
             this,         SLOT (onImportFile (const QVariant&)));

    // Search ModelPrsQtQuick_ViewPort among window's qt objects and attach View Port to Scene.
    myViewPort = myMainWindow->findChild<ModelPrsQtQuick_ViewPort*> (theViewPortName);
    Q_ASSERT (myViewPort);
    auto aRes = myViewPort->AttachToScene (myScene);

    myMainWindow->showNormal();

    myMainWindow->setProperty ("fileDialogNameFilters", "STEP files (*.stp *.step)");

    emit initialized();

    // Import model from the program arguments (when was specified).
    auto anArguments = QApplication::instance()->arguments();
    if (anArguments.size() > 1) {
        auto anArgument = anArguments.at (1);
        Import (anArgument);
    }

    return aRes;
}

//! Creates Qml Engine and create application window from qml.
QQuickWindow* BaseViewerApplication::CreateMainWindow (const QUrl& theUrl)
{
    auto anEngine = new QQmlApplicationEngine (this);

    QQmlComponent aComponent (anEngine);
    aComponent.loadUrl (theUrl);

    QObject* aQmlApp = nullptr;

    if (!aComponent.isReady()) {
        // For easy debugging redirect it to output.
        qDebug() << aComponent.errorString();
        QCoreApplication::postEvent (QCoreApplication::instance(), new QEvent (QEvent::Quit));
        return nullptr;
    }

    aQmlApp = aComponent.create();
    aQmlApp->setParent (this);
    return qobject_cast<QQuickWindow*> (aQmlApp);
}

//! Checks variant argument and calls Import for given file path.
void BaseViewerApplication::onImportFile (const QVariant& theUrl)
{
    if (!(theUrl.isValid() || !theUrl.canConvert<QUrl>())) {
        qWarning() << "BaseViewerApplication::OnImport: Invalid argument [" << theUrl << "]";
        return;
    }

    auto aFilename = theUrl.toUrl().toLocalFile();
    Import (aFilename);
}

//! Checks if file exists and creates ImportRunnable task to Read and Import this file.
void BaseViewerApplication::Import (const QString& theFilename)
{
    QFileInfo aFileInfo (theFilename);
    if (!aFileInfo.exists() || !aFileInfo.isFile() || !aFileInfo.isReadable()) {
        return;
    }

    Clear();

    auto aRunnable = new ImportRunnable (theFilename, myScene, myModel, myReaderParameters, this);
    QThreadPool::globalInstance()->start (aRunnable);

    myMainWindow->setProperty ("loading", true);
    myMainWindow->setTitle (QString ("CAD Exchanger [%1]").arg (theFilename));
}

//! Clears Scene and Model (before new import).
void BaseViewerApplication::Clear()
{
    myModel.Clear();
    myRoot.RemoveChildrenNodes();
    myScene.Update();
}

//! Creates Scene Nodes using Factory.
void BaseViewerApplication::CreateSceneNodes()
{
    ModelPrs_SceneNodeFactory aFactory;
    auto aRoot = aFactory.CreateGraph (myModel, ModelData_RM_BRep);
    myRoot.AddChildNode (aRoot);
}

//! Process custom events and proxy the rest to the base class.
bool BaseViewerApplication::event (QEvent* theEvent)
{
    auto anEventType = static_cast<ImportResult> (theEvent->type());

    if (ImportResult::Error != anEventType && anEventType != ImportResult::Success) {
        return QObject::event (theEvent);
    }

    onImportCompleted (theEvent);
    return true;
}

//! Process custom events from ImportRunnable task.
//! Shows message box if the import is failed, otherwise do "fit all" when the import successfully ended.
void BaseViewerApplication::onImportCompleted (QEvent* theEvent)
{
    auto anEventType = static_cast<ImportResult> (theEvent->type());

    switch (anEventType) {
    case ImportResult::Success: {
        myMainWindow->setProperty ("loading", false);
        myViewPort->animatedFitAll();
        break;
    }
    case ImportResult::Error: {
        Q_ASSERT (dynamic_cast<ErrorEvent*> (theEvent));
        auto anEvent = static_cast<ErrorEvent*> (theEvent);

        myMainWindow->setProperty ("loading", false);
        ShowMessageBox (anEvent->Message());
        break;
    }
    }
}

//! Shows message box (see Dialog from BaseWindow.qml)
void BaseViewerApplication::ShowMessageBox (const QString& theMessage)
{
    if (auto aDialog = myMainWindow->findChild<QObject*> ("dialog")) {
        aDialog->setProperty ("message", theMessage);
        QMetaObject::invokeMethod (aDialog, "open");
    }
}


