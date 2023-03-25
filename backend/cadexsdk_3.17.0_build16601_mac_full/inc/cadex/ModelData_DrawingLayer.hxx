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


#ifndef _ModelData_DrawingLayer_HeaderFile
#define _ModelData_DrawingLayer_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
class ModelData_Appearance;
class ModelData_DrawingElement;
class ModelData_DrawingElementVisitor;

namespace internal {
class ModelData_DrawingLayerImpl;
}

class ModelData_DrawingLayer : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_DrawingLayerImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingLayer();
    __CADEX_EXPORT explicit ModelData_DrawingLayer (initialized);
    __CADEX_EXPORT explicit ModelData_DrawingLayer (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_DrawingLayer (const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT bool IsVisible() const;
    __CADEX_EXPORT void SetIsVisible (bool theIsVisible);

    __CADEX_EXPORT void SetAppearance (const ModelData_Appearance& theAppearance);
    __CADEX_EXPORT ModelData_Appearance Appearance() const;

    __CADEX_EXPORT void Add (const ModelData_DrawingElement& theElement);

    __CADEX_EXPORT bool Remove (const ModelData_DrawingElement& theElement);

    __CADEX_EXPORT bool Contains (const ModelData_DrawingElement& theElement) const;

    __CADEX_EXPORT void Accept (ModelData_DrawingElementVisitor& theVisitor) const;
};

}

#endif
#endif
