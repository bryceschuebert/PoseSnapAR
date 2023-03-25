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


#ifndef _Unigine_NodeFactoryParameters_HeaderFile
#define _Unigine_NodeFactoryParameters_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>

#include <memory>

namespace cadex {

namespace internal {
class Unigine_NodeFactoryParametersImpl;
}

class Unigine_NodeFactoryParameters
{
public:
    __CADEX_EXPORT Unigine_NodeFactoryParameters();

    __CADEX_EXPORT void SetBRepMesherParameters (const ModelAlgo_BRepMesherParameters& theParameters);
    __CADEX_EXPORT const ModelAlgo_BRepMesherParameters& BRepMesherParameters() const;

    __CADEX_EXPORT void SetImportLODs (bool theImportLODs);
    __CADEX_EXPORT bool ImportLODs() const;

    __CADEX_EXPORT void SetImportProperties (bool theImportProperties);
    __CADEX_EXPORT bool ImportProperties() const;

    __CADEX_EXPORT void SetMergeTriangleSets (bool theMergeTriangleSets);
    __CADEX_EXPORT bool MergeTriangleSets() const;

    __CADEX_EXPORT void SetOptimizeMesh (bool theOptimizeMesh);
    __CADEX_EXPORT bool OptimizeMesh() const;

    __CADEX_EXPORT void SetScaleFactor (double theScaleFactor);
    __CADEX_EXPORT double ScaleFactor() const;

    __CADEX_EXPORT internal::Unigine_NodeFactoryParametersImpl* Impl() const;

private:
    std::shared_ptr<internal::Unigine_NodeFactoryParametersImpl> myImpl;
};

}

#endif
