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


#ifndef _IGES_WriterParameters_HeaderFile
#define _IGES_WriterParameters_HeaderFile

#include <cadex/Base_WriterParameters.hxx>

namespace cadex {

class IGES_WriterParameters : public Base_WriterParameters
{
public:
    enum VersionType {
        V2 = 2
    };
    enum WriteModeType {
        BoundedSurfaces,
        MSBO
    };

    __CADEX_EXPORT IGES_WriterParameters();

     __CADEX_EXPORT VersionType  Version() const;
     __CADEX_EXPORT VersionType& Version();

    __CADEX_EXPORT WriteModeType WriteMode() const;
    __CADEX_EXPORT WriteModeType& WriteMode();
};

}

#endif
