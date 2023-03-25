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


#ifndef _ModelPrs_ManipulatorMode_HeaderFile
#define _ModelPrs_ManipulatorMode_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION

namespace cadex {

enum ModelPrs_ManipulatorMode
{
    ModelPrs_MM_None        = 0x00,
    ModelPrs_MM_Translation = 0x01,
    ModelPrs_MM_Rotation    = 0x02
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_ManipulatorMode_HeaderFile
