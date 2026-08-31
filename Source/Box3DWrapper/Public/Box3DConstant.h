// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Box3DConstant.generated.h"


UCLASS()
class BOX3DWRAPPER_API UBox3DConstant : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void SetLengthUnitsPerMeter( float LengthUnits );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Length Unit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Constant")
	static float GetLengthUnitsPerMeter();
};

#define B3CONST UBox3DConstant