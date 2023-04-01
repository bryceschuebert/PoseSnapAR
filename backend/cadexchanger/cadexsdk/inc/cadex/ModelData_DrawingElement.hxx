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


#ifndef _ModelData_DrawingElement_HeaderFile
#define _ModelData_DrawingElement_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
class ModelData_DrawingElementVisitor;

namespace internal {
class ModelData_DrawingElementImpl;
}

class ModelData_DrawingElement : public ModelData_BaseObject
{
public:
    __CADEX_EXPORT void Accept (ModelData_DrawingElementVisitor& theVisitor) const;

protected:
    explicit ModelData_DrawingElement (internal::ModelData_DrawingElementImpl* theImpl);
};

}

#endif
#endif
