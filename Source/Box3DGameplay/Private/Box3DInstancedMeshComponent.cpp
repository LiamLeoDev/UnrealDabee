// Copyright (c) 2026 LiamLeo


#include "Box3DInstancedMeshComponent.h"
#include "Engine/World.h"
#include "Helper.h"
#include "Box3DBody.h"
#include "Box3DShape.h"
#include "Box3DWorld.h"
#include "Box3DJoint.h"
#include "Box3DWorldSubsystem.h"
#include "Box3DCreationBridge.h"

UBox3DInstancedMeshComponent::UBox3DInstancedMeshComponent()
{
    PrimaryComponentTick.bStartWithTickEnabled = true;
    PrimaryComponentTick.bCanEverTick = false;
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetGenerateOverlapEvents(false);
    SetCanEverAffectNavigation(false);
    NumCustomDataFloats = 1;
    bSupportRemoveAtSwap = true;
}

void UBox3DInstancedMeshComponent::BeginPlay()
{
    Super::BeginPlay();
    if(auto* Box3DSubsystem = GetWorld()->GetSubsystem<UBox3DWorldSubsystem>())
    {
        Box3DSubsystem->OnBodiesUpdated.AddUObject(this, &UBox3DInstancedMeshComponent::BodiesUpdatedCallback);
    }
}

void UBox3DInstancedMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UBox3DInstancedMeshComponent::OnRegister()
{
    Super::OnRegister();
    if(GetStaticMesh() && GetWorld() && GetWorld()->IsGameWorld())
    {
        ClearInstances();
        const int32 TotalCount = GridDim.X * GridDim.Y * GridDim.Z;
        InstancesData.Reserve(TotalCount);
        for (int32 X = 0; X < GridDim.X; ++X)
        {
            for (int32 Y = 0; Y < GridDim.Y; ++Y)
            {
                for (int32 Z = 0; Z < GridDim.Z; ++Z)
                {
                    const FVector Location = ((FVector(X, Y, Z)-FVector(GridDim.X*0.5, GridDim.Y*0.5, 0)) * GridSpacing);
                    FTransform InstanceTransform(FRotator::ZeroRotator, Location, (FMath::VRand()*0.7).GetAbs()+0.3);
                    const int32 InstanceIndex = AddInstance(InstanceTransform);
                }
            }
        }
    }
}

void UBox3DInstancedMeshComponent::CreateBodyAndCollisionForInstance(int32 InstanceIndex, FTransform InstanceTransform)
{
    const int32 Slot = InstancesData.Add(FB3InstanceData());
    SetCustomDataValue(InstanceIndex, 0, static_cast<float>(Slot), false);
    FB3InstanceData& CurrentInstance = InstancesData[Slot];
    CurrentInstance.BodyUserData.Object = this;
    CurrentInstance.BodyUserData.MoveCallback = &UBox3DInstancedMeshComponent::BodyMoveCallback;
    CurrentInstance.BodyUserData.StableSlot = Slot;
    CurrentInstance.BodyUserData.InstanceIndex = InstanceIndex;

    CurrentInstance.ShapeUserData.Object = this;
    CurrentInstance.ShapeUserData.BeginOverlapCallback = &UBox3DInstancedMeshComponent::BeginCallback;
    CurrentInstance.ShapeUserData.EndOverlapCallback = &UBox3DInstancedMeshComponent::EndCallback;

    BodyDef.Position = InstanceTransform.GetLocation();
    BodyDef.Rotation = InstanceTransform.GetRotation();
    BodyDef.UserData = &CurrentInstance.BodyUserData;
    ShapeDef.UserData = &CurrentInstance.ShapeUserData;

    CurrentInstance.BodyHandle = B3CREATE::CreateBody(GetWorld(), BodyDef);
    CollisionHelper::CreateCollisionForMesh(GetWorld(), GetStaticMesh(), CurrentInstance.BodyHandle, ShapeDef, FVector3f(InstanceTransform.GetScale3D()));
}

void UBox3DInstancedMeshComponent::OnUnregister()
{
    for (FB3InstanceData& Instance : InstancesData)
    {
        B3BODY::DestroyBody(Instance.BodyHandle);
    }
    ClearInstances();
    InstancesData.Empty();
    Super::OnUnregister();
}

int32 UBox3DInstancedMeshComponent::AddInstance(const FTransform& InstanceTransform, bool bWorldSpace)
{
    const int32 InstanceIndex = Super::AddInstance(InstanceTransform, bWorldSpace);

    if (InstanceIndex != INDEX_NONE)
    {
        const FTransform WorldTransform = bWorldSpace ? InstanceTransform : (InstanceTransform * GetComponentTransform());
        CreateBodyAndCollisionForInstance(InstanceIndex, WorldTransform);
    }

    return InstanceIndex;
}

// Callbacks
void UBox3DInstancedMeshComponent::BodyMoveCallback(FB3BodyUserData* BodyUserData, UObject* Object, const FTransform& Transform)
{
    auto* InstancedData = static_cast<FB3InstancedBodyUserData*>(BodyUserData);
    auto* InstancedComponent = static_cast<UBox3DInstancedMeshComponent*>(Object);
    FTransform InstanceTransform;
	if(InstancedComponent->GetInstanceTransform(InstancedData->InstanceIndex, InstanceTransform, true))
	{
		InstanceTransform.SetLocation(Transform.GetLocation());
		InstanceTransform.SetRotation(Transform.GetRotation());
		InstancedComponent->UpdateInstanceTransform(InstancedData->InstanceIndex, InstanceTransform, true, false, true);
	}
}

void UBox3DInstancedMeshComponent::BeginCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent)
{
    auto* Component = static_cast<UBox3DInstancedMeshComponent*>(Object);
    if(Component->OnBeginOverlap.IsBound())
    {
        FB3BodyHandle SensorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.SensorShapeHandle));
        FB3BodyHandle VisitorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.VisitorShapeHandle));
        Component->OnBeginOverlap.Broadcast( SensorBodyHandle, SensorTouchEvent.SensorShapeHandle, VisitorBodyHandle, SensorTouchEvent.VisitorShapeHandle);
    }
}

void UBox3DInstancedMeshComponent::EndCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent)
{
    auto* Component = static_cast<UBox3DInstancedMeshComponent*>(Object);
    if(Component->OnEndOverlap.IsBound())
    {
        FB3BodyHandle SensorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.SensorShapeHandle));
        FB3BodyHandle VisitorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.VisitorShapeHandle));
        Component->OnEndOverlap.Broadcast( SensorBodyHandle, SensorTouchEvent.SensorShapeHandle, VisitorBodyHandle, SensorTouchEvent.VisitorShapeHandle);
    }
}


void UBox3DInstancedMeshComponent::BodiesUpdatedCallback()
{
    MarkRenderStateDirty();
}
