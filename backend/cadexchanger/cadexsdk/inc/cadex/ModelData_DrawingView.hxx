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

#ifndef _ModelData_DrawingView_HeaderFile
#define _ModelData_DrawingView_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
class ModelData_Axis2Placement2d;
class ModelData_DrawingElement;
class ModelData_DrawingElementVisitor;
class ModelData_Ratio;

namespace internal {
class ModelData_DrawingViewImpl;
}

class ModelData_DrawingView : public ModelData_BaseObject
{
public:
    typedef cadex::internal::ModelData_DrawingViewImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingView();
    __CADEX_EXPORT explicit ModelData_DrawingView (const ModelData_Axis2Placement2d& thePosition);

    __CADEX_EXPORT const ModelData_Axis2Placement2d& Position() const;
    __CADEX_EXPORT void SetPosition (const ModelData_Axis2Placement2d& thePosition);

    __CADEX_EXPORT const ModelData_Ratio& Scale() const;
    __CADEX_EXPORT void SetScale (const ModelData_Ratio& theScale);

    __CADEX_EXPORT size_t NumberOfElements() const;
    __CADEX_EXPORT void Add (const ModelData_DrawingElement& theElement);

    __CADEX_EXPORT ModelData_Appearance ElementAppearance (const ModelData_DrawingElement& theElement) const;

    __CADEX_EXPORT void Accept (ModelData_DrawingElementVisitor& theVisitor) const;

    __CADEX_MODELDATA_DEFINE_TYPEID

    class ElementIterator
    {
    public:
        __CADEX_EXPORT ElementIterator (const ModelData_DrawingView& theView);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT ModelData_DrawingElement& Next();
    private:
        internal::Base_Handle myImpl;
    };
};

}

#endif
#endif
