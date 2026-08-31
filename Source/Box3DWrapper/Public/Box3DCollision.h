// Copyright (c) 2026 LiamLeo

#pragma once

#include "Box3DTypes.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Box3DCollision.generated.h"


UCLASS()
class BOX3DWRAPPER_API UBox3DCollision : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

    static void DestroyMesh(FB3MeshData* MeshData);

};

#define B3COLLISION UBox3DCollision