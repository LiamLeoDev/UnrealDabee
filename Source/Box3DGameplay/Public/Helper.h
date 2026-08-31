// Copyright (c) 2026 LiamLeo


#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/BodySetup.h"
#include "Box3DTypes.h"

namespace CollisionHelper
{
    ECollisionTraceFlag GetCollisionComplexity(UBodySetup* BodySetup);
    void GetMeshDef(UBodySetup* BodySetup, FB3MeshDef& MeshDefOut);
    void CreateCollisionForMesh(UWorld* World, UStaticMesh* StaticMesh,  const FB3BodyHandle& BodyHandle, FB3ShapeDef& ShapeDef,const FVector3f& ComponentScale, TArray<FB3ShapeHandle>* OutShapeHandles = nullptr);
}
