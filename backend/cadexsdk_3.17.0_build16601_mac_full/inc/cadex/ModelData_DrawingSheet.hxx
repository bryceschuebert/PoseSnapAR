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


#ifndef _ModelData_DrawingSheet_HeaderFile
#define _ModelData_DrawingSheet_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {

class ModelData_DrawingView;

namespace internal {
class ModelData_DrawingSheetImpl;
}

class ModelData_DrawingSheet : public ModelData_BaseObject
{
public:
    typedef cadex::internal::ModelData_DrawingSheetImpl ImplType;

    enum PaperSizeType
    {
        UnknownPaperSize = 0,
        A0,
        A1,
        A2,
        A3,
        A4,
        A,
        B,
        C,
        D,
        E,
        UserDefinedPaperSize = 1000
    };

    enum OrientationType
    {
        Landscape,
        Portrait
    };

    __CADEX_EXPORT ModelData_DrawingSheet();

    __CADEX_EXPORT double Width() const;
    __CADEX_EXPORT double Height() const;
    __CADEX_EXPORT PaperSizeType PaperSize() const;
    __CADEX_EXPORT OrientationType Orientation() const;
    __CADEX_EXPORT void SetStandardSheetSize (PaperSizeType thePaperSize,
                                              OrientationType theOrientation);
    __CADEX_EXPORT void SetCustomSheetSize (double theWidth, double theHeight);

    __CADEX_EXPORT size_t NumberOfViews() const;
    __CADEX_EXPORT void AddView (const ModelData_DrawingView& theView);

    __CADEX_MODELDATA_DEFINE_TYPEID

    class ViewIterator
    {
    public:
        __CADEX_EXPORT ViewIterator (const ModelData_DrawingSheet& theSheet);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_DrawingView& Next();

    private:
        internal::Base_Handle myImpl;
    };
};

}

#endif
#endif
