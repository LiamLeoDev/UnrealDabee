// Copyright (c) 2026 LiamLeo

#include "Box3DJoint.h"
#include "Box3DTypes.h"
#include "Box3DWorld.h"
#include "Box3DAsserts.h"
#include "box3d/box3d.h"
#include "box3d/types.h"

void UBox3DJoint::DestroyJoint( FB3JointHandle& JointHandle, bool WakeAttached )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("DestroyJoint called with an invlaid Joint Handle")); 
    b3DestroyJoint(JointHandle.GetID(), WakeAttached);
    JointHandle = FB3JointHandle(b3_nullJointId);
}
bool UBox3DJoint::IsValid( const FB3JointHandle JointHandle )
{
    return bool(JointHandle);
}
EB3JointType UBox3DJoint::GetType( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, EB3JointType::None, TEXT("GetType called with an invlaid Joint Handle"));
    return ToUnreal(b3Joint_GetType(JointHandle.GetID()));
}
FB3BodyHandle UBox3DJoint::GetBodyA( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, FB3BodyHandle(b3_nullBodyId), TEXT("GetBodyA called with an invlaid Joint Handle"));
    return FB3BodyHandle(b3Joint_GetBodyA(JointHandle.GetID()));
}
FB3BodyHandle UBox3DJoint::GetBodyB( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, FB3BodyHandle(b3_nullBodyId), TEXT("GetBodyB called with an invlaid Joint Handle"));
    return FB3BodyHandle(b3Joint_GetBodyB(JointHandle.GetID()));
}
FB3WorldHandle UBox3DJoint::GetPhysicsWorld( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, FB3WorldHandle(b3_nullWorldId), TEXT("GetPhysicsWorld called with an invlaid Joint Handle"));
    return FB3WorldHandle(b3Joint_GetWorld(JointHandle.GetID()));
}
void UBox3DJoint::SetLocalFrameA( const FB3JointHandle JointHandle, const FVector3f& Location, const FQuat4f& Rotation )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SetLocalFrameA called with an invlaid Joint Handle")); 
    b3Joint_SetLocalFrameA(JointHandle.GetID(), ToNativeTransform(FTransform3f(Rotation,Location)));
}
void UBox3DJoint::GetLocalFrameA( const FB3JointHandle JointHandle, FVector3f& Location, FQuat4f& Rotation )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("GetLocalFrameA called with an invlaid Joint Handle")); 
    FTransform3f LocalFrame = ToUnreal(b3Joint_GetLocalFrameA(JointHandle.GetID()));
    Location = LocalFrame.GetLocation();
    Rotation = LocalFrame.GetRotation();
}
void UBox3DJoint::SetLocalFrameB( const FB3JointHandle JointHandle, const FVector3f& Location, const FQuat4f& Rotation )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SetLocalFrameB called with an invlaid Joint Handle")); 
    b3Joint_SetLocalFrameB(JointHandle.GetID(), ToNativeTransform(FTransform3f(Rotation,Location)));
}
void UBox3DJoint::GetLocalFrameB( const FB3JointHandle JointHandle, FVector3f& Location, FQuat4f& Rotation )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("GetLocalFrameB called with an invlaid Joint Handle")); 
    FTransform3f LocalFrame = ToUnreal(b3Joint_GetLocalFrameB(JointHandle.GetID()));
    Location = LocalFrame.GetLocation();
    Rotation = LocalFrame.GetRotation();
}
void UBox3DJoint::SetCollideConnected( const FB3JointHandle JointHandle, bool ShouldCollide )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SetCollideConnected called with an invlaid Joint Handle")); 
    b3Joint_SetCollideConnected(JointHandle.GetID(), ShouldCollide);
}
bool UBox3DJoint::GetCollideConnected( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, false, TEXT("GetCollideConnected called with an invlaid Joint Handle"));
    return b3Joint_GetCollideConnected(JointHandle.GetID());
}
void UBox3DJoint::SetUserData( const FB3JointHandle JointHandle, FB3JointUserData* UserData )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SetUserData called with an invlaid Joint Handle")); 
    b3Joint_SetUserData(JointHandle.GetID(), UserData );
}
UObject* UBox3DJoint::BP_GetUserData(const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle, nullptr, TEXT("BP_GetUserData called with an invlaid Joint Handle"));
    if(FB3JointUserData* UserData = GetUserData(JointHandle))
    {
        return UserData->Object.Get();
    }
    return nullptr;
}
FB3JointUserData* UBox3DJoint::GetUserData( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, nullptr, TEXT("GetUserData called with an invlaid Joint Handle"));
    return static_cast<FB3JointUserData*>(b3Joint_GetUserData(JointHandle.GetID()));
}
void UBox3DJoint::WakeBodies( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WakeBodies called with an invlaid Joint Handle")); 
    b3Joint_WakeBodies(JointHandle.GetID());
}
FVector3f UBox3DJoint::GetConstraintForce( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, FVector3f::ZeroVector, TEXT("GetConstraintForce called with an invlaid Joint Handle"));
    return ToUnreal(b3Joint_GetConstraintForce(JointHandle.GetID()));
}
FVector3f UBox3DJoint::GetConstraintTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, FVector3f::ZeroVector, TEXT("GetConstraintTorque called with an invlaid Joint Handle"));
    return ToUnreal(b3Joint_GetConstraintTorque(JointHandle.GetID()));
}
float UBox3DJoint::GetLinearSeparation( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, 0.0f, TEXT("GetLinearSeparation called with an invlaid Joint Handle"));
    return b3Joint_GetLinearSeparation(JointHandle.GetID());
}
float UBox3DJoint::GetAngularSeparation( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, 0.0f, TEXT("GetAngularSeparation called with an invlaid Joint Handle"));
    return b3Joint_GetAngularSeparation(JointHandle.GetID());
}
void UBox3DJoint::SetConstraintTuning( const FB3JointHandle JointHandle, float Hertz, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SetConstraintTuning called with an invlaid Joint Handle")); 
    b3Joint_SetConstraintTuning(JointHandle.GetID(), Hertz, DampingRatio);
}
void UBox3DJoint::GetConstraintTuning( const FB3JointHandle JointHandle, float& Hertz, float& DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("GetConstraintTuning called with an invlaid Joint Handle")); 
    b3Joint_GetConstraintTuning(JointHandle.GetID(), &Hertz, &DampingRatio);
}
void UBox3DJoint::SetForceThreshold( const FB3JointHandle JointHandle, float Threshold )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SetForceThreshold called with an invlaid Joint Handle")); 
    b3Joint_SetForceThreshold(JointHandle.GetID(), Threshold);
}
float UBox3DJoint::GetForceThreshold( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, 0.0f, TEXT("GetForceThreshold called with an invlaid Joint Handle"));
    return b3Joint_GetForceThreshold(JointHandle.GetID());
}
void UBox3DJoint::SetTorqueThreshold( const FB3JointHandle JointHandle, float Threshold )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SetTorqueThreshold called with an invlaid Joint Handle")); 
    b3Joint_SetTorqueThreshold(JointHandle.GetID(), Threshold);
}
float UBox3DJoint::GetTorqueThreshold( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle, 0.0f, TEXT("GetTorqueThreshold called with an invlaid Joint Handle"));
    return b3Joint_GetTorqueThreshold(JointHandle.GetID());
}









