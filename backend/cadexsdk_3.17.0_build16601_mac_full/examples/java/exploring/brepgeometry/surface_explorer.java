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

public class surface_explorer extends base_explorer {
    public static void PrintSurface(ModelData_Surface theSurface) {
        switch (theSurface.Type()) {
            case ModelData_ST_Plane:
                PrintPlane(ModelData_Plane.Cast(theSurface));
                break;
            case ModelData_ST_Cylinder:
                PrintCylinder(ModelData_CylindricalSurface.Cast(theSurface));
                break;
            case ModelData_ST_Cone:
                PrintCone(ModelData_ConicalSurface.Cast(theSurface));
                break;
            case ModelData_ST_Sphere:
                PrintSphere(ModelData_SphericalSurface.Cast(theSurface));
                break;
            case ModelData_ST_Torus:
                PrintTorus(ModelData_ToroidalSurface.Cast(theSurface));
                break;
            case ModelData_ST_LinearExtrusion:
                PrintLinearExtrusion(ModelData_SurfaceOfLinearExtrusion.Cast(theSurface));
                break;
            case ModelData_ST_Revolution:
                PrintRevolution(ModelData_SurfaceOfRevolution.Cast(theSurface));
                break;
            case ModelData_ST_Bezier:
                PrintBezierSurface(ModelData_BezierSurface.Cast(theSurface));
                break;
            case ModelData_ST_BSpline:
                PrintBSplineSurface(ModelData_BSplineSurface.Cast(theSurface));
                break;
            case ModelData_ST_Offset:
                PrintOffsetSurface(ModelData_OffsetSurface.Cast(theSurface));
                break;
            case ModelData_ST_Trimmed:
                PrintTrimmedSurface(ModelData_RectangularTrimmedSurface.Cast(theSurface));
                break;
            default:
                break;
        }
    }

    public static void PrintPlane(ModelData_Plane thePlane) {
        PrintName("Plane");
        PrintElementary(thePlane);
    }

    public static void PrintCylinder(ModelData_CylindricalSurface theCylinder) {
        PrintName("Cylinder");
        double aRadius = theCylinder.Radius();
        PrintElementary(theCylinder);
        PrintParameter("Radius", aRadius);
    }

    public static void PrintCone(ModelData_ConicalSurface theCone) {
        PrintName("Cone");
        double aRadius =    theCone.Radius();
        double aSemiAngle = theCone.SemiAngle();
        PrintElementary(theCone);
        PrintParameter("Radius",     aRadius);
        PrintParameter("Semi-Angle", aSemiAngle);
    }

    public static void PrintSphere(ModelData_SphericalSurface theSphere)
    {
        PrintName ("Sphere");
        double aRadius = theSphere.Radius();
        PrintElementary(theSphere);
        PrintParameter("Radius", aRadius);
    }

    public static void PrintTorus(ModelData_ToroidalSurface theTorus) {
        PrintName("Torus");
        double aMajorRadius = theTorus.MajorRadius();
        double aMinorRadius = theTorus.MinorRadius();
        PrintElementary(theTorus);
        PrintParameter("Major Radius", aMajorRadius);
        PrintParameter("Minor Radius", aMinorRadius);
    }

    public static void PrintLinearExtrusion(ModelData_SurfaceOfLinearExtrusion theLinearExtrusion) {
        PrintName("Linear Extrusion Surface");
        ModelData_Direction aDir = theLinearExtrusion.Direction();
        PrintDomain(theLinearExtrusion);
        PrintParameter("Direction", aDir);
        System.out.print("Basis Curve = ");
        curve_explorer.PrintCurveInfo(theLinearExtrusion.BasisCurve());
    }

    public static void PrintRevolution(ModelData_SurfaceOfRevolution theRevolution) {
        PrintName("Revolution Surface");
        ModelData_Direction aDir = theRevolution.Direction();
        ModelData_Point     aLoc = theRevolution.Location();
        PrintDomain(theRevolution);
        PrintParameter("Location",  aLoc);
        PrintParameter("Direction", aDir);
        System.out.print("Basis Curve = ");
        curve_explorer.PrintCurveInfo(theRevolution.BasisCurve());
    }

