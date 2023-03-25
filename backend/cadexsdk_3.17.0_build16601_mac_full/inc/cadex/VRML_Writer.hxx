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


#ifndef _VRML_Writer_HeaderFile
#define _VRML_Writer_HeaderFile

#include <cadex/Base_Writer.hxx>


namespace cadex {
class VRML_WriterParameters;

class VRML_Writer : public Base_Writer
{
public:

    __CADEX_EXPORT VRML_Writer();

    __CADEX_EXPORT const VRML_WriterParameters& Parameters() const;

    __CADEX_EXPORT VRML_WriterParameters& Parameters();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_VRML_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_VRML_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_VRML_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExVRMLd.lib")
        #else
            #pragma comment(lib, "CadExVRML.lib")
        #endif
    #endif
#endif

#endif
