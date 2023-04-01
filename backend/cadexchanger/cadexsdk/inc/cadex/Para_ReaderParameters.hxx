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


#ifndef _Para_ReaderParameters_HeaderFile
#define _Para_ReaderParameters_HeaderFile

#include <cadex/Base_ReaderParameters.hxx>

namespace cadex {

class Para_ReaderParameters : public Base_ReaderParameters
{
public:
    __CADEX_EXPORT Para_ReaderParameters();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_PARA_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_PARA_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_PARA_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExParad.lib")
        #else
            #pragma comment(lib, "CadExPara.lib")
        #endif
    #endif
#endif
#endif
