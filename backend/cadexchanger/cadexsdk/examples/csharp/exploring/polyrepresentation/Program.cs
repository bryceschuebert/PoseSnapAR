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

namespace polyrepresentation
{
    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

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

            // Get the input
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the XML file to be read");
                return 1;
            }

            string aSource = args[0];

            // Open the model
            ModelData_Model aModel = new ModelData_Model();
            ModelData_ModelReader aReader = new ModelData_ModelReader();
            if (!aReader.Read(new Base_UTF16String(aSource), aModel))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            // If there is no Poly representation in the model, mesher will compute it
            ModelAlgo_BRepMesherParameters aMesherParams = new ModelAlgo_BRepMesherParameters();
            aMesherParams.SetGranularity(ModelAlgo_BRepMesherParameters.Granularity.Fine);

            ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher(aMesherParams);
            aMesher.Compute(aModel);

            // Explore Poly representation of model parts
            PartPolyVisitor aVisitor = new PartPolyVisitor();
            aModel.Accept(aVisitor);

            return 0;
        }
    }

    // Visits directly every part and calls Poly representation exploring if a part has one
    class PartPolyVisitor : ModelData_Model.VoidElementVisitor
    {
        public override void Apply(ModelData_Part thePart)
        {
            ModelData_PolyRepresentation aPolyRep = thePart.PolyRepresentation(ModelData_RepresentationMask.ModelData_RM_Poly);
            if (aPolyRep != null)
            {
                ExplorePoly(aPolyRep);
            }
        }

        // Explores PolyVertexSets of Poly representation
        private void ExplorePoly(ModelData_PolyRepresentation thePoly)
        {
            // Get() method retrieves PolyVertexSets listed in Poly representation by calling data providers flushing
            // Because of internal mechanics providers flushing is faster than for B-Rep representations
            ModelData_PolyShapeList aList = thePoly.Get();

            // Iterate over PolyShape list
            for (uint i = 0; i < aList.Size(); ++i)
            {
                ModelData_PolyVertexSet aPVS = aList.Element(i);
                Console.WriteLine("PolyShape " + i + ":");
                PrintPVSInfo(aPVS);
            }
        }

        // Function to print a PolyVertexSet info
        private void PrintPVSInfo(ModelData_PolyVertexSet thePVS)
        {
            if (thePVS.TypeId() == ModelData_IndexedTriangleSet.GetTypeId())
            {
                Console.WriteLine("IndexedTriangleSet type.");
                ModelData_IndexedTriangleSet ITS = ModelData_IndexedTriangleSet.Cast(thePVS);
                DumpTriangleSet(ITS);
            }
            else if (thePVS.TypeId() == ModelData_PolyLineSet.GetTypeId())
            {
                Console.WriteLine("PolyLineSet type.");
                ModelData_PolyLineSet PLS = ModelData_PolyLineSet.Cast(thePVS);
                DumpPolyLineSet(PLS);
            }
            else if (thePVS.TypeId() == ModelData_PolyPointSet.GetTypeId())
            {
                Console.WriteLine("PolyPointSet type.");
                ModelData_PolyPointSet PPS = ModelData_PolyPointSet.Cast(thePVS);
                DumpPolyPointSet(PPS);
            }
            else
            {
                Console.WriteLine("Undefined type");
            }
        }

        private void DumpPolyPointSet(ModelData_PolyPointSet thePS)
        {
            int n = thePS.NumberOfVertices();

            Console.WriteLine("PolyPoint set contains " + n + " vertices");
            for (int i = 0; i < n; ++i)
            {
                Console.WriteLine("Point " + i + ":");
                Console.WriteLine("  Node coordinates:");
                ModelData_Point aP = thePS.Coordinate(i);
                Console.WriteLine("  (" + aP.X() + ", " + aP.Y() + ", " + aP.Z() + ")");
            }
        }

        // Prints number of PolyLines and local coordinates for every vertex of each PolyLine
        private void DumpPolyLineSet(ModelData_PolyLineSet thePLS)
        {
            int n = thePLS.NumberOfPolyLines();

            Console.WriteLine("PolyLine set contains " + n + "PolyLines");
            for (int i = 0; i < n; ++i)
            {
                Console.WriteLine("PolyLine" + i + ":");
                Console.WriteLine("  Node coordinates:");
                for (int j = 0; j < thePLS.NumberOfVertices(i); ++j)
                {
                    ModelData_Point aV = thePLS.Coordinate(i, j);
                    Console.WriteLine("  (" + aV.X() + ", " + aV.Y() + ", " + aV.Z() + ")");
                }
            }
        }

        // Prints number of triangles and local data for each node
        // Prints Coords and UV-Coords for each vertex and prints Normals and Colors for each triangle
        private void DumpTriangleSet(ModelData_IndexedTriangleSet theTS)
        {
            int n = theTS.NumberOfFaces();

            Console.WriteLine("Triangle set contains " + n + " number of faces");
            for (int i = 0; i < n; ++i)
            {
                Console.WriteLine("Triangle " + i + ":");
                for (int j = 0; j < 3; ++j)
                {
                    Console.WriteLine("  Node " + j + ":");

                    // Coordinates
                    ModelData_Point aV = theTS.Coordinate(i, j);
                    Console.WriteLine("  Coordinates: (" + aV.X() + ", " + aV.Y() + ", " + aV.Z() + ")");

                    // UV-coordinates
                    if (theTS.HasUVCoordinates())
                    {
                        ModelData_Point2d aUV = theTS.UVCoordinate(i, j);
                        Console.WriteLine("  UV Coordinates: (" + aUV.X() + ", " + aUV.Y() + ")");
                    }

                    // Normals
                    if (theTS.HasNormals())
                    {
                        ModelData_Vectorf aN = theTS.VertexNormal(i, j);
                        Console.WriteLine("  Normal vector: (" + aN.X() + ", " + aN.Y() + ", " + aN.Z() + ")");
                    }

                    // Colors
                    if (theTS.HasColors())
                    {
                        ModelData_Color aColor = theTS.VertexColor(i, j);
                        Console.WriteLine("  Color(RGBA): " + aColor.R() + ", " + aColor.G() + ", " + aColor.B() + ", " + aColor.A() + ")");
                    }
                }
            }
        }
    }
}
