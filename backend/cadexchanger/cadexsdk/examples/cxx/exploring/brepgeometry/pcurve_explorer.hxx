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


#ifndef _PCurveExplorer_HeaderFile
#define _PCurveExplorer_HeaderFile

#include <base_explorer.hxx>

#include <cadex/ModelData_Axis2Placement.hxx>
#include <cadex/ModelData_BezierCurve2d.hxx>
#include <cadex/ModelData_BSplineCurve2d.hxx>
#include <cadex/ModelData_Circle2d.hxx>
#include <cadex/ModelData_Ellipse2d.hxx>
#include <cadex/ModelData_Hyperbola2d.hxx>
#include <cadex/ModelData_Line2d.hxx>
#include <cadex/ModelData_OffsetCurve2d.hxx>
#include <cadex/ModelData_Parabola2d.hxx>
#include <cadex/ModelData_TrimmedCurve2d.hxx>


using namespace std;
using namespace cadex;

class PCurveExplorer : public BaseExplorer
{
public:
    static void PrintPCurveInfo (const ModelData_Curve2d& theCurve)
    {
        switch (theCurve.Type()) {
            case ModelData_CT_Line:
            PrintLine         (static_cast <const ModelData_Line2d&>         (theCurve));
        break;
            case ModelData_CT_Circle:
            PrintCircle       (static_cast <const ModelData_Circle2d&>       (theCurve));
        break;
            case ModelData_CT_Ellipse:
            PrintEllipse      (static_cast <const ModelData_Ellipse2d&>      (theCurve));
        break;
        case ModelData_CT_Hyperbola:
            PrintHyperbola    (static_cast <const ModelData_Hyperbola2d&>    (theCurve));
            break;
        case ModelData_CT_Parabola:
            PrintParabola     (static_cast <const ModelData_Parabola2d&>     (theCurve));
            break;
        case ModelData_CT_Bezier:
            PrintBezierCurve  (static_cast <const ModelData_BezierCurve2d&>  (theCurve));
            break;
        case ModelData_CT_BSpline:
            PrintBSplineCurve (static_cast <const ModelData_BSplineCurve2d&> (theCurve));
            break;
        case ModelData_CT_Offset:
            PrintOffsetCurve  (static_cast <const ModelData_OffsetCurve2d&>  (theCurve));
            break;
        case ModelData_CT_Trimmed:
            PrintTrimmedCurve (static_cast <const ModelData_TrimmedCurve2d&> (theCurve));
            break;
        default:
            break;
        }
    }

    static void PrintLine (const ModelData_Line2d& theLine)
    {
        PrintName ("Line 2d");
        const ModelData_Point2d&     aLoc = theLine.Location();
        const ModelData_Direction2d& aDir = theLine.Direction();
        PrintDomain (theLine);
        PrintParameter ("Location",  aLoc.Coord());
        PrintParameter ("Direction", aDir.Coord());
    }

    static void PrintCircle (const ModelData_Circle2d& theCircle)
    {
        PrintName ("Circle 2d");
        double aRadius = theCircle.Radius();
        PrintElementary2d (theCircle);
        PrintParameter ("Radius", aRadius);
    }

    static void PrintEllipse (const ModelData_Ellipse2d& theEllipse)
    {
        PrintName ("Ellipse 2d");
        double aMajorRadius = theEllipse.MajorRadius();
        double aMinorRadius = theEllipse.MinorRadius();
        PrintElementary2d (theEllipse);
        PrintParameter ("Major Radius", aMajorRadius);
        PrintParameter ("Minor Radius", aMinorRadius);
    }

    static void PrintHyperbola (const ModelData_Hyperbola2d& theHyperbola)
    {
        PrintName ("Hyperbola 2d");
        double aMajorRadius = theHyperbola.MajorRadius();
        double aMinorRadius = theHyperbola.MinorRadius();
        PrintElementary2d (theHyperbola);
        PrintParameter ("Major Radius", aMajorRadius);
        PrintParameter ("Minor Radius", aMinorRadius);
    }

    static void PrintParabola (const ModelData_Parabola2d& theParabola)
    {
        PrintName ("Parabola 2d");
        double aFocal = theParabola.Focal();
        PrintElementary2d (theParabola);
        PrintParameter ("Focal", aFocal);
    }

    static void PrintBezierCurve (const ModelData_BezierCurve2d& theBezier)
    {
        PrintName ("Bezier Curve 2d");
        int aDegree =        theBezier.Degree();
        int aNumberOfPoles = theBezier.NumberOfPoles();
        PrintDomain (theBezier);
        PrintParameter ("Degree",          aDegree);
        PrintParameter ("Number Of Poles", aNumberOfPoles);

        PrintCollection ("Poles", aNumberOfPoles, [&](int i)
        {
            auto aPole = theBezier.Pole (i);
            PrintParameter (aPole.Coord());
        });

        PrintCollection ("Weights", aNumberOfPoles, [&](int i)
        {
            double aWeight = theBezier.Weight (i);
            PrintParameter (aWeight);
        });
    }

    static void PrintBSplineCurve (const ModelData_BSplineCurve2d& theBSpline)
    {
        PrintName ("BSpline Curve 2d");
        int aDegree =        theBSpline.Degree();
        int aNumberOfKnots = theBSpline.NumberOfKnots();
        int aNumberOfPoles = theBSpline.NumberOfPoles();
        PrintDomain (theBSpline);
        PrintParameter ("Degree",          aDegree);
        PrintParameter ("Number Of Knots", aNumberOfKnots);
        PrintParameter ("Number Of Poles", aNumberOfPoles);

        PrintCollection ("Knots", aNumberOfKnots, [&](int i)
        {
            double aKnot = theBSpline.Knot (i);
            PrintParameter (aKnot);
        });

        PrintCollection ("Multiplicities", aNumberOfKnots, [&](int i)
        {
            int aMultiplicity = theBSpline.Multiplicity (i);
            PrintParameter (aMultiplicity);
        });

        PrintCollection ("Poles", aNumberOfPoles, [&](int i)
        {
            auto aPole = theBSpline.Pole (i);
            PrintParameter (aPole.Coord());
        });

        PrintCollection ("Weights", aNumberOfPoles, [&](int i)
        {
            double aWeight = theBSpline.Weight (i);
            PrintParameter (aWeight);
        });
    }

    static void PrintOffsetCurve (const ModelData_OffsetCurve2d& theOffset)
    {
        PrintName ("Offset Curve 2d");
        double anOffset = theOffset.Offset();
        PrintDomain (theOffset);
        PrintParameter ("Offset", anOffset);
        cout << "Basis Curve = ";
        PrintPCurveInfo (theOffset.BasisCurve());
    }

    static void PrintTrimmedCurve (const ModelData_TrimmedCurve2d& theTrimmed)
    {
        PrintName ("Trimmed Curve 2d");
        PrintDomain (theTrimmed);
        cout << "Basis Curve = ";
        PrintPCurveInfo (theTrimmed.BasisCurve());
    }
};

#endif
