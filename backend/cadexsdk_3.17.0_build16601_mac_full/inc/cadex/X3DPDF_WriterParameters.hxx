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


#ifndef _X3DPDF_WriterParameters_HeaderFile
#define _X3DPDF_WriterParameters_HeaderFile

#include <cadex/Base_WriterParameters.hxx>

namespace cadex {

class X3DPDF_WriterParameters : public Base_WriterParameters
{
public:
       
    enum PaperSizeType
    {
        A0,
        A1,
        A2,
        A3,
        A4
    };

    enum PaperOrientationType
    {
        Landscape,
        Portrait
    };

    __CADEX_EXPORT X3DPDF_WriterParameters();

    __CADEX_EXPORT void SetPaperSize (PaperSizeType thePaperSize);
    __CADEX_EXPORT PaperSizeType PaperSize() const;

    __CADEX_EXPORT void SetPaperOrientation (PaperOrientationType theOrientation);
    __CADEX_EXPORT PaperOrientationType PaperOrientation() const;

    __CADEX_EXPORT void SetAddWatermark (bool theAddWatermark);
    __CADEX_EXPORT bool AddWatermark() const;
};

}

#endif
