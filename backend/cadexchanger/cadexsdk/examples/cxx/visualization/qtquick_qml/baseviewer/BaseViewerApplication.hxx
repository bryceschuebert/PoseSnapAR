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


#ifndef BaseViewerApplication_HeaderFile
#define BaseViewerApplication_HeaderFile

#include <cadex/Base_ReaderParameters.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelPrs_Scene.hxx>
#include <cadex/ModelPrs_SceneNode.hxx>
#include <cadex/ModelPrs_SceneNodeFactoryParameters.hxx>

#include <QtCore/QObject>

class QQuickWindow;
class QQmlEngine;
class QVariant;

namespace cadex {
class ModelPrsQtQuick_ViewPort;
}

class BaseViewerApplication : public QObject
{
    Q_OBJECT

public:
    BaseViewerApplication();

    bool Initialize (const QUrl& theUrl, const QString& theViewPortName);

    bool event (QEvent* theEvent) override;

    virtual void CreateSceneNodes();

signals:
    void initialized();

protected slots:
    void onImportFile (const QVariant& theUrl);

protected:
    void Import (const QString& theFilename);

    virtual void Clear();

    void ShowMessageBox (const QString& theMessage);

private:
    QQuickWindow* CreateMainWindow (const QUrl& theUrl);

    void onImportCompleted (QEvent* theEvent);

protected:
    cadex::ModelData_Model                      myModel;
    cadex::ModelPrs_Scene                       myScene;
    cadex::ModelPrs_SceneNode                   myRoot;
    cadex::Base_ReaderParameters                myReaderParameters;

    QQuickWindow*                       myMainWindow = nullptr;
    cadex::ModelPrsQtQuick_ViewPort*    myViewPort = nullptr;
};

#endif // BaseViewerApplication_HeaderFile
