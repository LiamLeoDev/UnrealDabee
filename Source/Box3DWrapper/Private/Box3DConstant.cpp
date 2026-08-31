// Copyright (c) 2026 LiamLeo


#include "Box3DConstant.h"
#include "box3d/constants.h"
#include "Box3DAsserts.h"

void UBox3DConstant::SetLengthUnitsPerMeter( float LengthUnits )
{
    b3SetLengthUnitsPerMeter(LengthUnits);
}
float UBox3DConstant::GetLengthUnitsPerMeter()
{
    return b3GetLengthUnitsPerMeter();
}