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


#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelData_Body.hxx>
#include <cadex/ModelData_BodyList.hxx>
#include <cadex/ModelAlgo_BRepMesher.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_BRepToPolyAssociations.hxx>
#include <cadex/ModelData_Face.hxx>
#include <cadex/ModelData_IndexArray.hxx>
#include <cadex/ModelData_IndexedTriangleSet.hxx>
#include <cadex/ModelData_MeshPatch.hxx>
#include <cadex/ModelData_ModelReader.hxx>
#include <cadex/ModelData_ModelWriter.hxx>
#include <cadex/ModelData_Part.hxx>

#include <cmath>
#include <iostream>

#include "../../cadex_license.cxx"

using namespace std;
using namespace cadex;

class FirstFaceGetter : public ModelData_Model::VoidElementVisitor
{
public:
    void operator() (const ModelData_Part& thePart) override
    {
        if (myFace.IsNull()) {
            ExploreBRep (thePart.BRepRepresentation());
        }
    }

    const ModelData_Face& FirstFace()
    {
        return myFace;
    };

private:
    void ExploreBRep (const ModelData_BRepRepresentation& theBRep)
    {
        const auto& aBodyList = theBRep.Get();
        const auto& aFirstBody = aBodyList.First();

        ModelData_Shape::Iterator aFaceIt (aFirstBody, ModelData_ST_Face);
        const auto& aFirstShape = aFaceIt.Next();
        const auto& aFirstFace = ModelData_Face::Cast (aFirstShape);
        myFace = aFirstFace;
    };

    ModelData_Face myFace;
};

void PrintFaceToPolyAssociation (const ModelData_Face&                   theFace,
                                 const ModelData_BRepToPolyAssociations& theAssociations) 
{
    ModelData_MeshPatch          aMeshPatch = theAssociations.Get (theFace);
    ModelData_IndexedTriangleSet anITS = static_cast<const ModelData_IndexedTriangleSet&> (aMeshPatch.PVS());
    ModelData_IndexArray         aTriangleIndices = aMeshPatch.Indices();

    cout << "Face triangulation contains " << aTriangleIndices.Size() << " triangles." << endl;

    const size_t aNumberOfTrianglesToPrint = std::min (size_t (4), aTriangleIndices.Size());

    for (size_t i = 0; i < aNumberOfTrianglesToPrint; ++i) {
        auto aTriangleIndex = aTriangleIndices[i];
        cout << "Triangle index " << aTriangleIndex << " with vertices: " << endl;
        for (ModelData_PolyVertexSet::IndexType aVertexNumber = 0; aVertexNumber < 3; ++aVertexNumber) {
            auto aVertexIndex = anITS.CoordinateIndex (aTriangleIndex, aVertexNumber);
            cout << "  Vertex index " << aVertexIndex << " with coords (";
            auto aPoint = anITS.Coordinate (aVertexIndex);
            cout << "X: " << aPoint.X() << ", ";
            cout << "Y: " << aPoint.Y() << ", ";
            cout << "Z: " << aPoint.Z() << ")" << endl;
        }
    }
}

int main (int argc, char* argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>, where:" << endl;
        cerr << "    <input_file> is a name of the XML file to be read" << endl;
        return 1;
    }

    const char* aSource = argv[1];

    ModelData_Model aModel;
    ModelData_ModelReader aReader;
    if (!aReader.Read (aSource, aModel)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // Set up mesher and parameters:
    ModelAlgo_BRepMesherParameters aParam;
    aParam.SetAngularDeflection (M_PI * 10 / 180);
    aParam.SetChordalDeflection (0.003);
    aParam.SetSaveBRepToPolyAssociations (true);

    ModelAlgo_BRepMesher aMesher (aParam);
    aMesher.Compute (aModel, true /*to add a polygonal representation to the model*/);

    // Example of using B-Rep to Poly representation associations:
    FirstFaceGetter aVisitor;
    aModel.Accept (aVisitor);

    ModelData_Face aFace = aVisitor.FirstFace();
    auto aBRepToPolyAssociations = aMesher.BRepToPolyAssociations();
    PrintFaceToPolyAssociation (aFace, aBRepToPolyAssociations);

    // Save the result:
    ModelData_ModelWriter aWriter;

    if (!aWriter.Write (aModel, "VisMesher.xml")) {
        cout << "Unable to save the model!" << endl;
        return 1;
    }

    return 0;
}
