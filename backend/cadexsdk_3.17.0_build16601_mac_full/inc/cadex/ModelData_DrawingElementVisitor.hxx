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


#ifndef _ModelData_DrawingElementVisitor_HeaderFile
#define _ModelData_DrawingElementVisitor_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

namespace cadex {
class ModelData_DrawingAngularDimension;
class ModelData_DrawingCurveSet;
class ModelData_DrawingDiametricDimension;
class ModelData_DrawingHatch;
class ModelData_DrawingLinearDimension;
class ModelData_DrawingPiecewiseContour;
class ModelData_DrawingPointSet;
class ModelData_DrawingPolyLineGeometry;
class ModelData_DrawingRadialDimension;
class ModelData_DrawingText;

class ModelData_DrawingElementVisitor
{
public:
    __CADEX_EXPORT virtual ~ModelData_DrawingElementVisitor();

    virtual void operator() (const ModelData_DrawingAngularDimension&   theElement) = 0;
    virtual void operator() (const ModelData_DrawingCurveSet&           theElement) = 0;
    virtual void operator() (const ModelData_DrawingDiametricDimension& theElement) = 0;
    virtual void operator() (const ModelData_DrawingHatch&              theElement) = 0;
    virtual void operator() (const ModelData_DrawingLinearDimension&    theElement) = 0;
    virtual void operator() (const ModelData_DrawingPiecewiseContour&   theElement) = 0;
    virtual void operator() (const ModelData_DrawingPointSet&           theElement) = 0;
    virtual void operator() (const ModelData_DrawingRadialDimension&    theElement) = 0;
    virtual void operator() (const ModelData_DrawingText&               theElement) = 0;

};

class ModelData_DrawingElementVoidVisitor : public ModelData_DrawingElementVisitor
{
public:
    void operator() (const ModelData_DrawingAngularDimension&  ) override {}
    void operator() (const ModelData_DrawingCurveSet&          ) override {}
    void operator() (const ModelData_DrawingDiametricDimension&) override {}
    void operator() (const ModelData_DrawingHatch&             ) override {}
    void operator() (const ModelData_DrawingLinearDimension&   ) override {}
    void operator() (const ModelData_DrawingPiecewiseContour&  ) override {}
    void operator() (const ModelData_DrawingPointSet&          ) override {}
    void operator() (const ModelData_DrawingRadialDimension&   ) override {}
    void operator() (const ModelData_DrawingText&              ) override {}
};

}

#endif
#endif
