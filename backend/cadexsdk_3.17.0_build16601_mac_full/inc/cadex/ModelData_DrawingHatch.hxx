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


#ifndef _ModelData_DrawingHatch_HeaderFile
#define _ModelData_DrawingHatch_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_DrawingElement.hxx>
#include <cadex/ModelData_DrawingGeometry.hxx>

namespace cadex {
namespace internal {
class ModelData_DrawingHatchImpl;
}

class ModelData_DrawingHatch : public ModelData_DrawingElement
{
public:

    enum PatternType {
        Solid,
        ANSI_31,
        ANSI_32,
        ANSI_33,
        ANSI_34,
        ANSI_35,
        ANSI_36,
        ANSI_37,
        ANSI_38
    };

    enum StyleType {
        Standard,
        Mirrored,
        Double
    };

    enum ContourType {
        Inner,
        Outer
    };

    typedef cadex::internal::ModelData_DrawingHatchImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingHatch();
    __CADEX_EXPORT explicit ModelData_DrawingHatch (ImplType*);

    __CADEX_EXPORT bool AddContour (const ModelData_DrawingPiecewiseContour& theContour, ContourType theType = Outer);
    __CADEX_EXPORT size_t NumberOfContours() const;
    __CADEX_EXPORT const ModelData_DrawingPiecewiseContour& Contour (size_t theIndex) const;
    __CADEX_EXPORT ContourType TypeOfContour (size_t theIndex) const;

    __CADEX_EXPORT void SetStyle (StyleType theStyle);
    __CADEX_EXPORT StyleType Style() const;

    __CADEX_EXPORT void SetPattern (PatternType thePattern);
    __CADEX_EXPORT PatternType Pattern() const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};


}

#endif
#endif
