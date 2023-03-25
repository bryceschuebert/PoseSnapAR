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


#ifndef _ModelData_BRepToPolyAssociations_HeaderFile
#define _ModelData_BRepToPolyAssociations_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_B_REP_TO_POLY_ASSOCIATIONS

#include <cadex/ModelData_MeshPatch.hxx>

#include <memory>


namespace cadex {

class ModelData_Edge;
class ModelData_Face;
class ModelData_Vertex;

namespace internal {
class ModelData_BRepToPolyAssociationsImpl;
}

class ModelData_BRepToPolyAssociations
{
public:

    __CADEX_EXPORT ModelData_BRepToPolyAssociations();
    __CADEX_EXPORT ~ModelData_BRepToPolyAssociations();

    __CADEX_EXPORT ModelData_MeshPatch Get (const ModelData_Vertex& theVertex) const;
    __CADEX_EXPORT ModelData_MeshPatch Get (const ModelData_Edge&   theEdge)   const;
    __CADEX_EXPORT ModelData_MeshPatch Get (const ModelData_Face&   theFace)   const;

    const std::shared_ptr<internal::ModelData_BRepToPolyAssociationsImpl>& Impl() const { return myImpl; }

private:

    std::shared_ptr<internal::ModelData_BRepToPolyAssociationsImpl>   myImpl;
};

}
#endif

#endif
