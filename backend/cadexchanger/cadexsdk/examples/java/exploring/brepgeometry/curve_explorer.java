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

public class curve_explorer extends base_explorer {
    public static void PrintCurveInfo(final ModelData_Curve theCurve) {
        switch (theCurve.Type()) {
            case ModelData_CT_Line:
                PrintLine(ModelData_Line.Cast(theCurve));
                break;
            case ModelData_CT_Circle:
                PrintCircle(ModelData_Circle.Cast(theCurve));
                break;
            case ModelData_CT_Ellipse:
                PrintEllipse(ModelData_Ellipse.Cast(theCurve));
                break;
            case ModelData_CT_Hyperbola:
                PrintHyperbola(ModelData_Hyperbola.Cast(theCurve));
                break;
            case ModelData_CT_Parabola:
                PrintParabola(ModelData_Parabola.Cast(theCurve));
                break;
            case ModelData_CT_Bezier:
                PrintBezierCurve(ModelData_BezierCurve.Cast(theCurve));
                break;
            case ModelData_CT_BSpline:
                PrintBSplineCurve(ModelData_BSplineCurve.Cast(theCurve));
                break;
            case ModelData_CT_Offset:
                PrintOffsetCurve(ModelData_OffsetCurve.Cast(theCurve));
                break;
            case ModelData_CT_Trimmed:
                PrintTrimmedCurve(ModelData_TrimmedCurve.Cast(theCurve));
                break;
            default:
                break;
        }
    }

    public static void PrintLine(final ModelData_Line theLine) {
        PrintName("Line");
        ModelData_Point     aLoc = theLine.Location();
        ModelData_Direction aDir = theLine.Direction();
        PrintDomain(theLine);
        PrintParameter("Location",  aLoc);
        PrintParameter("Direction", aDir);
    }

    public static void PrintCircle(final ModelData_Circle theCircle) {
        PrintName("Circle");
        double aRadius = theCircle.Radius();
        PrintElementary(theCircle);
        PrintParameter("Radius", aRadius);
    }

    public static void PrintEllipse(final ModelData_Ellipse theEllipse) {
        PrintName("Ellipse");
        double aMajorRadius = theEllipse.MajorRadius();
        double aMinorRadius = theEllipse.MinorRadius();
        PrintElementary(theEllipse);
        PrintParameter("Major Radius", aMajorRadius);
        PrintParameter("Minor Radius", aMinorRadius);
    }

    public static void PrintHyperbola(final ModelData_Hyperbola theHyperbola) {
        PrintName("Hyperbola");
        double aMajorRadius = theHyperbola.MajorRadius();
        double aMinorRadius = theHyperbola.MinorRadius();
        PrintElementary(theHyperbola);
        PrintParameter("Major Radius", aMajorRadius);
        PrintParameter("Minor Radius", aMinorRadius);
    }

    public static void PrintParabola(final ModelData_Parabola theParabola) {
        PrintName("Parabola");
        double aFocal = theParabola.Focal();
        PrintElementary(theParabola);
        PrintParameter("Focal", aFocal);
    }

    public static void PrintBezierCurve(final ModelData_BezierCurve theBezier) {
        PrintName("Bezier Curve");
        int aDegree =        theBezier.Degree();
        int aNumberOfPoles = theBezier.NumberOfPoles();
        PrintDomain(theBezier);
        PrintParameter("Degree",          aDegree);
        PrintParameter("Number Of Poles", aNumberOfPoles);

        PrintCollection("Poles", aNumberOfPoles, (Integer i) ->
        {
            ModelData_Point aPole = theBezier.Pole(i);
            PrintParameter(aPole);
        });

        PrintCollection("Weights", aNumberOfPoles, (Integer i) ->
        {
            double aWeight = theBezier.Weight(i);
            PrintParameter(aWeight);
        });
    }

    public static void PrintBSplineCurve(final ModelData_BSplineCurve theBSpline) {
        PrintName("BSpline Curve");
        int aDegree =        theBSpline.Degree();
        int aNumberOfKnots = theBSpline.NumberOfKnots();
        int aNumberOfPoles = theBSpline.NumberOfPoles();
        PrintDomain(theBSpline);
        PrintParameter("Degree",          aDegree);
        PrintParameter("Number Of Knots", aNumberOfKnots);
        PrintParameter("Number Of Poles", aNumberOfPoles);

        PrintCollection("Knots", aNumberOfKnots, (Integer i) ->
        {
            double aKnot = theBSpline.Knot(i);
            PrintParameter(aKnot);
        });

        PrintCollection("Multiplicities", aNumberOfKnots, (Integer i) ->
        {
            int aMultiplicity = theBSpline.Multiplicity(i);
            PrintParameter(aMultiplicity);
        });

        PrintCollection("Poles", aNumberOfPoles, (Integer i) ->
        {
            ModelData_Point aPole = theBSpline.Pole(i);
            PrintParameter(aPole);
        });

        PrintCollection("Weights", aNumberOfPoles, (Integer i) ->
        {
            double aWeight = theBSpline.Weight(i);
            PrintParameter(aWeight);
        });
    }

    public static void PrintOffsetCurve(final ModelData_OffsetCurve theOffset) {
        PrintName("Offset Curve");
        final ModelData_Direction aDir = theOffset.Direction();
        double anOffset = theOffset.Offset();
        PrintDomain(theOffset);
        PrintParameter("Direction", aDir);
        PrintParameter("Offset",    anOffset);
        System.out.print("Basis Curve = ");
        PrintCurveInfo(theOffset.BasisCurve());
    }

    public static void PrintTrimmedCurve(final ModelData_TrimmedCurve theTrimmed) {
        PrintName("Trimmed Curve");
        PrintDomain(theTrimmed);
        System.out.print("Basis Curve = ");
        PrintCurveInfo(theTrimmed.BasisCurve());
    }
}
