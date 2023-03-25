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


#ifndef _OBJ_Reader_HeaderFile
#define _OBJ_Reader_HeaderFile

#include <cadex/Base_Reader.hxx>

namespace cadex {

class OBJ_ReaderParameters;

class OBJ_Reader : public Base_Reader
{
public:

    __CADEX_EXPORT OBJ_Reader();

    //! Returns parameters.
    __CADEX_EXPORT const OBJ_ReaderParameters& Parameters() const;

    //! Returns parameters.
    __CADEX_EXPORT OBJ_ReaderParameters& Parameters();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_OBJ_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_OBJ_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_OBJ_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExOBJd.lib")
        #else
            #pragma comment(lib, "CadExOBJ.lib")
        #endif
    #endif
#endif

#endif
