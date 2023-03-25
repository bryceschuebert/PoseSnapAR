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

import cadex.*;

public class shape_explorer extends ModelData_Model.VoidElementVisitor {

    @Override
    public void Apply(ModelData_Part thePart) {
        ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
        if (aBRep != null) {
            System.out.println("Part = \"" + thePart.Name() + "\"");
            ExploreBRep (aBRep);
        }
    }

    private void ExploreBRep (final ModelData_BRepRepresentation theBRep) {
        // Get() method retrieves bodies listed in B-Rep representation by calling data providers flushing
        // Flushing isn't an elementary process so it can take a significant time (seconds, minutes depending on a model structure)
        final ModelData_BodyList  aBodyList = theBRep.Get();

        // Iterate over bodies
        for (int i = 0; i < aBodyList.Size(); ++i){
            final ModelData_Body  aBody = aBodyList.Element(i);
            System.out.println("Body " + i + ": " + BodyType(aBody));
            ExploreShape(aBody);
        }
    }

    // Recursive iterating over the Shape until reaching vertices
    private void ExploreShape (final ModelData_Shape theShape) {
        if (theShape.Type() == ModelData_ShapeType.ModelData_ST_Face) {
            myCurrentFace = ModelData_Face.Cast (theShape);
        }
        ++myBase.myNestingLevel;
        ModelData_Shape.Iterator aShapeIt = new ModelData_Shape.Iterator(theShape);
        while (aShapeIt.HasNext()) {
            ModelData_Shape aShape = aShapeIt.Next();
            PrintShape (aShape);
            ExploreShape (aShape);
        }
        if (theShape.Type() == ModelData_ShapeType.ModelData_ST_Face) {
            myCurrentFace = null;
        }
        --myBase.myNestingLevel;
    }

    // Returns body type name
    private final String BodyType (final ModelData_Body theBody) {
        switch (theBody.BodyType()) {
            case ModelData_BT_Solid:     return "Solid";
            case ModelData_BT_Sheet:     return "Sheet";
            case ModelData_BT_Wireframe: return "Wireframe";
            case ModelData_BT_Acorn:     return "Acorn";
            default:
                break;
        }
        return "Undefined";
    }

    // Returns shape type name and prints shape info in some cases
    private void PrintShape (final ModelData_Shape theShape) {
        myBase.PrintTabulation();

        switch (theShape.Type()) {
            case ModelData_ST_Solid:  System.out.print("Solid");                     break;
            case ModelData_ST_Shell:  PrintShell (ModelData_Shell.Cast  (theShape)); break;
            case ModelData_ST_Wire:   PrintWire  (ModelData_Wire.Cast   (theShape)); break;
            case ModelData_ST_Face:   PrintFace  (ModelData_Face.Cast   (theShape)); break;
            case ModelData_ST_Edge:   PrintEdge  (ModelData_Edge.Cast   (theShape)); break;
            case ModelData_ST_Vertex: PrintVertex(ModelData_Vertex.Cast (theShape)); break;
            default: System.out.print("Undefined");                                  break;
        }

        System.out.println("");
    }

    private void PrintShell (final ModelData_Shell theWire) {
        myBase.PrintName("Shell");
        ++myBase.myNestingLevel;
        myBase.PrintOrientation(theWire.Orientation());
        --myBase.myNestingLevel;
    }

    private void PrintWire(final ModelData_Wire theWire) {
        myBase.PrintName("Wire");
        ++myBase.myNestingLevel;
        myBase.PrintOrientation(theWire.Orientation());
        --myBase.myNestingLevel;
    }

    private void PrintFace (final ModelData_Face theFace) {
        myBase.PrintName("Face");
        ++myBase.myNestingLevel;
        myBase.PrintOrientation (theFace.Orientation());
        System.out.println("");
        ModelData_Surface aSurface = theFace.Surface();
        myBase.PrintTabulation();
        myBase.PrintName("Surface");
        surface_explorer.PrintSurface (aSurface);
        --myBase.myNestingLevel;
    }

    private void PrintEdge (final ModelData_Edge theEdge) {
        myBase.PrintName("Edge");
        ++myBase.myNestingLevel;
        if (theEdge.IsDegenerated()) {
            System.out.print("Degenerated: ");
        }
        myBase.PrintOrientation(theEdge.Orientation());
        myBase.PrintParameter("Tolerance", theEdge.Tolerance());

        if (!theEdge.IsDegenerated()) {
            double[] aFirstParameter = {0}, aLastParameter = {0};
            ModelData_Curve aCurve = theEdge.Curve(aFirstParameter, aLastParameter);
            System.out.println("");
            myBase.PrintTabulation();
            myBase.PrintName("Curve");
            myBase.PrintRange("Edge Range", aFirstParameter[0], aLastParameter[0]);
            curve_explorer.PrintCurveInfo(aCurve);
        }

        if (myCurrentFace != null) {
            double[] aFirstParameter2d = {0}, aLastParameter2d = {0};
            final ModelData_Curve2d aPCurve = theEdge.PCurve(myCurrentFace,
                                                             aFirstParameter2d,
                                                             aLastParameter2d);
            System.out.println("");
            myBase.PrintTabulation();
            myBase.PrintName("PCurve");
            myBase.PrintRange("Edge Range", aFirstParameter2d[0], aLastParameter2d[0]);
            pcurve_explorer.PrintPCurveInfo(aPCurve);
        }
        --myBase.myNestingLevel;
    }

    private void PrintVertex(final ModelData_Vertex theVertex) {
        myBase.PrintName ("Vertex");
        ModelData_Point aLoc =       theVertex.Point();
        double          aTolerance = theVertex.Tolerance();
        myBase.PrintOrientation(theVertex.Orientation());
        myBase.PrintParameter("Tolerance", aTolerance);
        myBase.PrintParameter("Location",  aLoc);
    }

    private base_explorer myBase = new base_explorer();
    private ModelData_Face myCurrentFace = null;
}
