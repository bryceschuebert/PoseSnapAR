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

#include "ModelImporter.h"

#include <cadex/LicenseManager_Activate.h>
#include <cadex/Base_UTF16String.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_ModelReader.hxx>
#include <cadex/Unigine_NodeFactory.hxx>
#include <cadex/Unigine_NodeFactoryParameters.hxx>

#include <UnigineImport.h>
#include <UnigineFileSystem.h>

#include <../../cadex_license.cxx>

using namespace Unigine;
using namespace cadex;

NodeReferencePtr ModelImporter::ImportViaPlugin (const String theFilePath)
{    
    // String to store the path to the resulting .node file with our imported scene
    String aFilePathNode;

    String aFilePath = FileSystem::getAbsolutePath (theFilePath);
    Importer* anImporter = Import::get()->createImporterByFileName (aFilePath);

    if (anImporter) {

        // Example of using parameters
        anImporter->setParameterDouble ("scale_factor", 1.0);

        anImporter->init(aFilePath.get(), ~0);

        String aFileName = aFilePath.filename();
        String anOutputFolder = String::format ("../data/%s/", aFileName.get());
        anImporter->import (anOutputFolder);

        aFilePathNode = anImporter->getOutputFilepath();
    } else {
        Log::error ("Importer not found\n");
        return nullptr;
    }

    if (aFilePathNode.empty()) {
        Log::error ("Scene import failure\n");
        return nullptr;
    }

    return NodeReference::create (aFilePathNode);;
}

NodeReferencePtr ModelImporter::ImportViaSDK (const String theFilePath)
{
    String aFilePath = FileSystem::getAbsolutePath (theFilePath);

    // Reading file to CAD Exchanger data model
    cadex::ModelData_Model aModel;
    cadex::ModelData_ModelReader aReader;
    if (!aReader.Read (cadex::Base_UTF16String (aFilePath.getRaw()), aModel)) {
        Log::error ("Failed to read the file %s\n", aFilePath.getRaw());
        return nullptr;
    }

    // Specifying output folder
    String aFileName = theFilePath.filename();
    Base_UTF16String anOutputFolder (String::format ("../data/%s/", aFileName.get()).get());

    Unigine_NodeFactory aFactory;

    // Example of using parameters
    Unigine_NodeFactoryParameters aParam;
    aParam.SetScaleFactor (1.0);
    aFactory.SetParameters (aParam);

    // Importing model
    Base_UTF16String aFilePathNode = aFactory.Create (aModel, anOutputFolder); 

    return NodeReference::create (aFilePathNode.ToUTF8().Data());;
}
