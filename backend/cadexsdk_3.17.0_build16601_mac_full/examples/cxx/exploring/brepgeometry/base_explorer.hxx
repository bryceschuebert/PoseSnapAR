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


#ifndef _BaseExplorer_HeaderFile
#define _BaseExplorer_HeaderFile

#include <cadex/ModelData_Axis2Placement2d.hxx>
#include <cadex/ModelData_Curve2d.hxx>
#include <cadex/ModelData_Direction.hxx>
#include <cadex/ModelData_Direction2d.hxx>
#include <cadex/ModelData_Point.hxx>
#include <cadex/ModelData_Point2d.hxx>
#include <cadex/ModelData_ShapeOrientation.hxx>
#include <cadex/ModelData_Surface.hxx>
#include <cadex/ModelData_XY.hxx>
#include <cadex/ModelData_XYZ.hxx>

#include <functional>
#include <iostream>

using namespace std;
using namespace cadex;

class BaseExplorer
{
public:

    template <typename T>
    static void PrintElementary (const T& theGeometry)
    {
        PrintDomain (theGeometry);
        auto& aPosition = theGeometry.Position();
        const ModelData_Point&     aLoc =   aPosition.Location();
        const ModelData_Direction& anAxis = aPosition.Axis();
        const ModelData_Direction& aXDir =  aPosition.XDirection();
        const ModelData_Direction& aYDir =  aPosition.YDirection();
        PrintParameter ("Location",    aLoc.Coord());
        PrintParameter ("Axis",        anAxis.Coord());
        PrintParameter ("X Direction", aXDir.Coord());
        PrintParameter ("Y Direction", aYDir.Coord());
    }

    template <typename T>
    static void PrintElementary2d (const T& theGeometry)
    {
        PrintDomain (theGeometry);
        auto& aPosition = theGeometry.Position();
        const ModelData_Point2d&     aLoc =  aPosition.Location();
        const ModelData_Direction2d& aXDir = aPosition.XDirection();
        const ModelData_Direction2d& aYDir = aPosition.YDirection();
        PrintParameter ("Location",    aLoc.Coord());
        PrintParameter ("X Direction", aXDir.Coord());
        PrintParameter ("Y Direction", aYDir.Coord());
    }

    static void PrintRange (const char* aName, double aFirstParameter, double aLastParameter)
    {
        cout << aName << " = [" << aFirstParameter << ", " << aLastParameter << "]; ";
    }

    static void PrintDomain (const ModelData_Curve& theCurve)
    {
        PrintRange ("Domain", theCurve.UMin(), theCurve.UMax());
    }
    
    static void PrintDomain (const ModelData_Curve2d& theCurve)
    {
        PrintRange ("Domain", theCurve.UMin(), theCurve.UMax());
    }

    static void PrintDomain (const ModelData_Surface& theSurface)
    {
        PrintRange ("Domain U", theSurface.UMin(), theSurface.UMax());
        PrintRange ("V", theSurface.VMin(), theSurface.VMax());
    }

    static void PrintParameter (ModelData_XYZd thePoint)
    {
        cout << "(" << thePoint.X() << ", " << thePoint.Y() << ", " << thePoint.Z() << "); ";
    }

    static void PrintParameter (ModelData_XYd thePoint)
    {
        cout << "(" << thePoint.X() << ", " << thePoint.Y() << "); ";
    }

    static void PrintParameter (double theValue)
    {
        cout << theValue << "; ";
    }

    template <typename T>
    static void PrintParameter (const char* theName, T theValue)
    {
        cout << theName << " = ";
        PrintParameter (theValue);
    }

    static void PrintName (const char* theName)
    {
        cout << theName << ": ";
    }

    static void PrintCollection (const char* theName,
                                 int theFinalIndex,
                                 std::function <void (int)> thePrintElement)
    {
        if (theName) {
            cout << theName << " = ";
        }

        cout << "[";
        for (int i = 1; i <= theFinalIndex; ++i)
        {
            if (i > 3) {
                cout << "...";
                break;
            }
            thePrintElement(i);
        }
        cout << "]; ";
    }

    static void PrintCollection (const char* theName,
                                 int theFinalIndex1,
                                 int theFinalIndex2,
                                 std::function <void (int, int)> thePrintElement)
    {
        PrintCollection (theName, theFinalIndex1, [&](int i)
        {
            PrintCollection (nullptr, theFinalIndex2, [&](int j) {thePrintElement(i, j); });
        });
    }

    static void PrintOrientation (const ModelData_ShapeOrientation& theOrientation)
    {
        cout << "Orientation = ";
        switch (theOrientation) {
        case ModelData_SO_Forward:  cout << "Forward";  break;
        case ModelData_SO_Reversed: cout << "Reversed"; break;
        default:
            cout << "Undefined";
            break;
        }
        cout << "; ";
    }

    void PrintTabulation()
    {
        for (size_t i = 0; i < myNestingLevel; ++i) {
            cout << "--- ";
        }
    }

    size_t myNestingLevel = 0;
};

#endif
