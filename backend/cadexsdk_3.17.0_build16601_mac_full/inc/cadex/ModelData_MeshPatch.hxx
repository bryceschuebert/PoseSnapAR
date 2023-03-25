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


#ifndef _ModelData_MeshPatch_HeaderFile
#define _ModelData_MeshPatch_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_B_REP_TO_POLY_ASSOCIATIONS

#include <cadex/ModelData_IndexArray.hxx>
#include <cadex/ModelData_PolyVertexSet.hxx>

namespace cadex {

namespace internal {
class ModelData_MeshPatchImpl;
}

class ModelData_MeshPatch 
{
public:
    __CADEX_EXPORT ModelData_MeshPatch();
    __CADEX_EXPORT ModelData_MeshPatch (internal::ModelData_MeshPatchImpl* theImpl);

    __CADEX_EXPORT const ModelData_PolyVertexSet& PVS() const;
    __CADEX_EXPORT const ModelData_IndexArray& Indices() const;

    __CADEX_EXPORT bool IsNull() const;

    const std::shared_ptr<internal::ModelData_MeshPatchImpl>& Impl() const { return myImpl; }

private:

    std::shared_ptr<internal::ModelData_MeshPatchImpl> myImpl;
};

}

#endif

#endif
