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
#include <cadex/ModelData_Body.hxx>
#include <cadex/ModelData_BodyList.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_ModelReader.hxx>
#include <cadex/ModelData_ModelWriter.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelSimplifier_Simplifier.hxx>
#include <cadex/ModelSimplifier_SimplifierBuilder.hxx>

#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

class FaceCounter : public ModelData_Model::VoidElementVisitor
{
public:
    void operator() (const ModelData_Part& thePart) override
    {
        auto aBRep = thePart.BRepRepresentation();
        const ModelData_BodyList& aBodyList = aBRep.Get();
        for (ModelData_BodyList::SizeType i = 0; i < aBodyList.Size(); ++i) {
            const ModelData_Body& aBody = aBodyList[i];
            ModelData_Shape::Iterator aFaceIt (aBody, ModelData_ST_Face);
            while (aFaceIt.HasNext()) {
                aFaceIt.Next();
                ++myNumberOfFaces;
            }
        }
    }

    size_t NumberOfFaces () const
    {
        return myNumberOfFaces;
    }

private:
    size_t myNumberOfFaces = 0;
};

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>, where:"   << endl;
        cerr << "    <input_file>  is a name of the ASIC file to be read"       << endl;
        cerr << "    <output_file>  is a name of the XML file to be saved"      << endl;
        return 1;
    }

    const char* aSource = argv[1];
    const char* aDest   = argv[2];

    ModelData_Model aModel;

    ModelData_ModelReader aReader;
    // Opening and converting the file
    if (!aReader.Read (aSource, aModel)) {
        cerr << "Failed to open and convert the file " << aSource << endl;
        return 1;
    }

    // Basic info about model
    FaceCounter aBeforeCounter;
    aModel.Accept (aBeforeCounter);
    cout << "Model name: "  << aModel.Name() << endl;
    cout << "# of faces before: "  << aBeforeCounter.NumberOfFaces() << endl;

    // Running the simplifier
    ModelSimplifier_SimplifierBuilder aBuilder;
    aBuilder.SetLevel (ModelSimplifier_SimplifierBuilder::High);
    aBuilder.SetFeatureSize (ModelSimplifier_SimplifierBuilder::Large);
    ModelSimplifier_Simplifier aSimplifier = aBuilder.CreatePipeline();

    ModelData_Model aNewModel = aSimplifier.Perform (aModel);

    // How many shapes does simplified model contain?
    FaceCounter anAfterCounter;
    aNewModel.Accept (anAfterCounter);
    cout << "# of faces after: " << anAfterCounter.NumberOfFaces() << endl;

    // Saving the simplified model
    if (!ModelData_ModelWriter().Write (aNewModel, aDest)) {
        cerr << "Failed to write the file " << aDest << endl;
        return 1;
    }

    return 0;
}
