// Copyright (c) 2026 LiamLeo


#include "Box3DStaticMeshComponent.h"
#include "Engine/World.h"
#include "Helper.h"
#include "Box3DTypes.h"
#include "Box3DBody.h"
#include "Box3DShape.h"
#include "Box3DWorld.h"
#include "Box3DJoint.h"
#include "Box3DWorldSubsystem.h"
#include "Box3DCreationBridge.h"


UBox3DStaticMeshComponent::UBox3DStaticMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    bEnableAutoLODGeneration = false; 
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetGenerateOverlapEvents(false);
    SetCanEverAffectNavigation(false);
}
void UBox3DStaticMeshComponent::OnRegister()
{
    Super::OnRegister();
    CreateBody();
    LinkToParent();
    if(!GetStaticMesh())return;
    CreateShape();
}

void UBox3DStaticMeshComponent::OnUnregister()
{
    B3BODY::DestroyBody(BodyHandle);
    Super::OnUnregister();
}

void UBox3DStaticMeshComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBox3DStaticMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UBox3DStaticMeshComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction);
}

bool UBox3DStaticMeshComponent::AttachToComponent(USceneComponent* InParent, const FAttachmentTransformRules& AttachmentRules, FName InSocketName)
{
    bool bSuccess = Super::AttachToComponent(InParent, AttachmentRules, InSocketName);
    if(bSuccess)
    {
        LinkToParent();
    }
    return bSuccess;
}

void UBox3DStaticMeshComponent::DetachFromComponent(const FDetachmentTransformRules& DetachmentRules)
{
    Super::DetachFromComponent(DetachmentRules);
    UnlinkFromParent();
}

bool UBox3DStaticMeshComponent::SetStaticMesh(UStaticMesh* NewMesh)
{
    bool bSuccess = Super::SetStaticMesh(NewMesh);
    if (bSuccess)
    {
        TArray<FB3ShapeHandle> OutHandles;
        B3BODY::GetShapes(BodyHandle,OutHandles);
        for(FB3ShapeHandle& Handle: OutHandles)
        {
            B3SHAPE::DestroyShape(Handle,true);
        }
        if(NewMesh != nullptr)
        {
            CreateShape();
        }
    }
    return bSuccess;
}

FB3BodyHandle UBox3DStaticMeshComponent::GetRigidBodyHandle()
{
    return BodyHandle;
}

void UBox3DStaticMeshComponent::CreateBody()
{
	BodyDef.Position      = GetComponentLocation();
	BodyDef.Rotation      = GetComponentQuat();
	BodyUserData.Object   = this;
	BodyUserData.MoveCallback = &UBox3DStaticMeshComponent::BodyMoveCallback;
	BodyDef.UserData      = &BodyUserData;
	BodyHandle            = B3CREATE::CreateBody(GetWorld(), BodyDef);
}

void UBox3DStaticMeshComponent::CreateShape()
{
	ShapeUserData.Object               = this;
	ShapeUserData.BeginOverlapCallback = &UBox3DStaticMeshComponent::BeginCallback;
	ShapeUserData.EndOverlapCallback   = &UBox3DStaticMeshComponent::EndCallback;
	ShapeDef.UserData                  = &ShapeUserData;
	CollisionHelper::CreateCollisionForMesh(GetWorld(), GetStaticMesh(), BodyHandle, ShapeDef, FVector3f(GetComponentScale()));
}



// Welding Unwelding of child and parent
bool UBox3DStaticMeshComponent::LinkToParent()
{
	if(IsRegistered())
	{
        if( B3JOINT::IsValid(WeldJointHandle))
        {
            B3JOINT::DestroyJoint(WeldJointHandle, true);
        }
        if(UBox3DStaticMeshComponent* Parent = Cast<UBox3DStaticMeshComponent>(GetAttachParent()))
        {
            FB3JointDef     JointDef;
            FB3WeldJointDef WeldJointDef;
            JointDef.LocationB   = FVector3f(this->GetRelativeLocation());
            JointDef.RotationB   = FRotator3f(this->GetRelativeRotation());
            JointDef.BodyHandleA = Parent->GetRigidBodyHandle();
            JointDef.BodyHandleB = BodyHandle;
            B3BODY::SetTransform(BodyHandle, Parent->GetComponentTransform() * this->GetRelativeTransform());
            WeldJointHandle = B3CREATE::CreateWeldJoint(GetWorld(), JointDef, WeldJointDef);
            return bool(WeldJointHandle);
        }
    }
    return false;
}

void UBox3DStaticMeshComponent::UnlinkFromParent()
{
    if (IsRegistered() && B3JOINT::IsValid(WeldJointHandle))
    {
        B3JOINT::DestroyJoint(WeldJointHandle, true);
        B3BODY::SetTransform(BodyHandle, GetComponentTransform());
    }
}




void UBox3DStaticMeshComponent::BodyMoveCallback(FB3BodyUserData* BodyUserData, UObject* Object, const FTransform& Transform)
{
    static_cast<UBox3DStaticMeshComponent*>(Object)->SetWorldLocationAndRotation(Transform.GetLocation(),Transform.GetRotation(),false,nullptr,ETeleportType::TeleportPhysics);
}

void UBox3DStaticMeshComponent::BeginCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent)
{
    auto* Component = static_cast<UBox3DStaticMeshComponent*>(Object);
    if(Component->OnBeginOverlap.IsBound())
    {
        FB3BodyHandle SensorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.SensorShapeHandle));
        FB3BodyHandle VisitorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.VisitorShapeHandle));
        Component->OnBeginOverlap.Broadcast( SensorBodyHandle, SensorTouchEvent.SensorShapeHandle, VisitorBodyHandle, SensorTouchEvent.VisitorShapeHandle);
    }
}

void UBox3DStaticMeshComponent::EndCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent)
{
    auto* Component = static_cast<UBox3DStaticMeshComponent*>(Object);
    if(Component->OnEndOverlap.IsBound())
    {
        FB3BodyHandle SensorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.SensorShapeHandle));
        FB3BodyHandle VisitorBodyHandle = FB3BodyHandle(B3SHAPE::GetBody(SensorTouchEvent.VisitorShapeHandle));
        Component->OnEndOverlap.Broadcast( SensorBodyHandle, SensorTouchEvent.SensorShapeHandle, VisitorBodyHandle, SensorTouchEvent.VisitorShapeHandle);
    }
}




#if WITH_EDITOR

void UBox3DStaticMeshComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    const FName PropertyName = PropertyChangedEvent.GetPropertyName();
    const FName MemberName = PropertyChangedEvent.GetMemberPropertyName();
    if (PropertyName == GET_MEMBER_NAME_CHECKED(USceneComponent, Mobility))
    {
        switch (GetMobility())
        {
            case EComponentMobility::Static:
                BodyDef.Type = EB3BodyType::Static;
                break;
            case EComponentMobility::Stationary:
                BodyDef.Type = EB3BodyType::Static;
                break;
            case EComponentMobility::Movable:
                BodyDef.Type = BodyDef.Type == EB3BodyType::Static || BodyDef.Type == EB3BodyType::Kinematic?EB3BodyType::Kinematic:EB3BodyType::Dynamic;
                break;
        }
    }
}

#endif