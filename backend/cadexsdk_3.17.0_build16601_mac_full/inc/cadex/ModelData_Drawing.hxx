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


#ifndef _ModelData_Drawing_HeaderFile
#define _ModelData_Drawing_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
class ModelData_DrawingLayer;
class ModelData_DrawingSheet;

namespace internal {
class ModelData_DrawingImpl;
}

class ModelData_Drawing : public ModelData_BaseObject
{
public:
    __CADEX_EXPORT ModelData_Drawing();
    __CADEX_EXPORT explicit ModelData_Drawing (const ModelData_DrawingSheet& theSheet);

    __CADEX_EXPORT size_t NumberOfSheets() const;
    __CADEX_EXPORT void AddSheet (const ModelData_DrawingSheet& theSheet);

    __CADEX_EXPORT size_t NumberOfLayers() const;
    __CADEX_EXPORT void AddLayer (const ModelData_DrawingLayer& theLayer);

    __CADEX_MODELDATA_DEFINE_TYPEID

    class SheetIterator
    {
    public:
        __CADEX_EXPORT SheetIterator (const ModelData_Drawing& theDrawing);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_DrawingSheet& Next();

    private:
        internal::Base_Handle myImpl;
    };

    class LayerIterator
    {
    public:
        __CADEX_EXPORT LayerIterator (const ModelData_Drawing& theDrawing);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_DrawingLayer& Next();

    private:
        internal::Base_Handle myImpl;
    };
};

}

#endif
#endif
