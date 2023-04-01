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
    class BaseExplorer
    {
        public static void PrintElementary(ModelData_Conic theGeometry)
        {
            PrintDomain(theGeometry);
            ModelData_Axis2Placement aPosition = theGeometry.Position();
            ModelData_Point          aLoc =      aPosition.Location();
            ModelData_Direction      anAxis =    aPosition.Axis();
            ModelData_Direction      aXDir =     aPosition.XDirection();
            ModelData_Direction      aYDir =     aPosition.YDirection();
            PrintParameter("Location",    aLoc);
            PrintParameter("Axis",        anAxis);
            PrintParameter("X Direction", aXDir);
            PrintParameter("Y Direction", aYDir);
        }

        public static void PrintElementary(ModelData_ElementarySurface theGeometry)
        {
            PrintDomain(theGeometry);
            ModelData_Axis3Placement aPosition = theGeometry.Position();
            ModelData_Point          aLoc =      aPosition.Location();
            ModelData_Direction      anAxis =    aPosition.Axis();
            ModelData_Direction      aXDir =     aPosition.XDirection();
            ModelData_Direction      aYDir =     aPosition.YDirection();
            PrintParameter("Location",    aLoc);
            PrintParameter("Axis",        anAxis);
            PrintParameter("X Direction", aXDir);
            PrintParameter("Y Direction", aYDir);
        }

        public static void PrintElementary2d(ModelData_Conic2d theGeometry)
        {
            PrintDomain(theGeometry);
            ModelData_Axis2Placement2d aPosition = theGeometry.Position();
            ModelData_Point2d          aLoc =      aPosition.Location();
            ModelData_Direction2d      aXDir =     aPosition.XDirection();
            ModelData_Direction2d      aYDir =     aPosition.YDirection();
            PrintParameter("Location",    aLoc);
            PrintParameter("X Direction", aXDir);
            PrintParameter("Y Direction", aYDir);
        }

        public static void PrintRange(string aName, double aFirstParameter, double aLastParameter)
        {
            Console.Write("{0} = [{1}, {2}]; ", aName, aFirstParameter, aLastParameter);
        }

        public static void PrintDomain(ModelData_Curve theCurve)
        {
            PrintRange("Domain", theCurve.UMin(), theCurve.UMax());
        }

        public static void PrintDomain(ModelData_Curve2d theCurve)
        {
            PrintRange("Domain", theCurve.UMin(), theCurve.UMax());
        }

        public static void PrintDomain(ModelData_Surface theSurface)
        {
            PrintRange("Domain U", theSurface.UMin(), theSurface.UMax());
            PrintRange("V", theSurface.VMin(), theSurface.VMax());
        }

        public static void PrintParameter(ModelData_Point theValue)
        {
            Console.Write("({0}, {1}); ", theValue.X(), theValue.Y());
        }

        public static void PrintParameter(ModelData_Direction theValue)
        {
            Console.Write("({0}, {1}, {2}); ", theValue.X(), theValue.Y(), theValue.Z());
        }

        public static void PrintParameter(ModelData_Point2d theValue)
        {
            Console.Write("({0}, {1}); ", theValue.X(), theValue.Y());
        }

        public static void PrintParameter(ModelData_Direction2d theValue)
        {
            Console.Write("({0}, {1}); ", theValue.X(), theValue.Y());
        }

        public static void PrintParameter(double theValue)
        {
            Console.Write("{0}; ", theValue);
        }

        public static void PrintParameter(string theName, ModelData_Point theValue)
        {
            Console.Write("{0} = ", theName);
            PrintParameter(theValue);
        }

        public static void PrintParameter(string theName, ModelData_Direction theValue)
        {
            Console.Write("{0} = ", theName);
            PrintParameter(theValue);
        }


        public static void PrintParameter(string theName, double theValue)
        {
            Console.Write("{0} = ", theName);
            PrintParameter(theValue);
        }

        public static void PrintParameter(string theName, ModelData_Point2d theValue)
        {
            Console.Write("{0} = ", theName);
            PrintParameter(theValue);
        }

        public static void PrintParameter(string theName, ModelData_Direction2d theValue)
        {
            Console.Write("{0} = ", theName);
            PrintParameter(theValue);
        }

        public static void PrintName(string theName)
        {
            Console.Write("{0}: ", theName);
        }

        public delegate void myPrint1dElement(int i);
        public static void PrintCollection(string theName,
                                           int theFinalIndex,
                                           myPrint1dElement thePrintElement)
        {
            if (theName != null)
            {
                Console.Write("{0} = ", theName);
            }

            Console.Write("[");
            for (int i = 1; i <= theFinalIndex; ++i)
            {
                if (i > 3)
                {
                    Console.Write("...");
                    break;
                }
                thePrintElement(i);
            }
            Console.Write("]; ");
        }

        public delegate void myPrint2dElement(int i, int j);

        public static void PrintCollection(string theName,
                                           int theFinalIndex1,
                                           int theFinalIndex2,
                                           myPrint2dElement thePrintElement)
        {
            PrintCollection(theName, theFinalIndex1, (int i) =>
            {
                PrintCollection(null, theFinalIndex2, (int j) => { thePrintElement(i, j); });
            });
        }

        public static void PrintOrientation(ModelData_ShapeOrientation theOrientation)
        {
            Console.Write("Orientation = ");
            switch (theOrientation)
            {
                case ModelData_ShapeOrientation.ModelData_SO_Forward: Console.Write("Forward"); break;
                case ModelData_ShapeOrientation.ModelData_SO_Reversed: Console.Write("Reversed"); break;
                default: Console.Write("Undefined"); break;
            }
            Console.Write("; ");
        }

        public void PrintTabulation()
        {
            for (uint i = 0; i < myNestingLevel; ++i)
            {
                Console.Write("--- ");
            }
        }

        public uint myNestingLevel = 0;
    }
}

