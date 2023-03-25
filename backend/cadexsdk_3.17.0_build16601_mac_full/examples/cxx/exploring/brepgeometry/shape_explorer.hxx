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


#ifndef _ShapeExplorer_HeaderFile
#define _ShapeExplorer_HeaderFile

#include <curve_explorer.hxx>
#include <base_explorer.hxx>
#include <pcurve_explorer.hxx>
#include <surface_explorer.hxx>

#include <cadex/ModelData_Body.hxx>
#include <cadex/ModelData_BodyList.hxx>
#include <cadex/ModelData_BodyType.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Curve.hxx>
#include <cadex/ModelData_Curve2d.hxx>
#include <cadex/ModelData_Edge.hxx>
#include <cadex/ModelData_Face.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_Shell.hxx>
#include <cadex/ModelData_Surface.hxx>
#include <cadex/ModelData_Vertex.hxx>
#include <cadex/ModelData_Wire.hxx>

#include <array>
#include <functional>
#include <iostream>
#include <unordered_map>


using namespace std;
using namespace cadex;

// Visits directly each part and calls B-Rep representation exploring if a part has one
class ShapeExplorer : public ModelData_Model::VoidElementVisitor, public BaseExplorer
{
protected:

    void operator() (const ModelData_Part& thePart) override
    {
        const ModelData_BRepRepresentation& aBRep = thePart.BRepRepresentation();
        if (aBRep) {
            cout << "Part = \"" << thePart.Name() << "\"" << endl;
            ExploreBRep (aBRep);
        }
    }

private:

    void ExploreBRep (const ModelData_BRepRepresentation& theBRep)
    {
        // Get() method retrieves bodies listed in B-Rep representation by calling data providers flushing
        // Flushing isn't an elementary process so it can take a significant time (seconds, minutes depending on a model structure)
        const ModelData_BodyList& aBodyList = theBRep.Get();

        // Iterate over bodies
        for (ModelData_BodyList::SizeType i = 0; i < aBodyList.Size(); ++i) {
            const ModelData_Body& aBody = aBodyList[i];
            cout << "Body " << i << ": " << BodyType (aBody) << endl;

            ExploreShape (aBody);
        }
    }

    // Recursive iterating over the Shape until reaching vertices
    void ExploreShape (const ModelData_Shape& theShape)
    {
        if (theShape.Type() == ModelData_ST_Face) {
            myCurrentFace = ModelData_Face::Cast (theShape);
        }
        ++myNestingLevel;
        ModelData_Shape::Iterator aShapeIt (theShape);
        while (aShapeIt.HasNext()) {
            const ModelData_Shape& aShape = aShapeIt.Next();
            PrintShape (aShape);
            ExploreShape (aShape);
        }
        if (theShape.Type() == ModelData_ST_Face) {
            myCurrentFace = ModelData_Face();
        }
        --myNestingLevel;
    }

    // Returns body type name
    const char* BodyType (const ModelData_Body& theBody)
    {
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
    void PrintShape (const ModelData_Shape& theShape)
    {
        PrintTabulation();

        switch (theShape.Type()) {
        case ModelData_ST_Solid:  cout << "Solid";                                 break;
        case ModelData_ST_Shell:  PrintShell  (ModelData_Shell::Cast  (theShape)); break;
        case ModelData_ST_Wire:   PrintWire   (ModelData_Wire::Cast   (theShape)); break;
        case ModelData_ST_Face:   PrintFace   (ModelData_Face::Cast   (theShape)); break;
        case ModelData_ST_Edge:   PrintEdge   (ModelData_Edge::Cast   (theShape)); break;
        case ModelData_ST_Vertex: PrintVertex (ModelData_Vertex::Cast (theShape)); break;
        default:
        cout << "Undefined"; break;
        }

        cout << endl;
    }

    void PrintShell (const ModelData_Shell& theWire)
    {
        PrintName ("Shell");
        ++myNestingLevel;
        PrintOrientation (theWire.Orientation());
        --myNestingLevel;
    }

    void PrintWire (const ModelData_Wire& theWire)
    {
        PrintName ("Wire");
        ++myNestingLevel;
        PrintOrientation (theWire.Orientation());
        --myNestingLevel;
    }

    void PrintFace (const ModelData_Face& theFace)
    {
        PrintName ("Face");
        ++myNestingLevel;
        PrintOrientation (theFace.Orientation());
        cout << endl;
        ModelData_Surface aSurface = theFace.Surface();
        PrintTabulation();
        cout << "Surface: ";
        SurfaceExplorer::PrintSurface (aSurface);
        --myNestingLevel;
    }

    void PrintEdge (const ModelData_Edge& theEdge)
    {
        PrintName ("Edge");
        ++myNestingLevel;
        if (theEdge.IsDegenerated()) {
            cout << "Degenerated: ";
        }
        PrintOrientation (theEdge.Orientation());
        PrintParameter ("Tolerance", theEdge.Tolerance());

        if (!theEdge.IsDegenerated()) {
            pair<double, double> aParameters;
            ModelData_Curve aCurve = theEdge.Curve (aParameters.first, aParameters.second);
            cout << endl;
            PrintTabulation();
            PrintName ("Curve");
            PrintRange ("Edge Range", aParameters.first, aParameters.second);
            CurveExplorer::PrintCurveInfo (aCurve);
        }
            
        if (myCurrentFace) {
            pair<double, double> aParameters2d;
            const ModelData_Curve2d& aPCurve = theEdge.PCurve (myCurrentFace,
                                                               aParameters2d.first, 
                                                               aParameters2d.second);
            cout << endl;
            PrintTabulation();
            PrintName ("PCurve");
            PrintRange ("Edge Range", aParameters2d.first, aParameters2d.second);
            PCurveExplorer::PrintPCurveInfo (aPCurve);
        }
        --myNestingLevel;
    }

    void PrintVertex (const ModelData_Vertex& theVertex)
    {
        PrintName ("Vertex");
        ModelData_Point aLoc =       theVertex.Point();
        double          aTolerance = theVertex.Tolerance();
        PrintOrientation (theVertex.Orientation());
        PrintParameter ("Tolerance", aTolerance);
        PrintParameter ("Location",  aLoc.Coord());
    }

    private: 
        ModelData_Face myCurrentFace;
};

#endif
