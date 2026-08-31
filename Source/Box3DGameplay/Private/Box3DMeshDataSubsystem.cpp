// Copyright (c) 2026 LiamLeo

#include "Box3DMeshDataSubsystem.h"
#include "EngineUtils.h"
#include "Box3DShape.h"
#include "Helper.h"
#include "Box3DCreationBridge.h"
#include "Box3DCollision.h"
#include "PhysicsEngine/BodySetup.h"
#include "Engine/StaticMesh.h"

bool UBox3DMeshDataSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
    return WorldType == EWorldType::Game
        || WorldType == EWorldType::PIE
        || WorldType == EWorldType::Editor
        || WorldType == EWorldType::EditorPreview
        || WorldType == EWorldType::GamePreview
        || WorldType == EWorldType::Inactive;

}
void UBox3DMeshDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UBox3DMeshDataSubsystem::Deinitialize()
{
    for (auto& Pair : ComplexMeshesRegistry)
    {
        B3COLLISION::DestroyMesh(&Pair.Value);
    }
    ComplexMeshesRegistry.Empty();
    Super::Deinitialize();
}

FB3MeshData* UBox3DMeshDataSubsystem::RegisterAndGetMeshData(UStaticMesh* StaticMesh)
{
    if(!IsValid(StaticMesh))
    {
        return nullptr;
    }
    if (FB3MeshData* MeshData = ComplexMeshesRegistry.Find(TWeakObjectPtr<UStaticMesh>(StaticMesh)))
    {
        return MeshData;
    }
    UBodySetup* BodySetup = StaticMesh->GetBodySetup();
    if (IsValid(BodySetup))
    {
        FB3MeshDef MeshDefOut;
        CollisionHelper::GetMeshDef(BodySetup, MeshDefOut);
        FB3MeshData MeshData = B3CREATE::CreateMeshData(MeshDefOut);
        if(MeshData.GetData())
        {
            return &ComplexMeshesRegistry.Add(TWeakObjectPtr<UStaticMesh>(StaticMesh), MeshData);
        }
    }
    return nullptr;
}
