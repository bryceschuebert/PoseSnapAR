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


#ifndef _ModelPrs_SceneNodeFactory_HeaderFile
#define _ModelPrs_SceneNodeFactory_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION

#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>

#include <memory>

namespace cadex {
class ModelData_Body;
class ModelData_Model;
class ModelData_PMIGraphicalElement;
class ModelData_PolyVertexSet;
class ModelData_Representation;
class ModelData_SceneGraphElement;
class ModelPrs_Measurement;
class ModelPrs_SceneNode;
class ModelPrs_SceneNodeFactoryParameters;

namespace internal {
class ModelPrs_SceneNodeFactoryImpl;
}

class ModelPrs_SceneNodeFactory : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_SceneNodeFactoryImpl    ImplType;

    __CADEX_EXPORT ModelPrs_SceneNodeFactory();

    __CADEX_EXPORT ModelPrs_SceneNodeFactory (const ModelPrs_SceneNodeFactoryParameters& theParameters);

    __CADEX_EXPORT ModelPrs_SceneNodeFactoryParameters& Parameters();
    __CADEX_EXPORT const ModelPrs_SceneNodeFactoryParameters& Parameters() const;

    __CADEX_EXPORT ModelPrs_SceneNode CreateGraph (const ModelData_Model&       theModel,
                                                   ModelData_RepresentationMask theRepresentationMask);

    __CADEX_EXPORT ModelPrs_SceneNode CreateGraph (const ModelData_Model&  theModel,
                                                   const Base_UTF16String& theRepresentationName);

    __CADEX_EXPORT ModelPrs_SceneNode CreateNode (const ModelData_SceneGraphElement& theSceneGraphElement);

    __CADEX_EXPORT ModelPrs_SceneNode CreateNode (const ModelData_Representation& theRepresentation);

    __CADEX_EXPORT ModelPrs_SceneNode CreateNode (const ModelData_PolyVertexSet& thePolyVertexSet);

    __CADEX_EXPORT ModelPrs_SceneNode CreateNode (
        const ModelData_Body&               theBody,
        const ModelData_BRepRepresentation& theRep  = ModelData_BRepRepresentation());

    __CADEX_EXPORT ModelPrs_SceneNode CreateNode (const ModelPrs_Measurement& theMeasurement);

    __CADEX_EXPORT ModelPrs_SceneNode CreateNode (const ModelData_PMIGraphicalElement& thePMIGraphicalElement);
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_SceneNodeFactory_HeaderFile
