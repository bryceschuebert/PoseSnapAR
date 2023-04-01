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


#ifndef _ModelPrs_SceneNodeFactoryParameters_HeaderFile
#define _ModelPrs_SceneNodeFactoryParameters_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION

#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>

namespace cadex {

namespace internal {
class ModelPrs_SceneNodeFactoryParametersImpl;
}

class ModelPrs_SceneNodeFactoryParameters : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_SceneNodeFactoryParametersImpl    ImplType;

    __CADEX_EXPORT ModelPrs_SceneNodeFactoryParameters (
        const ModelAlgo_BRepMesherParameters& theBRepParams = ModelAlgo_BRepMesherParameters());

    __CADEX_EXPORT void SetMesherParameters (const ModelAlgo_BRepMesherParameters& theParameters);
    __CADEX_EXPORT const ModelAlgo_BRepMesherParameters& MesherParameters() const;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_SceneNodeFactoryParameters_HeaderFile
