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


#ifndef _U3D_Writer_HeaderFile
#define _U3D_Writer_HeaderFile

#include <cadex/Base_Writer.hxx>

namespace cadex {

class U3D_WriterParameters;

class U3D_Writer : public Base_Writer
{
public:

    __CADEX_EXPORT U3D_Writer();

    __CADEX_EXPORT const U3D_WriterParameters& Parameters() const;

    __CADEX_EXPORT U3D_WriterParameters& Parameters();

protected:

    U3D_Writer (internal::Base_Writer_Private* theImpl) : Base_Writer (theImpl)
    {}
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_U3D_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_U3D_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_U3D_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExU3Dd.lib")
        #else
            #pragma comment(lib, "CadExU3D.lib")
        #endif
    #endif
#endif

#endif
