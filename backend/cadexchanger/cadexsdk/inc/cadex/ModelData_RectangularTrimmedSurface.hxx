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


#ifndef _ModelData_RectangularTrimmedSurface_HeaderFile
#define _ModelData_RectangularTrimmedSurface_HeaderFile

#include <cadex/ModelData_Surface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_RectangularTrimmedSurface)

namespace cadex {
namespace internal {
class ModelData_RectangularTrimmedSurfaceImpl;
}

class ModelData_RectangularTrimmedSurface : public ModelData_Surface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_RectangularTrimmedSurfaceImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_RectangularTrimmedSurface() {}

    __CADEX_EXPORT ModelData_RectangularTrimmedSurface (
        const ModelData_Surface& theBasisSurface, double U1, double U2, double V1, double V2);

    __CADEX_EXPORT ModelData_RectangularTrimmedSurface (
        const ModelData_Surface& theBasisSurface, double theParameter1, double theParameter2, bool theIsUTrim);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_RectangularTrimmedSurface,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_RectangularTrimmedSurface,Geom_RectangularTrimmedSurface)

    __CADEX_EXPORT ModelData_Surface BasisSurface() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_RectangularTrimmedSurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif
