// Copyright (c) 2026 LiamLeo


#include "Box3DBody.h"
#include "Box3DTypes.h"
#include "box3d/box3d.h"
#include "Box3DAsserts.h"

void UBox3DBody::DestroyBody(FB3BodyHandle& BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("DestroyBody called wih an invalid Body Handle")); 
    b3DestroyBody(BodyHandle.GetID());
    BodyHandle = FB3BodyHandle(b3_nullBodyId);
}
bool UBox3DBody::IsValid(const FB3BodyHandle BodyHandle)
{
    return bool(BodyHandle);
}
void UBox3DBody::SetType(const FB3BodyHandle BodyHandle,const EB3BodyType Type)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetType called wih an invalid Body Handle")); 
    b3Body_SetType(BodyHandle.GetID(), ToNative(Type));
}
void UBox3DBody::SetName(const FB3BodyHandle BodyHandle, const FName& Name)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetName called wih an invalid Body Handle")); 
    b3Body_SetName( BodyHandle.GetID(),Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*Name.ToString()));
}
FName UBox3DBody::GetName(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FName(TEXT("")), TEXT("GetName called wih an invalid Body Handle")); 
    return FName(UTF8_TO_TCHAR(b3Body_GetName(BodyHandle.GetID())));
}
UObject* UBox3DBody::BP_GetUserData(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, nullptr, TEXT("BP_GetUserData called wih an invalid Body Handle")); 
    if(FB3BodyUserData* UserData = GetUserData(BodyHandle))
    {
        return UserData->Object.Get();
    }
    return nullptr;
}
FB3BodyUserData* UBox3DBody::GetUserData(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, nullptr, TEXT("GetUserData called wih an invalid Body Handle")); 
    return static_cast<FB3BodyUserData*>(b3Body_GetUserData(BodyHandle.GetID()));
}
void UBox3DBody::SetUserData(const FB3BodyHandle BodyHandle, FB3BodyUserData* UserData)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetUserData called wih an invalid Body Handle")); 
    b3Body_SetUserData(BodyHandle.GetID(), UserData);
}
EB3BodyType UBox3DBody::GetType(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, EB3BodyType::None, TEXT("GetType called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetType(BodyHandle.GetID()));
}

FVector UBox3DBody::GetPosition(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector::ZeroVector, TEXT("GetPosition called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetPosition(BodyHandle.GetID()));
}

FQuat4f UBox3DBody::GetRotation(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FQuat4f::Identity, TEXT("GetRotation called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetRotation(BodyHandle.GetID()));
}

FTransform UBox3DBody::GetTransform(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FTransform::Identity, TEXT("GetTransform called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetTransform(BodyHandle.GetID()));
}

void UBox3DBody::SetTransform(const FB3BodyHandle BodyHandle,const FTransform& Transform)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetTransform called wih an invalid Body Handle")); 
    b3Body_SetTransform(BodyHandle.GetID(), ToNativePos(Transform.GetLocation()), ToNative(Transform.GetRotation()));
}

FVector3f UBox3DBody::GetLocalPoint(const FB3BodyHandle BodyHandle,const FVector& WorldPoint)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetLocalPoint called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetLocalPoint(BodyHandle.GetID(), ToNativePos(WorldPoint)));
}

FVector UBox3DBody::GetWorldPoint(const FB3BodyHandle BodyHandle,const FVector3f& LocalPoint)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector::ZeroVector, TEXT("GetWorldPoint called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetWorldPoint(BodyHandle.GetID(), ToNativeVec(LocalPoint)));
}

FVector3f UBox3DBody::GetLocalVector(const FB3BodyHandle BodyHandle,const FVector3f& WorldVector)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetLocalVector called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetLocalVector(BodyHandle.GetID(), ToNativeVec(WorldVector)));
}

FVector3f UBox3DBody::GetWorldVector(const FB3BodyHandle BodyHandle,const FVector3f& LocalVector)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetWorldVector called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetWorldVector(BodyHandle.GetID(), ToNativeVec(LocalVector)));
}

FVector3f UBox3DBody::GetLinearVelocity(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetLinearVelocity called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetLinearVelocity(BodyHandle.GetID()));
}

void UBox3DBody::SetLinearVelocity(const FB3BodyHandle BodyHandle,const FVector3f& Velocity)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetLinearVelocity called wih an invalid Body Handle")); 
    b3Body_SetLinearVelocity(BodyHandle.GetID(), ToNativeVec(Velocity));
}

FVector3f UBox3DBody::GetAngularVelocity(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetAngularVelocity called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetAngularVelocity(BodyHandle.GetID()));
}

