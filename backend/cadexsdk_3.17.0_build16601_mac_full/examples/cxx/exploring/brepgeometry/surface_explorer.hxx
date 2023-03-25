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


#ifndef _SurfaceExplorer_HeaderFile
#define _SurfaceExplorer_HeaderFile

#include <base_explorer.hxx>

#include <cadex/ModelData_Axis3Placement.hxx>
#include <cadex/ModelData_BezierSurface.hxx>
#include <cadex/ModelData_BSplineSurface.hxx>
#include <cadex/ModelData_ConicalSurface.hxx>
#include <cadex/ModelData_CylindricalSurface.hxx>
#include <cadex/ModelData_OffsetSurface.hxx>
#include <cadex/ModelData_Plane.hxx>
#include <cadex/ModelData_RectangularTrimmedSurface.hxx>
#include <cadex/ModelData_SphericalSurface.hxx>
#include <cadex/ModelData_SurfaceOfLinearExtrusion.hxx>
#include <cadex/ModelData_SurfaceOfRevolution.hxx>
#include <cadex/ModelData_ToroidalSurface.hxx>


using namespace std;
using namespace cadex;

class SurfaceExplorer : public BaseExplorer
{
public:
    static void PrintSurface (const ModelData_Surface& theSurface)
    {
        switch (theSurface.Type()) {
        case ModelData_ST_Plane:
            PrintPlane           (static_cast <const ModelData_Plane&>                     (theSurface));
            break;
        case ModelData_ST_Cylinder:
            PrintCylinder        (static_cast <const ModelData_CylindricalSurface&>        (theSurface));
            break;
        case ModelData_ST_Cone:
            PrintCone            (static_cast <const ModelData_ConicalSurface&>            (theSurface));
            break;
        case ModelData_ST_Sphere:
            PrintSphere          (static_cast <const ModelData_SphericalSurface&>          (theSurface));
            break;
        case ModelData_ST_Torus:
            PrintTorus           (static_cast <const ModelData_ToroidalSurface&>           (theSurface));
            break;
        case ModelData_ST_LinearExtrusion:
            PrintLinearExtrusion (static_cast <const ModelData_SurfaceOfLinearExtrusion&>  (theSurface));
            break;
        case ModelData_ST_Revolution:
            PrintRevolution      (static_cast <const ModelData_SurfaceOfRevolution&>       (theSurface));
            break;
        case ModelData_ST_Bezier:
            PrintBezierSurface   (static_cast <const ModelData_BezierSurface&>             (theSurface));
            break;
        case ModelData_ST_BSpline:
            PrintBSplineSurface  (static_cast <const ModelData_BSplineSurface&>            (theSurface));
            break;
        case ModelData_ST_Offset:
            PrintOffsetSurface   (static_cast <const ModelData_OffsetSurface&>             (theSurface));
            break;
        case ModelData_ST_Trimmed:
            PrintTrimmedSurface  (static_cast <const ModelData_RectangularTrimmedSurface&> (theSurface));
            break;
        default:
            break;
        }
    }

    static void PrintPlane (const ModelData_Plane& thePlane)
    {
        PrintName ("Plane");
        PrintElementary (thePlane);
    }

    static void PrintCylinder (const ModelData_CylindricalSurface& theCylinder)
    {
        PrintName ("Cylinder");
        double aRadius = theCylinder.Radius();
        PrintElementary (theCylinder);
        PrintParameter ("Radius", aRadius);
    }

    static void PrintCone (const ModelData_ConicalSurface& theCone)
    {
        PrintName ("Cone");
        double aRadius =    theCone.Radius();
        double aSemiAngle = theCone.SemiAngle();
        PrintElementary (theCone);
        PrintParameter ("Radius", aRadius);
        PrintParameter ("Semi-Angle", aSemiAngle);
    }

    static void PrintSphere (const ModelData_SphericalSurface& theSphere)
    {
        PrintName ("Sphere");
        double aRadius = theSphere.Radius();
        PrintElementary (theSphere);
        PrintParameter ("Radius", aRadius);
    }

    static void PrintTorus (const ModelData_ToroidalSurface& theTorus)
    {
        PrintName ("Torus");
        double aMajorRadius = theTorus.MajorRadius();
        double aMinorRadius = theTorus.MinorRadius();
        PrintElementary (theTorus);
        PrintParameter ("Major Radius", aMajorRadius);
        PrintParameter ("Minor Radius", aMinorRadius);
    }

    static void PrintLinearExtrusion (const ModelData_SurfaceOfLinearExtrusion& theLinearExtrusion)
    {
        PrintName ("Linear Extrusion Surface");
        const ModelData_Direction& aDir = theLinearExtrusion.Direction();
        PrintDomain (theLinearExtrusion);
        PrintParameter ("Direction", aDir.Coord());
        cout << "Basis Curve = ";
        CurveExplorer::PrintCurveInfo (theLinearExtrusion.BasisCurve());
    }

