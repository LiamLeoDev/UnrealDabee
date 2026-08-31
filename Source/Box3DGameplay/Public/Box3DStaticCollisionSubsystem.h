// Copyright (c) 2026 LiamLeo


#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Box3DTypes.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "Box3DStaticCollisionSubsystem.generated.h"

UCLASS(NotBlueprintable)
class BOX3DGAMEPLAY_API UBox3DStaticCollisionSubsystem final: public UWorldSubsystem
{
    GENERATED_BODY()

public: 
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

private:
    UFUNCTION()
    void OnActorDestroyed(AActor* DestroyedActor);
    void OnActorSpawned(AActor* SpawnedActor);
    void OnActorTransformChanged(USceneComponent* UpdatedComponent, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);

    void RegisterActor(AStaticMeshActor* Actor);
    void UnRegisterActor(AStaticMeshActor* Actor);
    
    void ActorsInitialized(const FActorsInitializedParams& Params);
    FDelegateHandle ActorSpawnedDelegateHandle;
    FDelegateHandle WorldInitializedActorsHandle;
    TMap<AActor*, TArray<FB3BodyHandle>> ActorsData;

    void CreateCollisionForStaticActor(AActor* StaticActor, TFunction<FB3BodyHandle(UStaticMeshComponent*)> BodyHandleOverride);


public:
    void ScanExistingActors();
#if WITH_EDITOR
    void DoUndoAndRedo();
#endif
};