void UBox3DJoint::RevoluteJoint_SetTargetAngle( const FB3JointHandle JointHandle, float TargetRadians )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("RevoluteJoint_SetTargetAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,, TEXT("RevoluteJoint_SetTargetAngle The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_SetTargetAngle(JointHandle.GetID(), TargetRadians);
}
float UBox3DJoint::RevoluteJoint_GetTargetAngle( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("RevoluteJoint_GetTargetAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f, TEXT("RevoluteJoint_GetTargetAngle The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetTargetAngle(JointHandle.GetID());
}
float UBox3DJoint::RevoluteJoint_GetAngle( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("RevoluteJoint_GetAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f, TEXT("RevoluteJoint_GetAngle The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetAngle(JointHandle.GetID());
}
float UBox3DJoint::RevoluteJoint_GetMotorTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("RevoluteJoint_GetMotorTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f, TEXT("RevoluteJoint_GetMotorTorque The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetMotorTorque(JointHandle.GetID());
}
void UBox3DJoint::RevoluteJoint_SetMaxMotorTorque( const FB3JointHandle JointHandle, float Torque )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("RevoluteJoint_SetMaxMotorTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,, TEXT("RevoluteJoint_SetMaxMotorTorque The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_SetMaxMotorTorque(JointHandle.GetID(), Torque);
}
float UBox3DJoint::RevoluteJoint_GetMaxMotorTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("RevoluteJoint_GetMaxMotorTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f, TEXT("RevoluteJoint_GetMaxMotorTorque The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetMaxMotorTorque(JointHandle.GetID());
}
void UBox3DJoint::RevoluteJoint_EnableLimit( const FB3JointHandle JointHandle, bool EnableLimit )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("RevoluteJoint_EnableLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,, TEXT("RevoluteJoint_EnableLimit The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_EnableLimit(JointHandle.GetID(), EnableLimit);
}
bool UBox3DJoint::RevoluteJoint_IsLimitEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("RevoluteJoint_IsLimitEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  false, TEXT("RevoluteJoint_IsLimitEnabled The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_IsLimitEnabled(JointHandle.GetID());
}
float UBox3DJoint::RevoluteJoint_GetLowerLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("RevoluteJoint_GetLowerLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f, TEXT("RevoluteJoint_GetLowerLimit The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetLowerLimit(JointHandle.GetID());
}
float UBox3DJoint::RevoluteJoint_GetUpperLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("RevoluteJoint_GetUpperLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f, TEXT("RevoluteJoint_GetUpperLimit The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetUpperLimit(JointHandle.GetID());
}
void UBox3DJoint::RevoluteJoint_SetLimits( const FB3JointHandle JointHandle, float LowerLimitRadians, float UpperLimitRadians )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("RevoluteJoint_SetLimits called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,, TEXT("RevoluteJoint_SetLimits The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_SetLimits(JointHandle.GetID(),LowerLimitRadians,UpperLimitRadians);
}
void UBox3DJoint::RevoluteJoint_SetMotorSpeed( const FB3JointHandle JointHandle, float MotorSpeed )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("RevoluteJoint_SetMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,, TEXT("RevoluteJoint_SetMotorSpeed The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_SetMotorSpeed(JointHandle.GetID(), MotorSpeed);
}
float UBox3DJoint::RevoluteJoint_GetMotorSpeed( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("RevoluteJoint_GetMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f , TEXT("RevoluteJoint_GetMotorSpeed The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetMotorSpeed(JointHandle.GetID());
}
void UBox3DJoint::RevoluteJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("RevoluteJoint_EnableSpring called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,, TEXT("RevoluteJoint_EnableSpring The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_EnableSpring(JointHandle.GetID(),EnableSpring); 
}
bool UBox3DJoint::RevoluteJoint_IsSpringEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("RevoluteJoint_IsSpringEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  false, TEXT("RevoluteJoint_IsSpringEnabled The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_IsSpringEnabled(JointHandle.GetID());
}
void UBox3DJoint::RevoluteJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("RevoluteJoint_EnableMotor called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,, TEXT("RevoluteJoint_EnableMotor The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_EnableMotor(JointHandle.GetID(), EnableMotor); 
}
bool UBox3DJoint::RevoluteJoint_IsMotorEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("RevoluteJoint_IsMotorEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  false, TEXT("RevoluteJoint_IsMotorEnabled The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_IsMotorEnabled(JointHandle.GetID());
}
void UBox3DJoint::RevoluteJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("RevoluteJoint_SetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint, , TEXT("RevoluteJoint_SetSpringHertz The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_SetSpringHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::RevoluteJoint_GetSpringHertz( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("RevoluteJoint_GetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f , TEXT("RevoluteJoint_GetSpringHertz The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetSpringHertz(JointHandle.GetID());
}
void UBox3DJoint::RevoluteJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("RevoluteJoint_SetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint, , TEXT("RevoluteJoint_SetSpringDampingRatio The passed in Joint Handle is not RevoluteJoint Handle"));
    b3RevoluteJoint_SetSpringDampingRatio(JointHandle.GetID(), DampingRatio); 
}
float UBox3DJoint::RevoluteJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("RevoluteJoint_GetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::RevoluteJoint,  0.0f , TEXT("RevoluteJoint_GetSpringDampingRatio The passed in Joint Handle is not RevoluteJoint Handle"));
    return b3RevoluteJoint_GetSpringDampingRatio(JointHandle.GetID());
}







void UBox3DJoint::ParallelJoint_SetMaxTorque( const FB3JointHandle JointHandle, float Force )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("ParallelJoint_SetMaxTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::ParallelJoint,, TEXT("ParallelJoint_SetMaxTorque The passed in Joint Handle is not ParallelJoint Handle"));
    b3ParallelJoint_SetMaxTorque(JointHandle.GetID(), Force);
}
float UBox3DJoint::ParallelJoint_GetMaxTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("ParallelJoint_GetMaxTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::ParallelJoint,  0.0f, TEXT("ParallelJoint_GetMaxTorque The passed in Joint Handle is not ParallelJoint Handle"));
    return b3ParallelJoint_GetMaxTorque(JointHandle.GetID());
}
void UBox3DJoint::ParallelJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("ParallelJoint_SetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::ParallelJoint, , TEXT("ParallelJoint_SetSpringHertz The passed in Joint Handle is not ParallelJoint Handle"));
    b3ParallelJoint_SetSpringHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::ParallelJoint_GetSpringHertz( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("ParallelJoint_GetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::ParallelJoint,  0.0f , TEXT("ParallelJoint_GetSpringHertz The passed in Joint Handle is not ParallelJoint Handle"));
    return b3ParallelJoint_GetSpringHertz(JointHandle.GetID());
}
void UBox3DJoint::ParallelJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("ParallelJoint_SetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::ParallelJoint, , TEXT("ParallelJoint_SetSpringDampingRatio The passed in Joint Handle is not ParallelJoint Handle"));
    b3ParallelJoint_SetSpringDampingRatio(JointHandle.GetID(), DampingRatio); 
}
float UBox3DJoint::ParallelJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("ParallelJoint_GetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::ParallelJoint,  0.0f , TEXT("ParallelJoint_GetSpringDampingRatio The passed in Joint Handle is not ParallelJoint Handle"));
    return b3ParallelJoint_GetSpringDampingRatio(JointHandle.GetID());
}







void UBox3DJoint::DistanceJoint_SetLength( const FB3JointHandle JointHandle, float Length )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("DistanceJoint_SetLength called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,, TEXT("DistanceJoint_SetLength The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_SetLength(JointHandle.GetID(),Length);
}
float UBox3DJoint::DistanceJoint_GetLength( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("DistanceJoint_GetLength called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f, TEXT("DistanceJoint_GetLength The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetLength(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_SetSpringForceRange( const FB3JointHandle JointHandle, float LowerForce, float UpperForce )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("DistanceJoint_SetSpringForceRange called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,, TEXT("DistanceJoint_SetSpringForceRange The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_SetSpringForceRange(JointHandle.GetID(), LowerForce, UpperForce);
}
void UBox3DJoint::DistanceJoint_GetSpringForceRange( const FB3JointHandle JointHandle, float& LowerForce, float& UpperForce )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("DistanceJoint_GetSpringForceRange called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,, TEXT("DistanceJoint_GetSpringForceRange The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_GetSpringForceRange(JointHandle.GetID(), &LowerForce, &UpperForce);
}
float UBox3DJoint::DistanceJoint_GetCurrentLength( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("DistanceJoint_GetCurrentLength called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f, TEXT("DistanceJoint_GetCurrentLength The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetCurrentLength(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_EnableLimit( const FB3JointHandle JointHandle, bool EnableLimit )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("DistanceJoint_EnableLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,, TEXT("DistanceJoint_EnableLimit The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_EnableLimit(JointHandle.GetID(), EnableLimit);
}
bool UBox3DJoint::DistanceJoint_IsLimitEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("DistanceJoint_IsLimitEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  false, TEXT("DistanceJoint_IsLimitEnabled The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_IsLimitEnabled(JointHandle.GetID());
}
float UBox3DJoint::DistanceJoint_GetMinLength( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("DistanceJoint_GetMinLength called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f, TEXT("DistanceJoint_GetMinLength The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetMinLength(JointHandle.GetID());
}
float UBox3DJoint::DistanceJoint_GetMaxLength( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("DistanceJoint_GetMaxLength called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f, TEXT("DistanceJoint_GetMaxLength The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetMaxLength(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_SetLengthRange( const FB3JointHandle JointHandle, float MinLength, float MaxLength )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("DistanceJoint_SetLengthRange called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,, TEXT("DistanceJoint_SetLengthRange The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_SetLengthRange(JointHandle.GetID(),MinLength,MaxLength);
}
void UBox3DJoint::DistanceJoint_SetMaxMotorForce( const FB3JointHandle JointHandle, float Force )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("DistanceJoint_SetMaxMotorForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint, , TEXT("DistanceJoint_SetMaxMotorForce The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_SetMaxMotorForce(JointHandle.GetID(),Force);
}
float UBox3DJoint::DistanceJoint_GetMaxMotorForce( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("DistanceJoint_GetMaxMotorForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f , TEXT("DistanceJoint_GetMaxMotorForce The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetMaxMotorForce(JointHandle.GetID());
}
float UBox3DJoint::DistanceJoint_GetMotorForce( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("DistanceJoint_GetMotorForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f , TEXT("DistanceJoint_GetMotorForce The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetMotorForce(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_SetMotorSpeed( const FB3JointHandle JointHandle, float MotorSpeed )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("DistanceJoint_SetMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint, , TEXT("DistanceJoint_SetMotorSpeed The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_SetMotorSpeed(JointHandle.GetID(), MotorSpeed);
}
float UBox3DJoint::DistanceJoint_GetMotorSpeed( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("DistanceJoint_GetMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f , TEXT("DistanceJoint_GetMotorSpeed The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetMotorSpeed(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("DistanceJoint_EnableSpring called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint, , TEXT("DistanceJoint_EnableSpring The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_EnableSpring(JointHandle.GetID(),EnableSpring); 
}
bool UBox3DJoint::DistanceJoint_IsSpringEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false , TEXT("DistanceJoint_IsSpringEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  false , TEXT("DistanceJoint_IsSpringEnabled The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_IsSpringEnabled(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("DistanceJoint_EnableMotor called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint, , TEXT("DistanceJoint_EnableMotor The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_EnableMotor(JointHandle.GetID(), EnableMotor); 
}
bool UBox3DJoint::DistanceJoint_IsMotorEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false , TEXT("DistanceJoint_IsMotorEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  false , TEXT("DistanceJoint_IsMotorEnabled The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_IsMotorEnabled(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("DistanceJoint_SetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint, , TEXT("DistanceJoint_SetSpringHertz The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_SetSpringHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::DistanceJoint_GetSpringHertz( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("DistanceJoint_GetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f , TEXT("DistanceJoint_GetSpringHertz The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetSpringHertz(JointHandle.GetID());
}
void UBox3DJoint::DistanceJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("DistanceJoint_SetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint, , TEXT("DistanceJoint_SetSpringDampingRatio The passed in Joint Handle is not DistanceJoint Handle"));
    b3DistanceJoint_SetSpringDampingRatio(JointHandle.GetID(), DampingRatio); 
}
float UBox3DJoint::DistanceJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("DistanceJoint_GetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::DistanceJoint,  0.0f , TEXT("DistanceJoint_GetSpringDampingRatio The passed in Joint Handle is not DistanceJoint Handle"));
    return b3DistanceJoint_GetSpringDampingRatio(JointHandle.GetID());
}







void UBox3DJoint::PrismaticJoint_SetTargetTranslation( const FB3JointHandle JointHandle, float TargetTranslation )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("PrismaticJoint_SetTargetTranslation called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,, TEXT("PrismaticJoint_SetTargetTranslation The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_SetTargetTranslation(JointHandle.GetID(), TargetTranslation);
}
float UBox3DJoint::PrismaticJoint_GetTargetTranslation( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("PrismaticJoint_GetTargetTranslation called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f, TEXT("PrismaticJoint_GetTargetTranslation The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetTargetTranslation(JointHandle.GetID());
}
float UBox3DJoint::PrismaticJoint_GetTranslation( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("PrismaticJoint_GetTranslation called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f, TEXT("PrismaticJoint_GetTranslation The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetTranslation(JointHandle.GetID());
}
float UBox3DJoint::PrismaticJoint_GetSpeed( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("PrismaticJoint_GetSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f, TEXT("PrismaticJoint_GetSpeed The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetSpeed(JointHandle.GetID());
}
void UBox3DJoint::PrismaticJoint_EnableLimit( const FB3JointHandle JointHandle, bool EnableLimit )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("PrismaticJoint_EnableLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,, TEXT("PrismaticJoint_EnableLimit The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_EnableLimit(JointHandle.GetID(), EnableLimit);
}
bool UBox3DJoint::PrismaticJoint_IsLimitEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("PrismaticJoint_IsLimitEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  false, TEXT("PrismaticJoint_IsLimitEnabled The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_IsLimitEnabled(JointHandle.GetID());
}
float UBox3DJoint::PrismaticJoint_GetLowerLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("PrismaticJoint_GetLowerLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f, TEXT("PrismaticJoint_GetLowerLimit The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetLowerLimit(JointHandle.GetID());
}
float UBox3DJoint::PrismaticJoint_GetUpperLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("PrismaticJoint_GetUpperLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f, TEXT("PrismaticJoint_GetUpperLimit The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetUpperLimit(JointHandle.GetID());
}
void UBox3DJoint::PrismaticJoint_SetLimits( const FB3JointHandle JointHandle, float Lower, float Upper )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("PrismaticJoint_SetLimits called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,, TEXT("PrismaticJoint_SetLimits The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_SetLimits(JointHandle.GetID(),Lower,Upper);
}
void UBox3DJoint::PrismaticJoint_SetMaxMotorForce( const FB3JointHandle JointHandle, float Force )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("PrismaticJoint_SetMaxMotorForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint, , TEXT("PrismaticJoint_SetMaxMotorForce The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_SetMaxMotorForce(JointHandle.GetID(),Force);
}
float UBox3DJoint::PrismaticJoint_GetMaxMotorForce( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("PrismaticJoint_GetMaxMotorForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f , TEXT("PrismaticJoint_GetMaxMotorForce The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetMaxMotorForce(JointHandle.GetID());
}
float UBox3DJoint::PrismaticJoint_GetMotorForce( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("PrismaticJoint_GetMotorForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f , TEXT("PrismaticJoint_GetMotorForce The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetMotorForce(JointHandle.GetID());
}
void UBox3DJoint::PrismaticJoint_SetMotorSpeed( const FB3JointHandle JointHandle, float MotorSpeed )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("PrismaticJoint_SetMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint, , TEXT("PrismaticJoint_SetMotorSpeed The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_SetMotorSpeed(JointHandle.GetID(), MotorSpeed);
}
float UBox3DJoint::PrismaticJoint_GetMotorSpeed( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("PrismaticJoint_GetMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f , TEXT("PrismaticJoint_GetMotorSpeed The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetMotorSpeed(JointHandle.GetID());
}
void UBox3DJoint::PrismaticJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("PrismaticJoint_EnableSpring called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint, , TEXT("PrismaticJoint_EnableSpring The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_EnableSpring(JointHandle.GetID(),EnableSpring); 
}
bool UBox3DJoint::PrismaticJoint_IsSpringEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false , TEXT("PrismaticJoint_IsSpringEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  false , TEXT("PrismaticJoint_IsSpringEnabled The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_IsSpringEnabled(JointHandle.GetID());
}
void UBox3DJoint::PrismaticJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("PrismaticJoint_EnableMotor called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint, , TEXT("PrismaticJoint_EnableMotor The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_EnableMotor(JointHandle.GetID(), EnableMotor); 
}
bool UBox3DJoint::PrismaticJoint_IsMotorEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false , TEXT("PrismaticJoint_IsMotorEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  false , TEXT("PrismaticJoint_IsMotorEnabled The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_IsMotorEnabled(JointHandle.GetID());
}
void UBox3DJoint::PrismaticJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("PrismaticJoint_SetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint, , TEXT("PrismaticJoint_SetSpringHertz The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_SetSpringHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::PrismaticJoint_GetSpringHertz( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("PrismaticJoint_GetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f , TEXT("PrismaticJoint_GetSpringHertz The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetSpringHertz(JointHandle.GetID());
}
void UBox3DJoint::PrismaticJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("PrismaticJoint_SetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint, , TEXT("PrismaticJoint_SetSpringDampingRatio The passed in Joint Handle is not PrismaticJoint Handle"));
    b3PrismaticJoint_SetSpringDampingRatio(JointHandle.GetID(), DampingRatio); 
}
float UBox3DJoint::PrismaticJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("PrismaticJoint_GetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::PrismaticJoint,  0.0f , TEXT("PrismaticJoint_GetSpringDampingRatio The passed in Joint Handle is not PrismaticJoint Handle"));
    return b3PrismaticJoint_GetSpringDampingRatio(JointHandle.GetID());
}







void UBox3DJoint::SphericalJoint_EnableConeLimit( const FB3JointHandle JointHandle, bool EnableLimit )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_EnableConeLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_EnableConeLimit The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_EnableConeLimit(JointHandle.GetID(), EnableLimit);
}
bool UBox3DJoint::SphericalJoint_IsConeLimitEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("SphericalJoint_IsConeLimitEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  false, TEXT("SphericalJoint_IsConeLimitEnabled The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_IsConeLimitEnabled(JointHandle.GetID());
}
float UBox3DJoint::SphericalJoint_GetConeLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("SphericalJoint_GetConeLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f, TEXT("SphericalJoint_GetConeLimit The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetConeLimit(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_SetConeLimit( const FB3JointHandle JointHandle, float AngleRadians )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_SetConeLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_SetConeLimit The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_SetConeLimit(JointHandle.GetID(), AngleRadians);
}
float UBox3DJoint::SphericalJoint_GetConeAngle( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("SphericalJoint_GetConeAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f, TEXT("SphericalJoint_GetConeAngle The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetConeAngle(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_EnableTwistLimit( const FB3JointHandle JointHandle, bool EnableLimit )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_EnableTwistLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_EnableTwistLimit The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_EnableTwistLimit(JointHandle.GetID(), EnableLimit);
}
bool UBox3DJoint::SphericalJoint_IsTwistLimitEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("SphericalJoint_IsTwistLimitEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  false, TEXT("SphericalJoint_IsTwistLimitEnabled The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_IsTwistLimitEnabled(JointHandle.GetID());
}
float UBox3DJoint::SphericalJoint_GetLowerTwistLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("SphericalJoint_GetLowerTwistLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f, TEXT("SphericalJoint_GetLowerTwistLimit The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetLowerTwistLimit(JointHandle.GetID());
}
float UBox3DJoint::SphericalJoint_GetUpperTwistLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("SphericalJoint_GetUpperTwistLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f, TEXT("SphericalJoint_GetUpperTwistLimit The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetUpperTwistLimit(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_SetTwistLimits( const FB3JointHandle JointHandle, float LowerLimitRadians, float UpperLimitRadians )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_SetTwistLimits called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_SetTwistLimits The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_SetTwistLimits(JointHandle.GetID(), LowerLimitRadians, UpperLimitRadians);
}
float UBox3DJoint::SphericalJoint_GetTwistAngle( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("SphericalJoint_GetTwistAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f, TEXT("SphericalJoint_GetTwistAngle The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetTwistAngle(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_SetTargetRotation( const FB3JointHandle JointHandle, FQuat4f TargetRotation )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_SetTargetRotation called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_SetTargetRotation The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_SetTargetRotation(JointHandle.GetID(), ToNative(TargetRotation));
}
FQuat4f UBox3DJoint::SphericalJoint_GetTargetRotation( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  FQuat4f::Identity, TEXT("SphericalJoint_GetTargetRotation called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  FQuat4f::Identity, TEXT("SphericalJoint_GetTargetRotation The passed in Joint Handle is not SphericalJoint Handle"));
    return ToUnreal(b3SphericalJoint_GetTargetRotation(JointHandle.GetID()));
}
void UBox3DJoint::SphericalJoint_SetMotorVelocity( const FB3JointHandle JointHandle, const FVector3f& MotorVelocity )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_SetMotorVelocity called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_SetMotorVelocity The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_SetMotorVelocity(JointHandle.GetID(), ToNativeVec(MotorVelocity));
}
FVector3f UBox3DJoint::SphericalJoint_GetMotorVelocity( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  FVector3f::ZeroVector, TEXT("SphericalJoint_GetMotorVelocity called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  FVector3f::ZeroVector, TEXT("SphericalJoint_GetMotorVelocity The passed in Joint Handle is not SphericalJoint Handle"));
    return ToUnreal(b3SphericalJoint_GetMotorVelocity(JointHandle.GetID()));
}
FVector3f UBox3DJoint::SphericalJoint_GetMotorTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  FVector3f::ZeroVector, TEXT("SphericalJoint_GetMotorTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  FVector3f::ZeroVector, TEXT("SphericalJoint_GetMotorTorque The passed in Joint Handle is not SphericalJoint Handle"));
    return ToUnreal(b3SphericalJoint_GetMotorTorque(JointHandle.GetID()));
}
void UBox3DJoint::SphericalJoint_SetMaxMotorTorque( const FB3JointHandle JointHandle, float Torque )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_SetMaxMotorTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_SetMaxMotorTorque The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_SetMaxMotorTorque(JointHandle.GetID(), Torque);
}
float UBox3DJoint::SphericalJoint_GetMaxMotorTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("SphericalJoint_GetMaxMotorTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f, TEXT("SphericalJoint_GetMaxMotorTorque The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetMaxMotorTorque(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_EnableSpring called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_EnableSpring The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_EnableSpring(JointHandle.GetID(),EnableSpring); 
}
bool UBox3DJoint::SphericalJoint_IsSpringEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("SphericalJoint_IsSpringEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  false, TEXT("SphericalJoint_IsSpringEnabled The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_IsSpringEnabled(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("SphericalJoint_EnableMotor called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,, TEXT("SphericalJoint_EnableMotor The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_EnableMotor(JointHandle.GetID(), EnableMotor); 
}
bool UBox3DJoint::SphericalJoint_IsMotorEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("SphericalJoint_IsMotorEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  false, TEXT("SphericalJoint_IsMotorEnabled The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_IsMotorEnabled(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("SphericalJoint_SetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint, , TEXT("SphericalJoint_SetSpringHertz The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_SetSpringHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::SphericalJoint_GetSpringHertz( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("SphericalJoint_GetSpringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f , TEXT("SphericalJoint_GetSpringHertz The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetSpringHertz(JointHandle.GetID());
}
void UBox3DJoint::SphericalJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle, , TEXT("SphericalJoint_SetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint, , TEXT("SphericalJoint_SetSpringDampingRatio The passed in Joint Handle is not SphericalJoint Handle"));
    b3SphericalJoint_SetSpringDampingRatio(JointHandle.GetID(), DampingRatio); 
}
float UBox3DJoint::SphericalJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle)
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f , TEXT("SphericalJoint_GetSpringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::SphericalJoint,  0.0f , TEXT("SphericalJoint_GetSpringDampingRatio The passed in Joint Handle is not SphericalJoint Handle"));
    return b3SphericalJoint_GetSpringDampingRatio(JointHandle.GetID());
}







void UBox3DJoint::MotorJoint_SetLinearVelocity( const FB3JointHandle JointHandle, const FVector3f& Velocity )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetLinearVelocity called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetLinearVelocity The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetLinearVelocity(JointHandle.GetID(), ToNativeVec(Velocity));
}
FVector3f UBox3DJoint::MotorJoint_GetLinearVelocity( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  FVector3f::ZeroVector, TEXT("MotorJoint_GetLinearVelocity called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  FVector3f::ZeroVector, TEXT("MotorJoint_GetLinearVelocity The passed in Joint Handle is not MotorJoint Handle"));
    return ToUnreal(b3MotorJoint_GetLinearVelocity(JointHandle.GetID()));
}
void UBox3DJoint::MotorJoint_SetAngularVelocity( const FB3JointHandle JointHandle, const FVector3f& Velocity )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetAngularVelocity called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetAngularVelocity The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetAngularVelocity(JointHandle.GetID(), ToNativeVec(Velocity));
}
FVector3f UBox3DJoint::MotorJoint_GetAngularVelocity( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  FVector3f::ZeroVector, TEXT("MotorJoint_GetAngularVelocity called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  FVector3f::ZeroVector, TEXT("MotorJoint_GetAngularVelocity The passed in Joint Handle is not MotorJoint Handle"));
    return ToUnreal(b3MotorJoint_GetAngularVelocity(JointHandle.GetID()));
}
void UBox3DJoint::MotorJoint_SetMaxVelocityForce( const FB3JointHandle JointHandle, float MaxForce )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetMaxVelocityForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetMaxVelocityForce The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetMaxVelocityForce(JointHandle.GetID(), MaxForce);
}
float UBox3DJoint::MotorJoint_GetMaxVelocityForce( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetMaxVelocityForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetMaxVelocityForce The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetMaxVelocityForce(JointHandle.GetID());
}
void UBox3DJoint::MotorJoint_SetMaxVelocityTorque( const FB3JointHandle JointHandle, float MaxTorque )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetMaxVelocityTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetMaxVelocityTorque The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetMaxVelocityTorque(JointHandle.GetID(),MaxTorque);
}
float UBox3DJoint::MotorJoint_GetMaxVelocityTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetMaxVelocityTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetMaxVelocityTorque The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetMaxVelocityTorque(JointHandle.GetID());
}
void UBox3DJoint::MotorJoint_SetMaxSpringForce( const FB3JointHandle JointHandle, float MaxForce )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetMaxSpringForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetMaxSpringForce The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetMaxSpringForce(JointHandle.GetID(),MaxForce);
}
float UBox3DJoint::MotorJoint_GetMaxSpringForce( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetMaxSpringForce called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetMaxSpringForce The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetMaxSpringForce(JointHandle.GetID());
}
void UBox3DJoint::MotorJoint_SetMaxSpringTorque( const FB3JointHandle JointHandle, float MaxTorque )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetMaxSpringTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetMaxSpringTorque The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetMaxSpringTorque(JointHandle.GetID(),MaxTorque);
}
float UBox3DJoint::MotorJoint_GetMaxSpringTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetMaxSpringTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetMaxSpringTorque The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetMaxSpringTorque(JointHandle.GetID());
}
void UBox3DJoint::MotorJoint_SetLinearHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetLinearHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetLinearHertz The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetLinearHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::MotorJoint_GetLinearHertz( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetLinearHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetLinearHertz The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetLinearHertz(JointHandle.GetID());
}
void UBox3DJoint::MotorJoint_SetLinearDampingRatio( const FB3JointHandle JointHandle, float Damping )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetLinearDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetLinearDampingRatio The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetLinearDampingRatio(JointHandle.GetID(), Damping);
}
float UBox3DJoint::MotorJoint_GetLinearDampingRatio( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetLinearDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetLinearDampingRatio The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetLinearDampingRatio(JointHandle.GetID());
}
void UBox3DJoint::MotorJoint_SetAngularHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetAngularHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetAngularHertz The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetAngularHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::MotorJoint_GetAngularHertz( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetAngularHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetAngularHertz The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetAngularHertz(JointHandle.GetID());
}
void UBox3DJoint::MotorJoint_SetAngularDampingRatio( const FB3JointHandle JointHandle, float Damping )
{    
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("MotorJoint_SetAngularDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,, TEXT("MotorJoint_SetAngularDampingRatio The passed in Joint Handle is not MotorJoint Handle"));
    b3MotorJoint_SetAngularDampingRatio(JointHandle.GetID(), Damping);
}
float UBox3DJoint::MotorJoint_GetAngularDampingRatio( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("MotorJoint_GetAngularDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::MotorJoint,  0.0f, TEXT("MotorJoint_GetAngularDampingRatio The passed in Joint Handle is not MotorJoint Handle"));
    return b3MotorJoint_GetAngularDampingRatio(JointHandle.GetID());
}







void UBox3DJoint::WeldJoint_SetLinearHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WeldJoint_SetLinearHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,, TEXT("WeldJoint_SetLinearHertz The passed in Joint Handle is not WeldJoint Handle"));
    b3WeldJoint_SetLinearHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::WeldJoint_GetLinearHertz( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WeldJoint_GetLinearHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,  0.0f, TEXT("WeldJoint_GetLinearHertz The passed in Joint Handle is not WeldJoint Handle"));
    return b3WeldJoint_GetLinearHertz(JointHandle.GetID());
}
void UBox3DJoint::WeldJoint_SetLinearDampingRatio( const FB3JointHandle JointHandle, float Damping )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WeldJoint_SetLinearDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,, TEXT("WeldJoint_SetLinearDampingRatio The passed in Joint Handle is not WeldJoint Handle"));
    b3WeldJoint_SetLinearDampingRatio(JointHandle.GetID(), Damping);
}
float UBox3DJoint::WeldJoint_GetLinearDampingRatio( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WeldJoint_GetLinearDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,  0.0f, TEXT("WeldJoint_GetLinearDampingRatio The passed in Joint Handle is not WeldJoint Handle"));
    return b3WeldJoint_GetLinearDampingRatio(JointHandle.GetID());
}
void UBox3DJoint::WeldJoint_SetAngularHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WeldJoint_SetAngularHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,, TEXT("WeldJoint_SetAngularHertz The passed in Joint Handle is not WeldJoint Handle"));
    b3WeldJoint_SetAngularHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::WeldJoint_GetAngularHertz( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WeldJoint_GetAngularHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,  0.0f, TEXT("WeldJoint_GetAngularHertz The passed in Joint Handle is not WeldJoint Handle"));
    return b3WeldJoint_GetAngularHertz(JointHandle.GetID());
}
void UBox3DJoint::WeldJoint_SetAngularDampingRatio( const FB3JointHandle JointHandle, float Damping )
{    
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WeldJoint_SetAngularDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,, TEXT("WeldJoint_SetAngularDampingRatio The passed in Joint Handle is not WeldJoint Handle"));
    b3WeldJoint_SetAngularDampingRatio(JointHandle.GetID(), Damping);
}
float UBox3DJoint::WeldJoint_GetAngularDampingRatio( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WeldJoint_GetAngularDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WeldJoint,  0.0f, TEXT("WeldJoint_GetAngularDampingRatio The passed in Joint Handle is not WeldJoint Handle"));
    return b3WeldJoint_GetAngularDampingRatio(JointHandle.GetID());
}







void UBox3DJoint::WheelJoint_EnableSuspension( const FB3JointHandle JointHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_EnableSuspension called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_EnableSuspension The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_EnableSuspension(JointHandle.GetID(),Flag);
}
bool UBox3DJoint::WheelJoint_IsSuspensionEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("WheelJoint_IsSuspensionEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  false, TEXT("WheelJoint_IsSuspensionEnabled The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_IsSuspensionEnabled(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetSuspensionHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetSuspensionHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetSuspensionHertz The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetSuspensionHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::WheelJoint_GetSuspensionHertz( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSuspensionHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSuspensionHertz The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSuspensionHertz(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetSuspensionDampingRatio( const FB3JointHandle JointHandle, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetSuspensionDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetSuspensionDampingRatio The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetSuspensionDampingRatio(JointHandle.GetID(), DampingRatio);
}
float UBox3DJoint::WheelJoint_GetSuspensionDampingRatio( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSuspensionDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSuspensionDampingRatio The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSuspensionDampingRatio(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_EnableSuspensionLimit( const FB3JointHandle JointHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_EnableSuspensionLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_EnableSuspensionLimit The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_EnableSuspensionLimit(JointHandle.GetID(), Flag);
}
bool UBox3DJoint::WheelJoint_IsSuspensionLimitEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("WheelJoint_IsSuspensionLimitEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  false, TEXT("WheelJoint_IsSuspensionLimitEnabled The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_IsSuspensionLimitEnabled(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetLowerSuspensionLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetLowerSuspensionLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetLowerSuspensionLimit The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetLowerSuspensionLimit(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetUpperSuspensionLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetUpperSuspensionLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetUpperSuspensionLimit The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetUpperSuspensionLimit(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetSuspensionLimits( const FB3JointHandle JointHandle, float Lower, float Upper )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetSuspensionLimits called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetSuspensionLimits The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetSuspensionLimits(JointHandle.GetID(),Lower,Upper);
}
void UBox3DJoint::WheelJoint_EnableSpinMotor( const FB3JointHandle JointHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_EnableSpinMotor called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_EnableSpinMotor The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_EnableSpinMotor(JointHandle.GetID(), Flag);
}
bool UBox3DJoint::WheelJoint_IsSpinMotorEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("WheelJoint_IsSpinMotorEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  false, TEXT("WheelJoint_IsSpinMotorEnabled The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_IsSpinMotorEnabled(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetSpinMotorSpeed( const FB3JointHandle JointHandle, float Speed )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetSpinMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetSpinMotorSpeed The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetSpinMotorSpeed(JointHandle.GetID(), Speed);
}
float UBox3DJoint::WheelJoint_GetSpinMotorSpeed( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSpinMotorSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSpinMotorSpeed The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSpinMotorSpeed(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetMaxSpinTorque( const FB3JointHandle JointHandle, float Torque )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetMaxSpinTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetMaxSpinTorque The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetMaxSpinTorque(JointHandle.GetID(), Torque);
}
float UBox3DJoint::WheelJoint_GetMaxSpinTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetMaxSpinTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetMaxSpinTorque The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetMaxSpinTorque(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetSpinSpeed( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSpinSpeed called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSpinSpeed The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSpinSpeed(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetSpinTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSpinTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSpinTorque The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSpinTorque(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_EnableSteering( const FB3JointHandle JointHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_EnableSteering called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_EnableSteering The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_EnableSteering(JointHandle.GetID(), Flag);
}
bool UBox3DJoint::WheelJoint_IsSteeringEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("WheelJoint_IsSteeringEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  false, TEXT("WheelJoint_IsSteeringEnabled The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_IsSteeringEnabled(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetSteeringHertz( const FB3JointHandle JointHandle, float Hertz )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetSteeringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetSteeringHertz The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetSteeringHertz(JointHandle.GetID(), Hertz);
}
float UBox3DJoint::WheelJoint_GetSteeringHertz( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSteeringHertz called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSteeringHertz The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSteeringHertz(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetSteeringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetSteeringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetSteeringDampingRatio The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetSteeringDampingRatio(JointHandle.GetID(), DampingRatio);
}
float UBox3DJoint::WheelJoint_GetSteeringDampingRatio( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSteeringDampingRatio called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSteeringDampingRatio The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSteeringDampingRatio(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetMaxSteeringTorque( const FB3JointHandle JointHandle, float Torque )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetMaxSteeringTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetMaxSteeringTorque The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetMaxSteeringTorque(JointHandle.GetID(), Torque);
}
float UBox3DJoint::WheelJoint_GetMaxSteeringTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetMaxSteeringTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetMaxSteeringTorque The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetMaxSteeringTorque(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_EnableSteeringLimit( const FB3JointHandle JointHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_EnableSteeringLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_EnableSteeringLimit The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_EnableSteeringLimit(JointHandle.GetID(), Flag);
}
bool UBox3DJoint::WheelJoint_IsSteeringLimitEnabled( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  false, TEXT("WheelJoint_IsSteeringLimitEnabled called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  false, TEXT("WheelJoint_IsSteeringLimitEnabled The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_IsSteeringLimitEnabled(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetLowerSteeringLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetLowerSteeringLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetLowerSteeringLimit The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetLowerSteeringLimit(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetUpperSteeringLimit( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetUpperSteeringLimit called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetUpperSteeringLimit The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetUpperSteeringLimit(JointHandle.GetID());
}
void UBox3DJoint::WheelJoint_SetSteeringLimits( const FB3JointHandle JointHandle, float LowerRadians, float UpperRadians )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetSteeringLimits called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetSteeringLimits The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetSteeringLimits(JointHandle.GetID(), LowerRadians, UpperRadians);
}
void UBox3DJoint::WheelJoint_SetTargetSteeringAngle( const FB3JointHandle JointHandle, float Radians )
{
    B3_ENSURE_MSG_RET(JointHandle,, TEXT("WheelJoint_SetTargetSteeringAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,, TEXT("WheelJoint_SetTargetSteeringAngle The passed in Joint Handle is not WheelJoint Handle"));
    b3WheelJoint_SetTargetSteeringAngle(JointHandle.GetID(),Radians);
}
float UBox3DJoint::WheelJoint_GetTargetSteeringAngle( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetTargetSteeringAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetTargetSteeringAngle The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetTargetSteeringAngle(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetSteeringAngle( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSteeringAngle called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSteeringAngle The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSteeringAngle(JointHandle.GetID());
}
float UBox3DJoint::WheelJoint_GetSteeringTorque( const FB3JointHandle JointHandle )
{
    B3_ENSURE_MSG_RET(JointHandle,  0.0f, TEXT("WheelJoint_GetSteeringTorque called with an invlaid Joint Handle"));
    B3_ENSURE_MSG_RET(GetType(JointHandle) == EB3JointType::WheelJoint,  0.0f, TEXT("WheelJoint_GetSteeringTorque The passed in Joint Handle is not WheelJoint Handle"));
    return b3WheelJoint_GetSteeringTorque(JointHandle.GetID());
}
