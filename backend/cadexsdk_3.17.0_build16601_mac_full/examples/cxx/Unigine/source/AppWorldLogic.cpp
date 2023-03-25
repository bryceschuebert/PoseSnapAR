/* Copyright (C) 2005-2022, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */
 
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


#include "AppWorldLogic.h"

#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_ModelReader.hxx>
#include <cadex/Unigine_NodeFactory.hxx>
#include <cadex/Unigine_NodeFactoryParameters.hxx>

#include <UnigineConsole.h>
#include <UnigineFileSystem.h>

#include <../../cadex_license.cxx>

using namespace Unigine;
using namespace cadex;

void AppWorldLogic::onBrowseButtonClicked()
{
    myDialogFileWidget->setFile ("");
    myDialogFileWidget->setHidden (0);
    myDialogFileWidget->setPermanentFocus();
}

void AppWorldLogic::onDialogFileOkClicked()
{
    String aPath = myDialogFileWidget->getFile();
    if (!FileSystem::isFileExist (aPath)) {
        return;
    }

    myDialogFileWidget->setHidden (1);
    myEditLineWidget->setText (aPath);
    myDialogFileWidget->removeFocus();
}

void AppWorldLogic::onDialogFileCancelClicked()
{
    myDialogFileWidget->setHidden (1);
    myDialogFileWidget->removeFocus();
}

void AppWorldLogic::onImportViaPluginButtonClicked (WidgetPtr theWidget)
{
    auto aFilePath = myEditLineWidget->getText();
    if (myImportedNode != nullptr) {
        myImportedNode->deleteLater();
    }
    myImportedNode = ModelImporter::ImportViaPlugin (aFilePath);
}

void AppWorldLogic::onImportViaSDKButtonClicked (WidgetPtr theWidget)
{
    auto aFilePath = myEditLineWidget->getText();
    if (myImportedNode != nullptr) {
        myImportedNode->deleteLater();
    }
    myImportedNode = ModelImporter::ImportViaSDK (aFilePath);
}


AppWorldLogic::AppWorldLogic()
{}

AppWorldLogic::~AppWorldLogic()
{}

int AppWorldLogic::init()
{
    // Activating CAD Exchanger license
    auto aKey = LicenseKey::Value();
    if (!CADExLicense_Activate (aKey)) {
        Console::errorLine ("Failed to activate CAD Exchanger license.");
        return 0;
    }

    myImportedNode = nullptr;

    // Setting up the GUI
    auto aGui = Gui::get();
    myUi = UserInterface::create (aGui, "ModelImporterWizard.ui");

    myUi->addCallback ("browseBtn", Gui::CLICKED, MakeCallback (this, &AppWorldLogic::onBrowseButtonClicked));

    myDialogFileWidget = WidgetDialogFile::create (aGui, "File import dialog");
    myDialogFileWidget->setPath ("./");

    myDialogFileWidget->getOkButton()->addCallback (Gui::CLICKED,
                                                    MakeCallback (this, &AppWorldLogic::onDialogFileOkClicked));
    myDialogFileWidget->getCancelButton()->addCallback (Gui::CLICKED,
                                                        MakeCallback (this, &AppWorldLogic::onDialogFileCancelClicked));

    myDialogFileWidget->setHidden (1);

    aGui->addChild (myDialogFileWidget, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

    auto aWidget = myUi->getWidget (myUi->findWidget ("filepath"));
    myEditLineWidget = static_ptr_cast<WidgetEditLine> (aWidget);

    myUi->addCallback ("importViaPluginBtn", Gui::CLICKED,
                       MakeCallback (this, &AppWorldLogic::onImportViaPluginButtonClicked));
    myUi->addCallback ("importViaSDKBtn", Gui::CLICKED,
                       MakeCallback (this, &AppWorldLogic::onImportViaSDKButtonClicked));

    auto aWindow = myUi->getWidget (myUi->findWidget ("window"));
    aGui->addChild (aWindow, Gui::ALIGN_LEFT);

    return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{
    // Write here code to be called before updating each render frame: specify all graphics-related functions you want to be called every frame while your application executes.
    return 1;
}

int AppWorldLogic::postUpdate()
{
    // The engine calls this function after updating each render frame: correct behavior after the state of the node has been updated.
    return 1;
}

int AppWorldLogic::updatePhysics()
{
    // Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
    // The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
    // WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
    return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::shutdown()
{
    // Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
    return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream)
{
    // Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
    UNIGINE_UNUSED(stream);
    return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream)
{
    // Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
    UNIGINE_UNUSED(stream);
    return 1;
}