void UBox3DBody::SetAngularVelocity(const FB3BodyHandle BodyHandle,const FVector3f& Velocity)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetAngularVelocity called wih an invalid Body Handle")); 
    b3Body_SetAngularVelocity(BodyHandle.GetID(), ToNativeVec(Velocity));
}

void UBox3DBody::SetTargetTransform(const FB3BodyHandle BodyHandle,const FTransform& Transform, float TimeStep, bool Wake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetTargetTransform called wih an invalid Body Handle")); 
    b3Body_SetTargetTransform(BodyHandle.GetID(), ToNativeWorldTransform(Transform), TimeStep, Wake);
}

FVector3f UBox3DBody::GetLocalPointVelocity(const FB3BodyHandle BodyHandle,const FVector3f& LocalPoint)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetLocalPointVelocity called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetLocalPointVelocity(BodyHandle.GetID(), ToNativeVec(LocalPoint)));
}

FVector3f UBox3DBody::GetWorldPointVelocity(const FB3BodyHandle BodyHandle,const FVector& WorldPoint)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetWorldPointVelocity called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetWorldPointVelocity(BodyHandle.GetID(), ToNativePos(WorldPoint)));
}

void UBox3DBody::ApplyForce(const FB3BodyHandle BodyHandle,const FVector3f& Force,const FVector& Point, bool Wake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("ApplyForce called wih an invalid Body Handle")); 
    b3Body_ApplyForce(BodyHandle.GetID(), ToNativeVec(Force), ToNativePos(Point), Wake);
}

void UBox3DBody::ApplyForceToCenter(const FB3BodyHandle BodyHandle,const FVector3f& Force, bool Wake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("ApplyForceToCenter called wih an invalid Body Handle")); 
    b3Body_ApplyForceToCenter(BodyHandle.GetID(), ToNativeVec(Force), Wake);
}

void UBox3DBody::ApplyTorque(const FB3BodyHandle BodyHandle,const FVector3f& Torque, bool Wake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("ApplyTorque called wih an invalid Body Handle")); 
    b3Body_ApplyTorque(BodyHandle.GetID(), ToNativeVec(Torque), Wake);
}

void UBox3DBody::ApplyLinearImpulse(const FB3BodyHandle BodyHandle,const FVector3f& Impulse,const FVector& Point, bool Wake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("ApplyLinearImpulse called wih an invalid Body Handle")); 
    b3Body_ApplyLinearImpulse(BodyHandle.GetID(), ToNativeVec(Impulse),ToNativePos(Point),Wake);
}

void UBox3DBody::ApplyLinearImpulseToCenter(const FB3BodyHandle BodyHandle,const FVector3f& Impulse, bool Wake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("ApplyLinearImpulseToCenter called wih an invalid Body Handle")); 
    b3Body_ApplyLinearImpulseToCenter(BodyHandle.GetID(), ToNativeVec(Impulse),Wake);
}

void UBox3DBody::ApplyAngularImpulse(const FB3BodyHandle BodyHandle,const FVector3f& Impulse, bool Wake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("ApplyAngularImpulse called wih an invalid Body Handle")); 
    b3Body_ApplyAngularImpulse(BodyHandle.GetID(), ToNativeVec(Impulse), Wake);
}

float UBox3DBody::GetMass(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0.0f, TEXT("GetMass called wih an invalid Body Handle")); 
    return b3Body_GetMass(BodyHandle.GetID());
}

FMatrix UBox3DBody::GetLocalRotationalInertia(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FMatrix::Identity, TEXT("GetLocalRotationalInertia called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetLocalRotationalInertia(BodyHandle.GetID()));
}

float UBox3DBody::GetInverseMass(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0.0f, TEXT("GetInverseMass called wih an invalid Body Handle")); 
    return b3Body_GetInverseMass(BodyHandle.GetID());
}

