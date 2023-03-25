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


#ifndef _CurveExplorer_HeaderFile
#define _CurveExplorer_HeaderFile

#include <cadex/ModelData_Axis2Placement.hxx>
#include <cadex/ModelData_BezierCurve.hxx>
#include <cadex/ModelData_BSplineCurve.hxx>
#include <cadex/ModelData_Circle.hxx>
#include <cadex/ModelData_Ellipse.hxx>
#include <cadex/ModelData_Hyperbola.hxx>
#include <cadex/ModelData_Line.hxx>
#include <cadex/ModelData_OffsetCurve.hxx>
#include <cadex/ModelData_Parabola.hxx>
#include <cadex/ModelData_TrimmedCurve.hxx>

#include <base_explorer.hxx>

using namespace std;
using namespace cadex;

class CurveExplorer : public BaseExplorer
{
public:
    static void PrintCurveInfo (const ModelData_Curve& theCurve)
    {
        switch (theCurve.Type()) {
        case ModelData_CT_Line:
            PrintLine         (static_cast <const ModelData_Line&>         (theCurve));
            break;
        case ModelData_CT_Circle:
            PrintCircle       (static_cast <const ModelData_Circle&>       (theCurve));
            break;
        case ModelData_CT_Ellipse:
            PrintEllipse      (static_cast <const ModelData_Ellipse&>      (theCurve));
            break;
        case ModelData_CT_Hyperbola:
            PrintHyperbola    (static_cast <const ModelData_Hyperbola&>    (theCurve));
            break;
        case ModelData_CT_Parabola:
            PrintParabola     (static_cast <const ModelData_Parabola&>     (theCurve));
            break;
        case ModelData_CT_Bezier:
            PrintBezierCurve  (static_cast <const ModelData_BezierCurve&>  (theCurve));
            break;
        case ModelData_CT_BSpline:
            PrintBSplineCurve (static_cast <const ModelData_BSplineCurve&> (theCurve));
            break;
        case ModelData_CT_Offset:
            PrintOffsetCurve  (static_cast <const ModelData_OffsetCurve&>  (theCurve));
            break;
        case ModelData_CT_Trimmed:
            PrintTrimmedCurve (static_cast <const ModelData_TrimmedCurve&> (theCurve));
            break;
        default:
            break;
        }
    }

    static void PrintLine (const ModelData_Line& theLine)
    {
        PrintName ("Line");
        const ModelData_Point& aLoc =     theLine.Location();
        const ModelData_Direction& aDir = theLine.Direction();
        PrintDomain (theLine);
        PrintParameter ("Location",  aLoc.Coord());
        PrintParameter ("Direction", aDir.Coord());
    }

    static void PrintCircle (const ModelData_Circle& theCircle)
    {
        PrintName ("Circle");
        double aRadius = theCircle.Radius();
        PrintElementary (theCircle);
        PrintParameter ("Radius", aRadius);
    }

    static void PrintEllipse (const ModelData_Ellipse& theEllipse)
    {
        PrintName ("Ellipse");
        double aMajorRadius = theEllipse.MajorRadius();
        double aMinorRadius = theEllipse.MinorRadius();
        PrintElementary (theEllipse);
        PrintParameter ("Major Radius", aMajorRadius);
        PrintParameter ("Minor Radius", aMinorRadius);
    }

    static void PrintHyperbola (const ModelData_Hyperbola& theHyperbola)
    {
        PrintName ("Hyperbola");
        double aMajorRadius = theHyperbola.MajorRadius();
        double aMinorRadius = theHyperbola.MinorRadius();
        PrintElementary (theHyperbola);
        PrintParameter ("Major Radius", aMajorRadius);
        PrintParameter ("Minor Radius", aMinorRadius);
    }

    static void PrintParabola (const ModelData_Parabola& theParabola)
    {
        PrintName ("Parabola");
        double aFocal = theParabola.Focal();
        PrintElementary (theParabola);
        PrintParameter ("Focal", aFocal);
    }

    static void PrintBezierCurve (const ModelData_BezierCurve& theBezier)
    {
        PrintName ("Bezier Curve");
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

    static void PrintBSplineCurve (const ModelData_BSplineCurve& theBSpline)
    {
        PrintName ("BSpline Curve");
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

    static void PrintOffsetCurve (const ModelData_OffsetCurve& theOffset)
    {
        PrintName ("Offset Curve");
        const ModelData_Direction& aDir = theOffset.Direction();
        double anOffset = theOffset.Offset();
        PrintDomain (theOffset);
        PrintParameter ("Direction", aDir.Coord());
        PrintParameter ("Offset",    anOffset);
        cout << "Basis Curve = ";
        PrintCurveInfo (theOffset.BasisCurve());
    }

    static void PrintTrimmedCurve (const ModelData_TrimmedCurve& theTrimmed)
    {
        PrintName ("Trimmed Curve");
        PrintDomain (theTrimmed);
        cout << "Basis Curve = ";
        PrintCurveInfo (theTrimmed.BasisCurve());
    }
};
#endif
