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


using cadex;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace brepgeometry 
{
    class ShapeExplorer : ModelData_Model.VoidElementVisitor
    {
        public override void Apply(ModelData_Part thePart)
        {
            ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
            if (aBRep != null)
            {
                Console.WriteLine("Part = \"{0}\"", thePart.Name());
                ExploreBRep(aBRep);
            }
        }

        private void ExploreBRep(ModelData_BRepRepresentation theBRep)
        {
            // Get() method retrieves bodies listed in B-Rep representation by calling data providers flushing
            // Flushing isn't an elementary process so it can take a significant time (seconds, minutes depending on a model structure)
            ModelData_BodyList aBodyList = theBRep.Get();

            // Iterate over bodies
            for (uint i = 0; i < aBodyList.Size(); ++i)
            {
                ModelData_Body aBody = aBodyList.Access(i);
                Console.WriteLine("Body {0}: -type {1}", i, BodyType(aBody));
                ExploreShape(aBody);
            }
        }

        // Recursive iterating over the Shape until reaching vertices
        private void ExploreShape(ModelData_Shape theShape)
        {
            if (theShape.Type() == ModelData_ShapeType.ModelData_ST_Face)
            {
                myCurrentFace = ModelData_Face.Cast(theShape);
            }
            ++myBase.myNestingLevel;
            ModelData_Shape.Iterator aShapeIt = new ModelData_Shape.Iterator(theShape);
            while (aShapeIt.HasNext())
            {
                ModelData_Shape aShape = aShapeIt.Next();
                PrintShape(aShape);
                ExploreShape(aShape);
            }
            if (theShape.Type() == ModelData_ShapeType.ModelData_ST_Face)
            {
                myCurrentFace = null;
            }
            --myBase.myNestingLevel;
        }

        // Returns body type name
        private string BodyType(ModelData_Body theBody)
        {
            switch (theBody.BodyType())
            {
                case ModelData_BodyType.ModelData_BT_Solid: return "Solid";
                case ModelData_BodyType.ModelData_BT_Sheet: return "Sheet";
                case ModelData_BodyType.ModelData_BT_Wireframe: return "Wireframe";
                case ModelData_BodyType.ModelData_BT_Acorn: return "Acorn";
            }
            return "Undefined";
        }

        // Prints shape type name and prints shape info in some cases
        private void PrintShape(ModelData_Shape theShape)
        {
            myBase.PrintTabulation();

            switch (theShape.Type())
            {
                case ModelData_ShapeType.ModelData_ST_Solid:
                    Console.Write("Solid");
                    break;
                case ModelData_ShapeType.ModelData_ST_Shell:
                    PrintShell(ModelData_Shell.Cast(theShape));
                    break;
                case ModelData_ShapeType.ModelData_ST_Wire:
                    PrintWire(ModelData_Wire.Cast(theShape));
                    break;
                case ModelData_ShapeType.ModelData_ST_Face:
                    PrintFace(ModelData_Face.Cast(theShape));
                    break;
                case ModelData_ShapeType.ModelData_ST_Edge:
                    PrintEdge(ModelData_Edge.Cast(theShape));
                    break;
                case ModelData_ShapeType.ModelData_ST_Vertex:
                    PrintVertex(ModelData_Vertex.Cast(theShape));
                    break;
                default: Console.Write("Undefined"); break;
            }

            Console.WriteLine();
        }

        private void PrintShell(ModelData_Shell theWire)
        {
            BaseExplorer.PrintName("Shell");
            ++myBase.myNestingLevel;
            BaseExplorer.PrintOrientation(theWire.Orientation());
            --myBase.myNestingLevel;
        }

        private void PrintWire(ModelData_Wire theWire)
        {
            BaseExplorer.PrintName("Wire");
            ++myBase.myNestingLevel;
            BaseExplorer.PrintOrientation(theWire.Orientation());
            --myBase.myNestingLevel;
        }

        private void PrintFace(ModelData_Face theFace)
        {
            BaseExplorer.PrintName("Face");
            ++myBase.myNestingLevel;
            BaseExplorer.PrintOrientation(theFace.Orientation());
            Console.WriteLine();
            ModelData_Surface aSurface = theFace.Surface();
            myBase.PrintTabulation();
            BaseExplorer.PrintName("Surface");
            SurfaceExplorer.PrintSurface(aSurface);
            --myBase.myNestingLevel;
        }

        private void PrintEdge(ModelData_Edge theEdge)
        {
            BaseExplorer.PrintName("Edge");
            ++myBase.myNestingLevel;
            if (theEdge.IsDegenerated())
            {
                Console.Write("Degenerated: ");
            }
            BaseExplorer.PrintOrientation(theEdge.Orientation());
            BaseExplorer.PrintParameter("Tolerance", theEdge.Tolerance());

            if (!theEdge.IsDegenerated())
            {
                double aFirstParameter = 0, aLastParameter = 0;
                ModelData_Curve aCurve = theEdge.Curve(ref aFirstParameter, ref aLastParameter);
                Console.WriteLine();
                myBase.PrintTabulation();
                BaseExplorer.PrintName("Curve");
                BaseExplorer.PrintRange("Edge Range", aFirstParameter, aLastParameter);
                CurveExplorer.PrintCurveInfo(aCurve);
            }

            if (myCurrentFace != null)
            {
                double aFirstParameter2d = 0, aLastParameter2d = 0;
                ModelData_Curve2d aPCurve = theEdge.PCurve(myCurrentFace,
                                                           ref aFirstParameter2d,
                                                           ref aLastParameter2d);
                Console.WriteLine();
                myBase.PrintTabulation();
                BaseExplorer.PrintName("PCurve");
                BaseExplorer.PrintRange("Edge Range", aFirstParameter2d, aLastParameter2d);
                PCurveExplorer.PrintPCurveInfo(aPCurve);
            }
            --myBase.myNestingLevel;
        }

        private void PrintVertex(ModelData_Vertex theVertex)
        {
            BaseExplorer.PrintName("Vertex");
            ModelData_Point aLoc =       theVertex.Point();
            double          aTolerance = theVertex.Tolerance();
            BaseExplorer.PrintOrientation(theVertex.Orientation());
            BaseExplorer.PrintParameter("Tolerance", aTolerance);
            BaseExplorer.PrintParameter("Location", aLoc);
        }

        private BaseExplorer myBase = new BaseExplorer();
        private ModelData_Face myCurrentFace = null;
    }
}
