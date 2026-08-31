// Copyright (c) 2026 LiamLeo


#include "Box3DStaticCollisionSubsystem.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h" 
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Box3DBody.h"
#include "Box3DShape.h"
#include "Box3DCreationBridge.h"
#include "Helper.h"


bool UBox3DStaticCollisionSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
    return WorldType == EWorldType::Game
        || WorldType == EWorldType::PIE
        || WorldType == EWorldType::Editor
        || WorldType == EWorldType::GamePreview
        || WorldType == EWorldType::Inactive;
}
void UBox3DStaticCollisionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    if(GetWorld()->IsGameWorld())
    {
        WorldInitializedActorsHandle = FWorldDelegates::OnWorldInitializedActors.AddUObject(this, &UBox3DStaticCollisionSubsystem::ActorsInitialized);
    }
    ActorSpawnedDelegateHandle = GetWorld()->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this, &UBox3DStaticCollisionSubsystem::OnActorSpawned));
}

void UBox3DStaticCollisionSubsystem::Deinitialize()
{
    GetWorld()->RemoveOnActorSpawnedHandler(ActorSpawnedDelegateHandle);
    FWorldDelegates::OnWorldInitializedActors.Remove(WorldInitializedActorsHandle);
    Super::Deinitialize();
}

void UBox3DStaticCollisionSubsystem::OnActorSpawned(AActor* SpawnedActor)
{
    TWeakObjectPtr<UBox3DStaticCollisionSubsystem> WeakThis = Cast<UBox3DStaticCollisionSubsystem>(this);
    TWeakObjectPtr<AStaticMeshActor> WeakActor = Cast<AStaticMeshActor>(SpawnedActor);
    GetWorld()->GetTimerManager().SetTimerForNextTick([WeakThis, WeakActor]()
    {
        if(UBox3DStaticCollisionSubsystem* Self = WeakThis.Get())
        {
            if (AStaticMeshActor* ResolvedActor = WeakActor.Get())
            {
                Self->RegisterActor(ResolvedActor);
            }
        }
    });
}

void UBox3DStaticCollisionSubsystem::OnActorDestroyed(AActor* DestroyedActor)
{
    UnRegisterActor(Cast<AStaticMeshActor>(DestroyedActor));
}

void UBox3DStaticCollisionSubsystem::ActorsInitialized(const FActorsInitializedParams& Params)
{
    ScanExistingActors();
}

void UBox3DStaticCollisionSubsystem::ScanExistingActors()
{
    UWorld* World = GetWorld();
    for (TActorIterator<AStaticMeshActor> It(World); It; ++It)
    {
        RegisterActor(*It);
    }
}

#if WITH_EDITOR
void UBox3DStaticCollisionSubsystem::DoUndoAndRedo()
{
    ScanExistingActors();
    for (auto It = ActorsData.CreateIterator(); It; ++It)
    {
        if (!IsValid(It->Key))
        {
            for(FB3BodyHandle BodyHandle: It->Value)
            {
                B3BODY::DestroyBody(BodyHandle);
            }
            It.RemoveCurrent();
        }
    }
}
#endif

void UBox3DStaticCollisionSubsystem::RegisterActor(AStaticMeshActor* Actor)
{
#if WITH_EDITOR
    if (!IsValid(Actor) || Actor->bIsEditorPreviewActor)
    {
        return;
    }
#endif

    if(IsValid(Actor) && !Actor->IsActorBeingDestroyed() && !ActorsData.Contains(Actor))
    {
        TArray<FB3BodyHandle> BodyHandles;
        CreateCollisionForStaticActor(Actor,
            [this, &BodyHandles](UStaticMeshComponent* Comp) -> FB3BodyHandle
            {
                FB3BodyDef BodyDef;
                BodyDef.Position      = Comp->GetComponentLocation();
                BodyDef.Rotation      = Comp->GetComponentQuat();
                return BodyHandles.Add_GetRef(B3CREATE::CreateBody(GetWorld(),BodyDef));
            });
        
        ActorsData.Add(Actor,BodyHandles);
        Actor->OnDestroyed.AddUniqueDynamic(this, &UBox3DStaticCollisionSubsystem::OnActorDestroyed);

#if WITH_EDITOR
        if (GetWorld()->IsEditorWorld())
        {
            if(USceneComponent* Root = Actor->GetRootComponent())
            {
                Root->TransformUpdated.AddUObject(this, &UBox3DStaticCollisionSubsystem::OnActorTransformChanged);
            }
        }
#endif
    }
}
void UBox3DStaticCollisionSubsystem::UnRegisterActor(AStaticMeshActor* Actor)
{
    TArray<FB3BodyHandle> OutBodyHandles;
    if(IsValid(Actor) && ActorsData.RemoveAndCopyValue(Actor, OutBodyHandles))
    {

#if WITH_EDITOR
        if (GetWorld()->IsEditorWorld())
        {
            if (USceneComponent* Root = Actor->GetRootComponent())
            {
                Root->TransformUpdated.RemoveAll(this);
            }
        }
#endif

        Actor->OnDestroyed.RemoveDynamic(this, &UBox3DStaticCollisionSubsystem::OnActorDestroyed);
        for(FB3BodyHandle BodyHandle: OutBodyHandles)
        {
            B3BODY::DestroyBody(BodyHandle);
        }
    }
}


void UBox3DStaticCollisionSubsystem::OnActorTransformChanged(USceneComponent* UpdatedComponent, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport)
{
    AActor* Owner = UpdatedComponent->GetOwner();
    
    if (TArray<FB3BodyHandle>* BodiesOnActor = ActorsData.Find(Owner))
    {
        int32 Index = 0;
        CreateCollisionForStaticActor(Owner, 
            [BodiesOnActor, &Index](UStaticMeshComponent* Comp) -> FB3BodyHandle
            {
                FB3BodyHandle BodyHandle = (*BodiesOnActor)[Index];
                TArray<FB3ShapeHandle> OutHandles;
                B3BODY::SetTransform(BodyHandle,Comp->GetComponentTransform());
                B3BODY::GetShapes(BodyHandle,OutHandles);
                for(FB3ShapeHandle& Handle: OutHandles)
                {
                    B3SHAPE::DestroyShape(Handle,true);
                }

                Index++;
                return BodyHandle;
            });
    }
}

void UBox3DStaticCollisionSubsystem::CreateCollisionForStaticActor( AActor* StaticActor, TFunction<FB3BodyHandle(UStaticMeshComponent*)> BodyHandleOverride)
{
    TArray<UStaticMeshComponent*> MeshComponents;
    StaticActor->GetComponents<UStaticMeshComponent>(MeshComponents);
    FB3ShapeDef ShapeDef;
    for (UStaticMeshComponent* Comp : MeshComponents)
    {
        const FB3BodyHandle& ActiveBodyHandle = BodyHandleOverride(Comp);
        CollisionHelper::CreateCollisionForMesh(GetWorld(), Comp->GetStaticMesh(), ActiveBodyHandle, ShapeDef, FVector3f(Comp->GetComponentScale()));
    }
}