    static void PrintRevolution (const ModelData_SurfaceOfRevolution& theRevolution)
    {
        PrintName ("Revolution Surface");
        const ModelData_Direction& aDir = theRevolution.Direction();
        const ModelData_Point&     aLoc = theRevolution.Location();
        PrintDomain (theRevolution);
        PrintParameter ("Location",  aLoc.Coord());
        PrintParameter ("Direction", aDir.Coord());
        cout << "Basis Curve = ";
        CurveExplorer::PrintCurveInfo (theRevolution.BasisCurve());
    }

    static void PrintBezierSurface (const ModelData_BezierSurface& theBezier)
    {
        PrintName ("Bezier Surface");
        int aUDegree =        theBezier.UDegree();
        int aVDegree =        theBezier.VDegree();
        int aNumberOfUPoles = theBezier.NumberOfUPoles();
        int aNumberOfVPoles = theBezier.NumberOfVPoles();
        PrintDomain (theBezier);
        PrintParameter ("U Degree",          aUDegree);
        PrintParameter ("V Degree",          aVDegree);
        PrintParameter ("Number Of U Poles", aNumberOfUPoles);
        PrintParameter ("Number Of V Poles", aNumberOfVPoles);

        PrintCollection ("Poles", aNumberOfUPoles, aNumberOfVPoles, [&](int i, int j)
        {
            auto aPole = theBezier.Pole (i, j);
            PrintParameter (aPole.Coord());
        });

        PrintCollection ("Weights", aNumberOfUPoles, aNumberOfVPoles, [&](int i, int j)
        {
            double aWeight = theBezier.Weight (i, j);
            PrintParameter (aWeight);
        });
    }

    static void PrintBSplineSurface (const ModelData_BSplineSurface& theBSpline)
    {
        PrintName ("BSpline Surface");

        int aUDegree =        theBSpline.UDegree();
        int aVDegree =        theBSpline.VDegree();
        int aNumberOfUKnots = theBSpline.NumberOfUKnots();
        int aNumberOfVKnots = theBSpline.NumberOfVKnots();
        int aNumberOfUPoles = theBSpline.NumberOfUPoles();
        int aNumberOfVPoles = theBSpline.NumberOfVPoles();
        PrintDomain (theBSpline);
        PrintParameter ("U Degree",          aUDegree);
        PrintParameter ("V Degree",          aVDegree);
        PrintParameter ("Number Of U Knots", aNumberOfUKnots);
        PrintParameter ("Number Of V Knots", aNumberOfVKnots);
        PrintParameter ("Number Of U Poles", aNumberOfUPoles);
        PrintParameter ("Number Of V Poles", aNumberOfVPoles);

        PrintCollection ("U Knots", aNumberOfUKnots, [&](int i)
        {
            double aKnot = theBSpline.UKnot (i);
            PrintParameter (aKnot);
        });

        PrintCollection ("V Knots", aNumberOfVKnots, [&](int i)
        {
            double aKnot = theBSpline.VKnot (i);
            PrintParameter (aKnot);
        });


        PrintCollection ("U Multiplicities", aNumberOfUKnots, [&](int i)
        {
            int aUMultiplicity = theBSpline.UMultiplicity (i);
            PrintParameter (aUMultiplicity);
        });

        PrintCollection ("V Multiplicities", aNumberOfVKnots, [&](int i)
        {
            int aVMultiplicity = theBSpline.VMultiplicity (i);
            PrintParameter (aVMultiplicity);
        });

        PrintCollection ("Poles", aNumberOfUPoles, aNumberOfVPoles, [&](int i, int j)
        {
            auto aPole = theBSpline.Pole (i, j);
            PrintParameter (aPole.Coord());
        });

        PrintCollection ("Weights", aNumberOfUPoles, aNumberOfVPoles, [&](int i, int j)
        {
            double aWeight = theBSpline.Weight (i, j);
            PrintParameter (aWeight);
        });
    }

    static void PrintOffsetSurface (const ModelData_OffsetSurface& theOffset)
    {
        PrintName ("Offset Surface");
        double anOffset = theOffset.Offset();
        PrintDomain (theOffset);
        PrintParameter ("Offset", anOffset);
        cout << "Basis Surface = ";
        PrintSurface (theOffset.BasisSurface());
    }

    static void PrintTrimmedSurface (const ModelData_RectangularTrimmedSurface& theTrimmed)
    {
        PrintName ("Trimmed Surface");
        PrintDomain (theTrimmed);
        cout << "Basis Surface = ";
        PrintSurface (theTrimmed.BasisSurface());
    }
};
#endif
