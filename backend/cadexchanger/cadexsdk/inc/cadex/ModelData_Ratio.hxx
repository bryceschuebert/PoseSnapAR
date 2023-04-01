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


#ifndef _ModelData_Ratio_HeaderFile
#define _ModelData_Ratio_HeaderFile

namespace cadex {

class ModelData_Ratio
{
public:
    __CADEX_EXPORT ModelData_Ratio();
    __CADEX_EXPORT ModelData_Ratio (size_t theNumerator, size_t theDenominator);

    __CADEX_EXPORT size_t Numerator() const;
    __CADEX_EXPORT void SetNumerator (size_t theNumerator);
    __CADEX_EXPORT size_t Denominator() const;
    __CADEX_EXPORT void SetDenominator (size_t theDenominator);

    __CADEX_EXPORT double ToDouble() const;

    __CADEX_EXPORT bool operator== (const ModelData_Ratio& theOther) const;
    __CADEX_EXPORT bool operator!= (const ModelData_Ratio& theOther) const;

private:
    size_t myValue[2];
};

}

#endif
