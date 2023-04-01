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


#ifndef _Unigine_NodeFactory_HeaderFile
#define _Unigine_NodeFactory_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_ProgressStatus.hxx>
#include <cadex/Base_UTF16String.hxx>
#include <cadex/ModelData_Model.hxx>

#include <UnigineNodes.h>

#include <memory>

namespace cadex {

class Unigine_NodeFactoryParameters;

namespace internal {
class Unigine_NodeFactoryImpl;
}

class Unigine_NodeFactory
{
public:
    __CADEX_EXPORT Unigine_NodeFactory();

    __CADEX_EXPORT Base_UTF16String Create (const ModelData_Model& theModel, const Base_UTF16String& theOutputFolder);

    __CADEX_EXPORT void SetParameters (const Unigine_NodeFactoryParameters& theParameters) const;
    __CADEX_EXPORT const Unigine_NodeFactoryParameters& Parameters() const;

    __CADEX_EXPORT void SetProgressStatus (const Base_ProgressStatus& theProgressStatus);
    __CADEX_EXPORT const Base_ProgressStatus& ProgressStatus() const;

private:
    std::shared_ptr<internal::Unigine_NodeFactoryImpl> myImpl;
};

}


#endif
