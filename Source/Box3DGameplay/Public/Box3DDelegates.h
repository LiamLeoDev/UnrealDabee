// Copyright (c) 2026 LiamLeo


#pragma once

#include "CoreMinimal.h"
#include "Box3DTypes.h" 
#include "Box3DDelegates.generated.h"


UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
    FB3OnBeginOverlap,
    FB3BodyHandle, SensorBodyHandle,
    FB3ShapeHandle, SensorShapeHandle,
    FB3BodyHandle, VisitorBodyHandle,
    FB3ShapeHandle, VisitorShapeHandle
);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
    FB3OnEndOverlap,
    FB3BodyHandle, SensorBodyHandle,
    FB3ShapeHandle, SensorShapeHandle,
    FB3BodyHandle, VisitorBodyHandle,
    FB3ShapeHandle, VisitorShapeHandle
);