    public static void PrintBezierSurface(ModelData_BezierSurface theBezier) {
        PrintName ("Bezier Surface");
        int aUDegree =        theBezier.UDegree();
        int aVDegree =        theBezier.VDegree();
        int aNumberOfUPoles = theBezier.NumberOfUPoles();
        int aNumberOfVPoles = theBezier.NumberOfVPoles();
        PrintDomain(theBezier);
        PrintParameter("U Degree",          aUDegree);
        PrintParameter("V Degree",          aVDegree);
        PrintParameter("Number Of U Poles", aNumberOfUPoles);
        PrintParameter("Number Of V Poles", aNumberOfVPoles);

        PrintCollection("Poles", aNumberOfUPoles, aNumberOfVPoles, (Integer i, Integer j) -> {
            ModelData_Point aPole = theBezier.Pole(i, j);
            PrintParameter(aPole);
        });

        PrintCollection("Weights", aNumberOfUPoles, aNumberOfVPoles, (Integer i, Integer j) -> {
            double aWeight = theBezier.Weight (i, j);
            PrintParameter (aWeight);
        });
    }

    public static void PrintBSplineSurface(ModelData_BSplineSurface theBSpline) {
        PrintName("BSpline Surface");
        int aUDegree =        theBSpline.UDegree();
        int aVDegree =        theBSpline.VDegree();
        int aNumberOfUKnots = theBSpline.NumberOfUKnots();
        int aNumberOfVKnots = theBSpline.NumberOfVKnots();
        int aNumberOfUPoles = theBSpline.NumberOfUPoles();
        int aNumberOfVPoles = theBSpline.NumberOfVPoles();
        PrintDomain(theBSpline);
        PrintParameter("U Degree",          aUDegree);
        PrintParameter("V Degree",          aVDegree);
        PrintParameter("Number Of U Knots", aNumberOfUKnots);
        PrintParameter("Number Of V Knots", aNumberOfVKnots);
        PrintParameter("Number Of U Poles", aNumberOfUPoles);
        PrintParameter("Number Of V Poles", aNumberOfVPoles);

        PrintCollection("U Knots", aNumberOfUKnots, (Integer i) -> {
            double aKnot = theBSpline.UKnot(i);
            PrintParameter(aKnot);
        });

        PrintCollection("V Knots", aNumberOfVKnots, (Integer i) -> {
            double aKnot = theBSpline.VKnot(i);
            PrintParameter(aKnot);
        });


        PrintCollection("U Multiplicities", aNumberOfUKnots, (Integer i) -> {
            int aUMultiplicity = theBSpline.UMultiplicity(i);
            PrintParameter(aUMultiplicity);
        });

        PrintCollection("V Multiplicities", aNumberOfVKnots, (Integer i) -> {
            int aVMultiplicity = theBSpline.VMultiplicity(i);
            PrintParameter(aVMultiplicity);
        });

        PrintCollection("Poles", aNumberOfUPoles, aNumberOfVPoles, (Integer i, Integer j) -> {
            ModelData_Point aPole = theBSpline.Pole(i, j);
            PrintParameter(aPole);
        });

        PrintCollection("Weights", aNumberOfUPoles, aNumberOfVPoles, (Integer i, Integer j) -> {
            double aWeight = theBSpline.Weight(i, j);
            PrintParameter(aWeight);
        });
    }

    public static void PrintOffsetSurface(ModelData_OffsetSurface theOffset) {
        PrintName("Offset Surface");
        double anOffset = theOffset.Offset();
        PrintDomain(theOffset);
        PrintParameter("Offset", anOffset);
        System.out.print("Basis Surface = ");
        PrintSurface(theOffset.BasisSurface());
    }

    public static void PrintTrimmedSurface(ModelData_RectangularTrimmedSurface theTrimmed) {
        PrintName("Trimmed Surface");
        PrintDomain(theTrimmed);
        System.out.print("Basis Surface = ");
        PrintSurface(theTrimmed.BasisSurface());
    }
}