FMatrix UBox3DBody::GetWorldInverseRotationalInertia(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FMatrix::Identity, TEXT("GetWorldInverseRotationalInertia called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetWorldInverseRotationalInertia(BodyHandle.GetID()));
}

FVector3f UBox3DBody::GetLocalCenter(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector3f::ZeroVector, TEXT("GetLocalCenter called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetLocalCenter(BodyHandle.GetID()));
}

FVector UBox3DBody::GetWorldCenter(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FVector::ZeroVector, TEXT("GetWorldCenter called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetWorldCenter(BodyHandle.GetID()));
}


void UBox3DBody::SetMassData(const FB3BodyHandle BodyHandle, const FB3MassData& MassData )
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetMassData called wih an invalid Body Handle")); 
    b3Body_SetMassData(BodyHandle.GetID(), ToNative(MassData));
}

FB3MassData UBox3DBody::GetMassData(const FB3BodyHandle BodyHandle )
{
    B3_ENSURE_MSG_RET(BodyHandle, FB3MassData{}, TEXT("GetMassData called wih an invalid Body Handle")); 
    b3MassData MassData = b3Body_GetMassData(BodyHandle.GetID());
    return ToUnreal(b3Body_GetMassData(BodyHandle.GetID()));
}


void UBox3DBody::ApplyMassFromShapes(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("ApplyMassFromShapes called wih an invalid Body Handle")); 
    b3Body_ApplyMassFromShapes(BodyHandle.GetID());
}

void UBox3DBody::SetLinearDamping(const FB3BodyHandle BodyHandle, float LinearDamping)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetLinearDamping called wih an invalid Body Handle")); 
    b3Body_SetLinearDamping(BodyHandle.GetID(), LinearDamping);
}

void UBox3DBody::SetAngularDamping(const FB3BodyHandle BodyHandle, float AngularDamping)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetAngularDamping called wih an invalid Body Handle")); 
    b3Body_SetAngularDamping(BodyHandle.GetID(), AngularDamping);
}

float UBox3DBody::GetLinearDamping(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0.0f, TEXT("GetLinearDamping called wih an invalid Body Handle")); 
    return b3Body_GetLinearDamping(BodyHandle.GetID());
}

float UBox3DBody::GetAngularDamping(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0.0f, TEXT("GetAngularDamping called wih an invalid Body Handle")); 
    return b3Body_GetAngularDamping(BodyHandle.GetID());
}

void UBox3DBody::SetGravityScale(const FB3BodyHandle BodyHandle, float GravityScale)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetGravityScale called wih an invalid Body Handle")); 
    b3Body_SetGravityScale(BodyHandle.GetID(), GravityScale);
}

float UBox3DBody::GetGravityScale(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0.0f, TEXT("GetGravityScale called wih an invalid Body Handle")); 
    return b3Body_GetGravityScale(BodyHandle.GetID());
}

bool UBox3DBody::IsAwake(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, false, TEXT("IsAwake called wih an invalid Body Handle")); 
    return b3Body_IsAwake(BodyHandle.GetID());
}

void UBox3DBody::SetAwake(const FB3BodyHandle BodyHandle, bool Awake)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetAwake called wih an invalid Body Handle")); 
    b3Body_SetAwake(BodyHandle.GetID(), Awake);
}

void UBox3DBody::EnableSleep(const FB3BodyHandle BodyHandle, bool EnableSleep)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("EnableSleep called wih an invalid Body Handle")); 
    b3Body_EnableSleep(BodyHandle.GetID(), EnableSleep);
}

bool UBox3DBody::IsSleepEnabled(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, false, TEXT("IsSleepEnabled called wih an invalid Body Handle")); 
    return b3Body_IsSleepEnabled(BodyHandle.GetID());
}

void UBox3DBody::SetSleepThreshold(const FB3BodyHandle BodyHandle, float SleepThreshold)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetSleepThreshold called wih an invalid Body Handle")); 
    b3Body_SetSleepThreshold(BodyHandle.GetID(), SleepThreshold);
}

float UBox3DBody::GetSleepThreshold(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0.0f, TEXT("GetSleepThreshold called wih an invalid Body Handle")); 
    return b3Body_GetSleepThreshold(BodyHandle.GetID());
}

bool UBox3DBody::IsEnabled(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, false, TEXT("IsEnabled called wih an invalid Body Handle")); 
    return b3Body_IsEnabled(BodyHandle.GetID());
}

void UBox3DBody::Disable(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("Disable called wih an invalid Body Handle")); 
    b3Body_Disable(BodyHandle.GetID());
}

void UBox3DBody::Enable(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("Enable called wih an invalid Body Handle")); 
    b3Body_Enable(BodyHandle.GetID());
}

void UBox3DBody::SetMotionLocks(const FB3BodyHandle BodyHandle,const FB3MotionLocks MotionLocks)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetMotionLocks called wih an invalid Body Handle")); 
    b3Body_SetMotionLocks(BodyHandle.GetID(), ToNative(MotionLocks));
}

FB3MotionLocks UBox3DBody::GetMotionLocks(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FB3MotionLocks{}, TEXT("GetMotionLocks called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_GetMotionLocks(BodyHandle.GetID()));
}

void UBox3DBody::SetBullet(const FB3BodyHandle BodyHandle, bool Flag)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("SetBullet called wih an invalid Body Handle")); 
    b3Body_SetBullet(BodyHandle.GetID(), Flag);
}

