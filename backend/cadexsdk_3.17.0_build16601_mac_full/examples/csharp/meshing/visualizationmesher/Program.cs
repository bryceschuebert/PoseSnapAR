﻿// ****************************************************************************
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


using cadex;
using System;
using System.Runtime.InteropServices;

namespace visualizationmesher
{
    class FirstFaceGetter : ModelData_Model.VoidElementVisitor
    {

        public override void Apply(ModelData_Part thePart)
        {
            if (myFace == null) {
                ExploreBRep(thePart.BRepRepresentation());
            }
        }
        
        public ModelData_Face FirstFace()
        {
            return myFace;
        }
        
        private void ExploreBRep(ModelData_BRepRepresentation theBRep)
        {
            ModelData_BodyList aBodyList = theBRep.Get();
            ModelData_Body aFirstBody = aBodyList.First();

            ModelData_Shape.Iterator aFaceIt = 
                new ModelData_Shape.Iterator(aFirstBody, ModelData_ShapeType.ModelData_ST_Face);
            ModelData_Shape aFirstShape = aFaceIt.Next();
            ModelData_Face aFirstFace = ModelData_Face.Cast(aFirstShape);
            myFace = aFirstFace;
        }

        private ModelData_Face myFace = null;
    };

    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        static void PrintFaceToPolyAssociation(ModelData_Face theFace, ModelData_BRepToPolyAssociations theAssociations)
        {
            ModelData_MeshPatch aMeshPatch = theAssociations.Get(theFace);
            ModelData_IndexedTriangleSet anITS = ModelData_IndexedTriangleSet.Cast(aMeshPatch.PVS());
            ModelData_IndexArray aTriangleIndices = aMeshPatch.Indices();

            Console.WriteLine("Face triangulation contains {0} triangles", aTriangleIndices.Size());

            uint aNumberOfTrianglesToPrint = Math.Min(4, aTriangleIndices.Size());

            for (uint i = 0; i < aNumberOfTrianglesToPrint; ++i) {
                int aTriangleIndex = aTriangleIndices.Element(i);
                Console.WriteLine("Triangle index {0} with vertices: ", aTriangleIndex);
                for (int aVertexNumber = 0; aVertexNumber < 3; ++aVertexNumber) {
                    int aVertexIndex = anITS.CoordinateIndex(aTriangleIndex, aVertexNumber);
                    ModelData_Point aPoint = anITS.Coordinate(aVertexIndex);
                    Console.WriteLine("  Vertex index {0} with coords (X: {1}, Y: {2}, Z: {3})", aVertexIndex,
                        aPoint.X(), aPoint.Y(), aPoint.Z());
                }
            }
        }

        static int Main(string[] args)
        {
            // Add runtime path to CAD Exchanger libraries (e.g. compiled with Visual Studio 2015)
            SetDllDirectory("../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                Console.WriteLine("Failed to activate CAD Exchanger license.");
                return 1;
            }

            if (args.Length != 1)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the XML file to be read");
                return 1;
            }

            string aSource = args[0];

            ModelData_Model aModel = new ModelData_Model();
            ModelData_ModelReader aReader = new ModelData_ModelReader();
            if (!aReader.Read(new Base_UTF16String(aSource), aModel))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            // Set up mesher and parameters
            ModelAlgo_BRepMesherParameters aParam = new ModelAlgo_BRepMesherParameters();
            aParam.SetAngularDeflection(Math.PI * 10 / 180);
            aParam.SetChordalDeflection(0.003);
            aParam.SetSaveBRepToPolyAssociations(true);

            ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher(aParam);
            aMesher.Compute(aModel, true);

            // Example of using B-Rep to Poly representation associations:
            FirstFaceGetter aVisitor = new FirstFaceGetter();
            aModel.Accept(aVisitor);

            ModelData_Face aFace = aVisitor.FirstFace();
            ModelData_BRepToPolyAssociations aBRepToPolyAssociations = aMesher.BRepToPolyAssociations();
            PrintFaceToPolyAssociation(aFace, aBRepToPolyAssociations);
            
            // Save the result
            ModelData_ModelWriter aWriter = new ModelData_ModelWriter();
            if (!aWriter.Write(aModel, new Base_UTF16String("VisMesher.xml")))
            {
                Console.WriteLine("Unable to save the model");
                return 1;
            }

            return 0;
        }
    }
}
