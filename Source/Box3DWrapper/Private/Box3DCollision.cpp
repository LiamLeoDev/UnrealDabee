// Copyright (c) 2026 LiamLeo

#include "Box3DCollision.h"
#include "box3d/collision.h"
#include "Box3DAsserts.h"

void UBox3DCollision::DestroyMesh(FB3MeshData* MeshData)
{
    B3_ENSURE_MSG_RET(MeshData,, TEXT("DestroyMesh called wih an invalid Mesh Data")); 
    B3_ENSURE_MSG_RET(MeshData->GetData(),, TEXT("DestroyMesh The data inside MeshData is invalid")); 
    if(MeshData && MeshData->GetData())
    {
        b3DestroyMesh(MeshData->GetData());
    }
    MeshData = nullptr;
}