bool UBox3DBody::IsBullet(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, false, TEXT("IsBullet called wih an invalid Body Handle")); 
    return b3Body_IsBullet(BodyHandle.GetID());
}

void UBox3DBody::AllowFastRotation(const FB3BodyHandle BodyHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("AllowFastRotation called wih an invalid Body Handle")); 
    b3Body_AllowFastRotation(BodyHandle.GetID(), Flag);
}

bool UBox3DBody::IsFastRotationAllowed(const FB3BodyHandle BodyHandle )
{
    B3_ENSURE_MSG_RET(BodyHandle, false, TEXT("IsFastRotationAllowed called wih an invalid Body Handle")); 
    return b3Body_IsFastRotationAllowed(BodyHandle.GetID());
}

void UBox3DBody::EnableContactRecycling(const FB3BodyHandle BodyHandle, bool Flag)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("EnableContactRecycling called wih an invalid Body Handle")); 
    b3Body_EnableContactRecycling(BodyHandle.GetID(), Flag);
}

bool UBox3DBody::IsContactRecyclingEnabled(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, false, TEXT("IsContactRecyclingEnabled called wih an invalid Body Handle")); 
    return b3Body_IsContactRecyclingEnabled(BodyHandle.GetID());
}

void UBox3DBody::EnableHitEvents(const FB3BodyHandle BodyHandle, bool Flag)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("EnableHitEvents called wih an invalid Body Handle")); 
    b3Body_EnableHitEvents(BodyHandle.GetID(), Flag);
}

FB3WorldHandle UBox3DBody::GetPhysicsWorld(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FB3WorldHandle(b3_nullWorldId), TEXT("GetPhysicsWorld called wih an invalid Body Handle")); 
    return FB3WorldHandle(b3Body_GetWorld(BodyHandle.GetID()));
}

int32 UBox3DBody::GetShapeCount(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0, TEXT("GetShapeCount called wih an invalid Body Handle")); 
    return b3Body_GetShapeCount(BodyHandle.GetID());
}
void UBox3DBody::GetShapes(const FB3BodyHandle BodyHandle, TArray<FB3ShapeHandle>& OutShapeHandles)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("GetShapes called wih an invalid Body Handle")); 
    TArray<b3ShapeId> ShapeIds;
    int32 ShapeCount = B3BODY::GetShapeCount(BodyHandle);
    ShapeIds.SetNum(ShapeCount);
    const int32 Count = b3Body_GetShapes( BodyHandle.GetID(), ShapeIds.GetData(), ShapeCount);
    OutShapeHandles.Reset();
    OutShapeHandles.Reserve(Count);
    for (int32 Index = 0; Index < Count; ++Index)
    {
        OutShapeHandles.Add(FB3ShapeHandle(ShapeIds[Index]));
    }
}
void UBox3DBody::GetJoints(const FB3BodyHandle BodyHandle, TArray<FB3JointHandle>& OutJointHandles )
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("GetJoints called wih an invalid Body Handle")); 
    TArray<b3JointId> JointIds;
    int32 JointCount = GetJointCount(BodyHandle);
    JointIds.SetNum(JointCount);
    const int32 Count = b3Body_GetJoints( BodyHandle.GetID(), JointIds.GetData(), JointCount);
    OutJointHandles.Reset();
    OutJointHandles.Reserve(Count);
    for (int32 Index = 0; Index < Count; ++Index)
    {
        OutJointHandles.Add(FB3JointHandle(JointIds[Index]));
    }
}

int32 UBox3DBody::GetJointCount(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0, TEXT("GetJointCount called wih an invalid Body Handle")); 
    return b3Body_GetJointCount(BodyHandle.GetID());
}

int32 UBox3DBody::GetContactCapacity(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, 0, TEXT("GetContactCapacity called wih an invalid Body Handle")); 
    return b3Body_GetContactCapacity(BodyHandle.GetID());
}
FB3AABB UBox3DBody::ComputeAABB(const FB3BodyHandle BodyHandle)
{
    B3_ENSURE_MSG_RET(BodyHandle, FB3AABB{}, TEXT("ComputeAABB called wih an invalid Body Handle")); 
    return ToUnreal(b3Body_ComputeAABB(BodyHandle.GetID()));
}

void UBox3DBody::GetClosestPoint(const FB3BodyHandle BodyHandle, FVector3f& OutPoint,const FVector3f& Target)
{
    B3_ENSURE_MSG_RET(BodyHandle,, TEXT("GetClosestPoint called wih an invalid Body Handle")); 
    b3Vec3 Result;
    float Distance = b3Body_GetClosestPoint(BodyHandle.GetID(), &Result, ToNativeVec(Target));
    OutPoint = ToUnreal(Result);
}