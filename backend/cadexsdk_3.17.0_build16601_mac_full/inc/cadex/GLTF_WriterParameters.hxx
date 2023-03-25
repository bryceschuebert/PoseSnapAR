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


#ifndef _GLTF_WriterParameters_HeaderFile
#define _GLTF_WriterParameters_HeaderFile

#include <cadex/Base_WriterParameters.hxx>

namespace cadex {

class GLTF_WriterParameters : public Base_WriterParameters
{
public:
    enum GLTFFormatType {
        GLTF,
        GLB
    };
    __CADEX_EXPORT GLTF_WriterParameters();

    __CADEX_EXPORT GLTFFormatType GLTFFormat() const;
    __CADEX_EXPORT GLTFFormatType& GLTFFormat();
};

}

#endif
