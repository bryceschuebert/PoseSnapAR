// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2023, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// This file may be used under the terms and conditions of the License
// Agreement supplied with the software.
//
// This file is provided "AS IS" WITH NO WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE WARRANTY OF DESIGN,
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// ****************************************************************************


#ifndef _ModelData_DrawingGeometry_HeaderFile
#define _ModelData_DrawingGeometry_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_DrawingElement.hxx>

namespace cadex {
class ModelData_BSplineCurve2d;
class ModelData_Curve2d;
class ModelData_Point2d;
class ModelData_TrimmedCurve2d;

namespace internal {
class ModelData_DrawingCurveSetImpl;
class ModelData_DrawingGeometryImpl;
class ModelData_DrawingPiecewiseContourImpl;
class ModelData_DrawingPointSetImpl;
}

class ModelData_DrawingGeometry : public ModelData_DrawingElement
{
protected:
    explicit ModelData_DrawingGeometry (internal::ModelData_DrawingGeometryImpl* theImpl);
};

class ModelData_DrawingCurveSet : public ModelData_DrawingGeometry
{
public:
    typedef cadex::internal::ModelData_DrawingCurveSetImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingCurveSet();
    __CADEX_EXPORT explicit ModelData_DrawingCurveSet (ImplType*);

    __CADEX_EXPORT void AddCurve (const ModelData_Curve2d& theCurve);
    __CADEX_EXPORT size_t NumberOfCurves() const;
    __CADEX_EXPORT const ModelData_Curve2d& Curve (size_t theIndex) const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};

class ModelData_DrawingPointSet : public ModelData_DrawingGeometry
{
public:
    typedef cadex::internal::ModelData_DrawingPointSetImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingPointSet();
    __CADEX_EXPORT explicit ModelData_DrawingPointSet (ImplType*);

    __CADEX_EXPORT void AddPoint (const ModelData_Point2d& thePoint);
    __CADEX_EXPORT size_t NumberOfPoints() const;
    __CADEX_EXPORT const ModelData_Point2d& Point (size_t theIndex) const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};

class ModelData_DrawingPiecewiseContour : public ModelData_DrawingGeometry
{
public:
    typedef cadex::internal::ModelData_DrawingPiecewiseContourImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingPiecewiseContour();
    __CADEX_EXPORT explicit ModelData_DrawingPiecewiseContour (ImplType*);

    __CADEX_EXPORT bool IsClosed() const;

    __CADEX_EXPORT bool AddCurve (const ModelData_TrimmedCurve2d& theCurve);
    __CADEX_EXPORT bool AddCurve (const ModelData_BSplineCurve2d& theCurve);

    __CADEX_EXPORT size_t NumberOfCurves() const;
    __CADEX_EXPORT const ModelData_Curve2d& Curve (size_t theIndex) const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};

}

#endif
#endif
