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


#ifndef _ModelData_DrawingDimension_HeaderFile
#define _ModelData_DrawingDimension_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_DRAWINGS

#include <cadex/ModelData_DrawingElement.hxx>

namespace cadex {
class ModelData_Point2d;

namespace internal {
class ModelData_DrawingAngularDimensionImpl;
class ModelData_DrawingDiametricDimensionImpl;
class ModelData_DrawingDimensionImpl;
class ModelData_DrawingLinearDimensionImpl;
class ModelData_DrawingRadialDimensionImpl;
}

class ModelData_DrawingDimension : public ModelData_DrawingElement
{
public:

    enum TextVerticalPositionType
    {
        Above,
        Centered,
        Below
    };

    enum TextHorizontalPositionType
    {
        Left,
        Center,
        Right
    };

    enum ArrowheadPlacementType
    {
        Internal,
        External
    };

    __CADEX_EXPORT TextVerticalPositionType TextVerticalPosition() const;
    __CADEX_EXPORT void SetTextVerticalPosition (TextVerticalPositionType theTextVerticalPosition);

    __CADEX_EXPORT TextHorizontalPositionType TextHorizontalPosition() const;
    __CADEX_EXPORT void SetTextHorizontalPosition (TextHorizontalPositionType theTextHorizontalPosition);

    __CADEX_EXPORT ArrowheadPlacementType ArrowheadPlacement() const;
    __CADEX_EXPORT void SetArrowheadPlacement (ArrowheadPlacementType theArrowheadPlacement);

    __CADEX_EXPORT bool AlignTextHorizontally() const;
    __CADEX_EXPORT void SetAlignTextHorizontally (bool theAlignTextHorizontally);

    __CADEX_EXPORT double MeasurementValue() const;
    __CADEX_EXPORT void SetMeasurementValue (double theMeasurementValue);

protected:

    typedef cadex::internal:: ModelData_DrawingDimensionImpl ImplType;

    explicit ModelData_DrawingDimension (ImplType *);
};

class ModelData_DrawingAngularDimension : public ModelData_DrawingDimension
{
public:
    typedef cadex::internal::ModelData_DrawingAngularDimensionImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingAngularDimension();
    __CADEX_EXPORT explicit ModelData_DrawingAngularDimension (ImplType*);
    __CADEX_EXPORT ModelData_DrawingAngularDimension (const ModelData_Point2d& theAnglePoint,
                                                      const ModelData_Point2d& theFirstReferencePoint,
                                                      const ModelData_Point2d& theSecondReferencePoint,
                                                      const ModelData_Point2d& theDimensionArcPoint,
                                                      double theMeasurementValue);

    __CADEX_EXPORT const ModelData_Point2d& AnglePoint() const;
    __CADEX_EXPORT void SetAnglePoint (const ModelData_Point2d& theAnglePoint);

    __CADEX_EXPORT const ModelData_Point2d& FirstReferencePoint() const;
    __CADEX_EXPORT void SetFirstReferencePoint (const ModelData_Point2d& theFirstReferencePoint);

    __CADEX_EXPORT const ModelData_Point2d& SecondReferencePoint() const;
    __CADEX_EXPORT void SetSecondReferencePoint (const ModelData_Point2d& theSecondReferencePoint);

    __CADEX_EXPORT const ModelData_Point2d& DimensionArcPoint() const;
    __CADEX_EXPORT void SetDimensionArcPoint (const ModelData_Point2d& theDimensionArcPoint);

    __CADEX_MODELDATA_DEFINE_TYPEID
};

class ModelData_DrawingDiametricDimension : public ModelData_DrawingDimension
{
public:
    typedef cadex::internal::ModelData_DrawingDiametricDimensionImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingDiametricDimension();
    __CADEX_EXPORT explicit ModelData_DrawingDiametricDimension (ImplType*);
    __CADEX_EXPORT ModelData_DrawingDiametricDimension (const ModelData_Point2d& theFirstChordPoint,
                                                        const ModelData_Point2d& theSecondChordPoint,
                                                        const ModelData_Point2d& theDimensionEndPoint,
                                                        double theMeasurementValue);

