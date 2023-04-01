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


#ifndef _SLD_ReaderParameters_HeaderFile
#define _SLD_ReaderParameters_HeaderFile

#include <cadex/Base_ReaderParameters.hxx>

namespace cadex {
class Base_UTF16String;

class SLD_ReaderParameters : public Base_ReaderParameters
{
public:
    enum ConfigurationsModeType
    {
        Actual,
        All,
        Custom
    };

    __CADEX_EXPORT SLD_ReaderParameters();

    __CADEX_EXPORT ConfigurationsModeType  ConfigurationsMode() const;
    __CADEX_EXPORT ConfigurationsModeType& ConfigurationsMode();
    
    __CADEX_EXPORT void SetCustomConfigurationNames (const Base_UTF16String theNames[], size_t theNameNb);

};

}

#endif
