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


#ifndef _ModelData_ConfigurationManager_HeaderFile
#define _ModelData_ConfigurationManager_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_CONFIGURATIONS

#include <cadex/ModelData_BaseObject.hxx>


namespace cadex {
class Base_UTF16String;
class ModelData_SceneGraphElement;

namespace internal {
class ModelData_ConfigurationManagerImpl;
}

class ModelData_ConfigurationManager : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_ConfigurationManagerImpl ImplType;

    __CADEX_EXPORT ModelData_ConfigurationManager();
    __CADEX_EXPORT ModelData_ConfigurationManager (const ModelData_SceneGraphElement& theBaseConfiguration);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetBaseConfiguration (const ModelData_SceneGraphElement& theBaseConfiguration);

    __CADEX_EXPORT ModelData_SceneGraphElement AddConfiguration (const Base_UTF16String& theName);

    __CADEX_EXPORT ModelData_SceneGraphElement Configuration (const Base_UTF16String& theName) const;
    
    __CADEX_EXPORT bool IsEmpty() const;

    __CADEX_EXPORT size_t NumberOfConfigurations() const;

    __CADEX_EXPORT static Base_UTF16String ConfigurationName (const ModelData_SceneGraphElement& theConfiguration);

    class ConfigurationIterator
    {
    public:
        __CADEX_EXPORT ConfigurationIterator (const ModelData_ConfigurationManager& theManager);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_SceneGraphElement& Next();

    private:
        internal::Base_Handle myImpl;
    };
};
}

#endif
#endif
