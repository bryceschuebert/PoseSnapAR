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


#ifndef _ModelData_DrawingText_HeaderFile
#define _ModelData_DrawingText_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_DrawingElement.hxx>

namespace cadex {
class Base_UTF16String;
class ModelData_Point2d;

namespace internal {
class ModelData_DrawingTextImpl;
}

class ModelData_DrawingText : public ModelData_DrawingElement
{
public:

    typedef cadex::internal::ModelData_DrawingTextImpl     ImplType;

    __CADEX_EXPORT ModelData_DrawingText();
    __CADEX_EXPORT explicit ModelData_DrawingText (ImplType* theImpl);

    __CADEX_EXPORT void SetText (const Base_UTF16String& theText);
    __CADEX_EXPORT const Base_UTF16String& Text() const;

    __CADEX_EXPORT void SetTextOrigin (const ModelData_Point2d& theTextOrigin);
    __CADEX_EXPORT const ModelData_Point2d& TextOrigin() const;

    __CADEX_EXPORT void SetFontSize (float theFontSize);
    __CADEX_EXPORT float FontSize() const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};
}

#endif
#endif