    __CADEX_EXPORT const ModelData_Point2d& FirstChordPoint() const;
    __CADEX_EXPORT void SetFirstChordPoint (const ModelData_Point2d& theFirstChordPoint);

    __CADEX_EXPORT const ModelData_Point2d& SecondChordPoint() const;
    __CADEX_EXPORT void SetSecondChordPoint (const ModelData_Point2d& theSecondChordPoint);

    __CADEX_EXPORT const ModelData_Point2d& DimensionEndPoint() const;
    __CADEX_EXPORT void SetDimensionEndPoint (const ModelData_Point2d& theDimensionEndPoint);

    __CADEX_EXPORT bool StartsFromCenter() const;
    __CADEX_EXPORT void SetStartsFromCenter (bool theStartsFromCenter);

    __CADEX_MODELDATA_DEFINE_TYPEID
};

class ModelData_DrawingRadialDimension : public ModelData_DrawingDimension
{
public:
    typedef cadex::internal::ModelData_DrawingRadialDimensionImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingRadialDimension();
    __CADEX_EXPORT explicit ModelData_DrawingRadialDimension (ImplType*);
    __CADEX_EXPORT ModelData_DrawingRadialDimension (const ModelData_Point2d& theCenterPoint,
                                                     const ModelData_Point2d& theChordPoint,
                                                     const ModelData_Point2d& theDimensionEndPoint,
                                                     double theMeasurementValue);

    __CADEX_EXPORT const ModelData_Point2d& CenterPoint() const;
    __CADEX_EXPORT void SetCenterPoint (const ModelData_Point2d& theCenterPoint);

    __CADEX_EXPORT const ModelData_Point2d& ChordPoint() const;
    __CADEX_EXPORT void SetChordPoint (const ModelData_Point2d& theChordPoint);

    __CADEX_EXPORT const ModelData_Point2d& DimensionEndPoint() const;
    __CADEX_EXPORT void SetDimensionEndPoint (const ModelData_Point2d& theDimensionEndPoint);

    __CADEX_EXPORT bool StartsFromCenter() const;
    __CADEX_EXPORT void SetStartsFromCenter (bool theStartsFromCenter) const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};

class ModelData_DrawingLinearDimension : public ModelData_DrawingDimension
{
public:

    enum RotationType
    {
        Horizontal,
        Vertical,
        Aligned
    };

    typedef cadex::internal::ModelData_DrawingLinearDimensionImpl ImplType;

    __CADEX_EXPORT ModelData_DrawingLinearDimension();
    __CADEX_EXPORT explicit ModelData_DrawingLinearDimension (ImplType*);
    __CADEX_EXPORT ModelData_DrawingLinearDimension (const ModelData_Point2d& theFirstReferencePoint,
                                                     const ModelData_Point2d& theSecondReferencePoint,
                                                     const ModelData_Point2d& theDimensionLinePoint,
                                                     double theMeasurementValue,
                                                     RotationType theRotation = Horizontal);

    __CADEX_EXPORT const ModelData_Point2d& FirstReferencePoint() const;
    __CADEX_EXPORT void SetFirstReferencePoint (const ModelData_Point2d& theFirstReferencePoint);

    __CADEX_EXPORT const ModelData_Point2d& SecondReferencePoint() const;
    __CADEX_EXPORT void SetSecondReferencePoint (const ModelData_Point2d& theSecondReferencePoint);

    __CADEX_EXPORT const ModelData_Point2d& DimensionLinePoint() const;
    __CADEX_EXPORT void SetDimensionLinePoint (const ModelData_Point2d& theDimensionLinePoint);

    __CADEX_EXPORT RotationType Rotation() const;
    __CADEX_EXPORT void SetRotation (RotationType theRotation);

    __CADEX_MODELDATA_DEFINE_TYPEID
};

}

#endif
#endif
