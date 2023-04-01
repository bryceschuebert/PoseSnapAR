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
    class PCurveExplorer : BaseExplorer
    {

        // Prints 2d curve type name and prints shape info in some cases
        public static void PrintPCurveInfo(ModelData_Curve2d theCurve)
        {
            switch (theCurve.Type())
            {
                case ModelData_CurveType.ModelData_CT_Line:
                    PrintLine(ModelData_Line2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_Circle:
                    PrintCircle(ModelData_Circle2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_Ellipse:
                    PrintEllipse(ModelData_Ellipse2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_Hyperbola:
                    PrintHyperbola(ModelData_Hyperbola2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_Parabola:
                    PrintParabola(ModelData_Parabola2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_Bezier:
                    PrintBezierCurve(ModelData_BezierCurve2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_BSpline:
                    PrintBSplineCurve(ModelData_BSplineCurve2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_Offset:
                    PrintOffsetCurve(ModelData_OffsetCurve2d.Cast(theCurve));
                    break;
                case ModelData_CurveType.ModelData_CT_Trimmed:
                    PrintTrimmedCurve(ModelData_TrimmedCurve2d.Cast(theCurve));
                    break;
                default:
                    break;
            }
        }

        public static void PrintLine(ModelData_Line2d theLine)
        {
            PrintName("Line 2d");
            ModelData_Point2d     aLoc = theLine.Location();
            ModelData_Direction2d aDir = theLine.Direction();
            PrintDomain(theLine);
            PrintParameter("Location",  aLoc);
            PrintParameter("Direction", aDir);
        }

        public static void PrintCircle(ModelData_Circle2d theCircle)
        {
            PrintName("Circle 2d");
            double aRadius = theCircle.Radius();
            PrintElementary2d(theCircle);
            PrintParameter("Radius", aRadius);
        }

        public static void PrintEllipse(ModelData_Ellipse2d theEllipse)
        {
            PrintName("Ellipse 2d");
            double aMajorRadius = theEllipse.MajorRadius();
            double aMinorRadius = theEllipse.MinorRadius();
            PrintElementary2d(theEllipse);
            PrintParameter("Major Radius", aMajorRadius);
            PrintParameter("Minor Radius", aMinorRadius);
        }

        public static void PrintHyperbola(ModelData_Hyperbola2d theHyperbola)
        {
            PrintName("Hyperbola 2d");
            double aMajorRadius = theHyperbola.MajorRadius();
            double aMinorRadius = theHyperbola.MinorRadius();
            PrintElementary2d(theHyperbola);
            PrintParameter("Major Radius", aMajorRadius);
            PrintParameter("Minor Radius", aMinorRadius);
        }

        public static void PrintParabola(ModelData_Parabola2d theParabola)
        {
            PrintName("Parabola 2d");
            double aFocal = theParabola.Focal();
            PrintElementary2d(theParabola);
            PrintParameter("Focal", aFocal);
        }

        public static void PrintBezierCurve(ModelData_BezierCurve2d theBezier)
        {
            PrintName("Bezier Curve 2d");
            int aDegree =        theBezier.Degree();
            int aNumberOfPoles = theBezier.NumberOfPoles();
            PrintDomain(theBezier);
            PrintParameter("Degree",          aDegree);
            PrintParameter("Number Of Poles", aNumberOfPoles);

            PrintCollection("Poles", aNumberOfPoles, (int i) => {
                ModelData_Point2d aPole = theBezier.Pole(i);
                PrintParameter(aPole);
            });

            PrintCollection("Weights", aNumberOfPoles, (int i) => {
                double aWeight = theBezier.Weight(i);
                PrintParameter(aWeight);
            });
        }

        public static void PrintBSplineCurve(ModelData_BSplineCurve2d theBSpline)
        {
            PrintName("BSpline Curve 2d");
            int aDegree =        theBSpline.Degree();
            int aNumberOfKnots = theBSpline.NumberOfKnots();
            int aNumberOfPoles = theBSpline.NumberOfPoles();
            PrintDomain(theBSpline);
            PrintParameter("Degree",          aDegree);
            PrintParameter("Number Of Knots", aNumberOfKnots);
            PrintParameter("Number Of Poles", aNumberOfPoles);

            PrintCollection("Knots", aNumberOfKnots, (int i) =>
            {
                double aKnot = theBSpline.Knot(i);
                PrintParameter(aKnot);
            });

            PrintCollection("Multiplicities", aNumberOfKnots, (int i) => {
                int aMultiplicity = theBSpline.Multiplicity(i);
                PrintParameter(aMultiplicity);
            });

            PrintCollection("Poles", aNumberOfPoles, (int i) => {
                ModelData_Point2d aPole = theBSpline.Pole(i);
                PrintParameter(aPole);
            });

            PrintCollection("Weights", aNumberOfPoles, (int i) => {
                double aWeight = theBSpline.Weight(i);
                PrintParameter(aWeight);
            });
        }

        public static void PrintOffsetCurve(ModelData_OffsetCurve2d theOffset)
        {
            PrintName("Offset Curve 2d");
            double anOffset = theOffset.Offset();
            PrintDomain(theOffset);
            PrintParameter("Offset", anOffset);
            Console.Write("Basis Curve = ");
            PrintPCurveInfo(theOffset.BasisCurve());
        }

        public static void PrintTrimmedCurve(ModelData_TrimmedCurve2d theTrimmed)
        {
            PrintName("Trimmed Curve 2d");
            PrintDomain(theTrimmed);
            Console.Write("Basis Curve = ");
            PrintPCurveInfo(theTrimmed.BasisCurve());
        }
    }

   
}
