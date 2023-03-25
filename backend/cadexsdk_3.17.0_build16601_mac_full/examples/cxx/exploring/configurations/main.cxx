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


#include <cadex/LicenseManager_Activate.h>
#define __CADEX_PREVIEW_CONFIGURATIONS 1
#include <cadex/ModelData_ConfigurationManager.hxx>
#include <cadex/ModelData_ModelReader.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>
#include <cadex/SLD_ReaderParameters.hxx>
#include <iostream>

#include "../../cadex_license.cxx"

using namespace std;
using namespace cadex;

// Visits directly each part and calls configuration exploring if a part has one
class PartConfigurationVisitor : public ModelData_Model::VoidElementVisitor
{
protected:

    void operator() (const ModelData_Part& thePart) override
    {
        const ModelData_ConfigurationManager& aManager = thePart.Configurations();
        if (aManager) {
            ExploreConfigurations (aManager);
        }
    }

private:

    void ExploreConfigurations (const ModelData_ConfigurationManager& theManager)
    {
        cout << "Number of part configurations: " << theManager.NumberOfConfigurations() << endl;

        ModelData_ConfigurationManager::ConfigurationIterator anIterator (theManager);
        while (anIterator.HasNext()) {
            const ModelData_SceneGraphElement& anElement = anIterator.Next();
            cout << "Part configuration name: " << theManager.ConfigurationName (anElement) << endl;
        }
    }
};

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    // Get the input
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>, where:" << endl;
        cerr << "    <input_file> is a name of the SLD file to be read" << endl;
        return 1;
    }

    const char* aSource = argv[1];

    // Open the model
    ModelData_Model aModel;

    //Read all configurations
    SLD_ReaderParameters aParameters;
    aParameters.ConfigurationsMode() = SLD_ReaderParameters::All;

    ModelData_ModelReader aReader;
    aReader.SetReaderParameters (aParameters);
    if (!aReader.Read (aSource, aModel)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    PartConfigurationVisitor aVisitor;
    aModel.Accept (aVisitor);

    return 0;
}
