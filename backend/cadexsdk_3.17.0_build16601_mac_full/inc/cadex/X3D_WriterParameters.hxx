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


#ifndef _X3D_WriterParameters_HeaderFile
#define _X3D_WriterParameters_HeaderFile

#include <cadex/Base_WriterParameters.hxx>

namespace cadex {

class X3D_WriterParameters : public Base_WriterParameters
{
public:
    __CADEX_EXPORT X3D_WriterParameters();

    __CADEX_EXPORT bool  SaveViewpoint() const;
    __CADEX_EXPORT bool& SaveViewpoint();

    __CADEX_EXPORT bool  WriteNormals() const;
    __CADEX_EXPORT bool& WriteNormals();
};

}

#endif
