// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Box3DTypes.h"
#include "Box3DMeshDataSubsystem.generated.h"

UCLASS(NotBlueprintable)
class BOX3DGAMEPLAY_API UBox3DMeshDataSubsystem final: public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
    FB3MeshData* RegisterAndGetMeshData(UStaticMesh* StaticMesh);
private:
    TMap<TWeakObjectPtr<UStaticMesh>, FB3MeshData> ComplexMeshesRegistry;
};