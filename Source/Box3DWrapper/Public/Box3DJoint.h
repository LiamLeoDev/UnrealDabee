// Copyright (c) 2026 LiamLeo

#pragma once

#include "Box3DTypes.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Box3DJoint.generated.h"


UCLASS()
class BOX3DWRAPPER_API UBox3DJoint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DestroyJoint 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void DestroyJoint( UPARAM(ref) FB3JointHandle& JointHandle, bool WakeAttached = false );
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsJointValid 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static bool IsValid( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetType 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="JointType") EB3JointType GetType( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetBodyA 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="BodyHandle") FB3BodyHandle GetBodyA( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetBodyB 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="BodyHandle") FB3BodyHandle GetBodyB( const FB3JointHandle JointHandle );

	static FB3WorldHandle GetPhysicsWorld( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetLocalFrameA 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Transform"), Category = "Box3D|Joint|Main")
	static void SetLocalFrameA( const FB3JointHandle JointHandle, const FVector3f& Location, const FQuat4f& Rotation );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetLocalFrameA 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void GetLocalFrameA( const FB3JointHandle JointHandle, FVector3f& Location, FQuat4f& Rotation );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetLocalFrameB 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Transform"), Category = "Box3D|Joint|Main")
	static void SetLocalFrameB( const FB3JointHandle JointHandle, const FVector3f& Location, const FQuat4f& Rotation );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetLocalFrameB 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void GetLocalFrameB( const FB3JointHandle JointHandle, FVector3f& Location, FQuat4f& Rotation );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetCollideConnected 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void SetCollideConnected( const FB3JointHandle JointHandle, bool ShouldCollide );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetCollideConnected 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static bool GetCollideConnected( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetUserData 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="ObjRef") UObject* BP_GetUserData(const FB3JointHandle JointHandle);
	static FB3JointUserData* GetUserData( const FB3JointHandle JointHandle );
	static void SetUserData( const FB3JointHandle JointHandle, FB3JointUserData* UserData );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WakeBodies 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void WakeBodies( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetConstraintForce 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="Force") FVector3f GetConstraintForce( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetConstraintTorque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="Torque") FVector3f GetConstraintTorque( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetLinearSeparation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="Linear") float GetLinearSeparation( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetAngularSeparation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="Angular") float GetAngularSeparation( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetConstraintTuning 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void SetConstraintTuning( const FB3JointHandle JointHandle, float Hertz, float DampingRatio );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetConstraintTuning 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void GetConstraintTuning( const FB3JointHandle JointHandle, float& Hertz, float& DampingRatio );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetForceThreshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void SetForceThreshold( const FB3JointHandle JointHandle, float Threshold );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetForceThreshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="Threshold") float GetForceThreshold( const FB3JointHandle JointHandle );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetTorqueThreshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static void SetTorqueThreshold( const FB3JointHandle JointHandle, float Threshold );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetTorqueThreshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Main")
	static UPARAM(DisplayName="Threshold") float GetTorqueThreshold( const FB3JointHandle JointHandle );
	
	








	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Set TargetAngle 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_SetTargetAngle( const FB3JointHandle JointHandle, float TargetRadians );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Get TargetAngle 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetTargetAngle( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Get Angle 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetAngle( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Get Motor Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetMotorTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Set Max Motor Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_SetMaxMotorTorque( const FB3JointHandle JointHandle, float Torque );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Get Max Motor Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetMaxMotorTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Enable Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_EnableLimit( const FB3JointHandle JointHandle, bool EnableLimit );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Is Limit Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static bool RevoluteJoint_IsLimitEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Get Lower Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetLowerLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Get Upper Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetUpperLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Set Limits 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_SetLimits( const FB3JointHandle JointHandle, float LowerLimitRadians, float UpperLimitRadians);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Set Motor Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_SetMotorSpeed( const FB3JointHandle JointHandle, float MotorSpeed );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Get Motor Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetMotorSpeed( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Enable Spring 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Is Spring Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static bool RevoluteJoint_IsSpringEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Enable Motor 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Is Motor Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static bool RevoluteJoint_IsMotorEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Set Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Get Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetSpringHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Revolute Joint Set Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static void RevoluteJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Revolute Joint Get Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|RevoluteJoint")
	static float RevoluteJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle );

	



	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parallel Joint Set Max Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|ParallelJoint")
	static void ParallelJoint_SetMaxTorque( const FB3JointHandle JointHandle, float Force );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Parallel Joint Get Max Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|ParallelJoint")
	static float ParallelJoint_GetMaxTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parallel Joint Set Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|ParallelJoint")
	static void ParallelJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Parallel Joint Get Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|ParallelJoint")
	static float ParallelJoint_GetSpringHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parallel Joint Set Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|ParallelJoint")
	static void ParallelJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Parallel Joint Get Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|ParallelJoint")
	static float ParallelJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle );
	




	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Set Length 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_SetLength( const FB3JointHandle JointHandle, float Length );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Length 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetLength( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Set Spring Force Range 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_SetSpringForceRange( const FB3JointHandle JointHandle, float LowerForce, float UpperForce );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Spring Force Range 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_GetSpringForceRange( const FB3JointHandle JointHandle, float& LowerForce, float& UpperForce );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Current Length 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetCurrentLength( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Enable Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_EnableLimit( const FB3JointHandle JointHandle, bool EnableLimit );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Is Limit Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static bool DistanceJoint_IsLimitEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Min Length 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetMinLength( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Max Length 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetMaxLength( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Set Length Range 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_SetLengthRange( const FB3JointHandle JointHandle, float MinLength, float MaxLength);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Set Max Motor Force 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_SetMaxMotorForce( const FB3JointHandle JointHandle, float Force );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Max Motor Force 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetMaxMotorForce( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Motor Force 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetMotorForce( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Set Motor Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_SetMotorSpeed( const FB3JointHandle JointHandle, float MotorSpeed );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Motor Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetMotorSpeed( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Enable Spring 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Is Spring Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static bool DistanceJoint_IsSpringEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Enable Motor 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Is Motor Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static bool DistanceJoint_IsMotorEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Set Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetSpringHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distance Joint Set Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static void DistanceJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance Joint Get Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|DistanceJoint")
	static float DistanceJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle );
	




	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Set Target Translation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_SetTargetTranslation( const FB3JointHandle JointHandle, float targetTranslation );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Target Translation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetTargetTranslation( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Translation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetTranslation( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetSpeed( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Enable Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_EnableLimit( const FB3JointHandle JointHandle, bool EnableLimit );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Is Limit Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static bool PrismaticJoint_IsLimitEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Lower Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetLowerLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Upper Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetUpperLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Set Limits 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_SetLimits( const FB3JointHandle JointHandle, float Lower, float Upper);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Set Max Motor Force 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_SetMaxMotorForce( const FB3JointHandle JointHandle, float Force );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Max Motor Force 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetMaxMotorForce( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Motor Force 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetMotorForce( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Set Motor Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_SetMotorSpeed( const FB3JointHandle JointHandle, float MotorSpeed );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Motor Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetMotorSpeed( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Enable Spring 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Is Spring Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static bool PrismaticJoint_IsSpringEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Enable Motor 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Is Motor Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static bool PrismaticJoint_IsMotorEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Set Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetSpringHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Prismatic Joint Set Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static void PrismaticJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Prismatic Joint Get Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|PrismaticJoint")
	static float PrismaticJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle );

	


	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Enable Cone Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_EnableConeLimit( const FB3JointHandle JointHandle, bool EnableLimit );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Is Cone Limit Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static bool SphericalJoint_IsConeLimitEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Cone Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetConeLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Set Cone Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_SetConeLimit( const FB3JointHandle JointHandle, float AngleRadians );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Cone Angle 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetConeAngle( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Enable Twist Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_EnableTwistLimit( const FB3JointHandle JointHandle, bool EnableLimit );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Is Twist Limit Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static bool SphericalJoint_IsTwistLimitEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Lower Twist Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetLowerTwistLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Upper Twist Limit 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetUpperTwistLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Set Twist Limits 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_SetTwistLimits( const FB3JointHandle JointHandle, float LowerLimitRadians, float UpperLimitRadians );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Twist Angle 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetTwistAngle( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Set Target Rotation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_SetTargetRotation( const FB3JointHandle JointHandle, FQuat4f TargetRotation );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Target Rotation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static FQuat4f SphericalJoint_GetTargetRotation( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Set Motor Velocity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_SetMotorVelocity( const FB3JointHandle JointHandle, const FVector3f& MotorVelocity );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Motor Velocity"), Category = "Box3D|Joint|SphericalJoint")
	static FVector3f SphericalJoint_GetMotorVelocity( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Motor Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static FVector3f SphericalJoint_GetMotorTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Set Max Motor Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_SetMaxMotorTorque( const FB3JointHandle JointHandle, float Torque );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Max Motor Torque 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetMaxMotorTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Enable Spring 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_EnableSpring( const FB3JointHandle JointHandle, bool EnableSpring );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Is Spring Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static bool SphericalJoint_IsSpringEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Enable Motor 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_EnableMotor( const FB3JointHandle JointHandle, bool EnableMotor );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Is Motor Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static bool SphericalJoint_IsMotorEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Set Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_SetSpringHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Spring Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetSpringHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spherical Joint Set Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static void SphericalJoint_SetSpringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Spherical Joint Get Spring Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|SphericalJoint")
	static float SphericalJoint_GetSpringDampingRatio( const FB3JointHandle JointHandle );
	




	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Linear Velocity"), Category = "Box3D|Joint|MotorJoint")
	static void MotorJoint_SetLinearVelocity( const FB3JointHandle JointHandle, const FVector3f& Velocity );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Linear Velocity"), Category = "Box3D|Joint|MotorJoint")
	static FVector3f MotorJoint_GetLinearVelocity( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Angular Velocity"), Category = "Box3D|Joint|MotorJoint")
	static void MotorJoint_SetAngularVelocity( const FB3JointHandle JointHandle, const FVector3f& Velocity );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Angular Velocity"), Category = "Box3D|Joint|MotorJoint")
	static FVector3f MotorJoint_GetAngularVelocity( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Max Velocity Force"), Category = "Box3D|Joint|MotorJoint")
	static void MotorJoint_SetMaxVelocityForce( const FB3JointHandle JointHandle, float MaxForce );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Max Velocity Force"), Category = "Box3D|Joint|MotorJoint")
	static float MotorJoint_GetMaxVelocityForce( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Max Velocity Torque"), Category = "Box3D|Joint|MotorJoint")
	static void MotorJoint_SetMaxVelocityTorque( const FB3JointHandle JointHandle, float MaxTorque );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Max Velocity Torque"), Category = "Box3D|Joint|MotorJoint")
	static float MotorJoint_GetMaxVelocityTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Max Spring Force"), Category = "Box3D|Joint|MotorJoint")
	static void MotorJoint_SetMaxSpringForce( const FB3JointHandle JointHandle, float MaxForce );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Max Spring Force"), Category = "Box3D|Joint|MotorJoint")
	static float MotorJoint_GetMaxSpringForce( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Max Spring Torque"), Category = "Box3D|Joint|MotorJoint")
	static void MotorJoint_SetMaxSpringTorque( const FB3JointHandle JointHandle, float MaxTorque );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Max Spring Torque"), Category = "Box3D|Joint|MotorJoint")
	static float MotorJoint_GetMaxSpringTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Linear Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static void MotorJoint_SetLinearHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Linear Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static float MotorJoint_GetLinearHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Linear Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static void MotorJoint_SetLinearDampingRatio( const FB3JointHandle JointHandle, float Damping );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Linear Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static float MotorJoint_GetLinearDampingRatio( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Angular Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static void MotorJoint_SetAngularHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Angular Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static float MotorJoint_GetAngularHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Motor Joint Set Angular Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static void MotorJoint_SetAngularDampingRatio( const FB3JointHandle JointHandle, float Damping );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Motor Joint Get Angular Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|Motor")
	static float MotorJoint_GetAngularDampingRatio( const FB3JointHandle JointHandle );
	
	



	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Weld Joint Set Linear Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static void WeldJoint_SetLinearHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Weld Joint Get Linear Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static float WeldJoint_GetLinearHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Weld Joint Set Linear Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static void WeldJoint_SetLinearDampingRatio( const FB3JointHandle JointHandle, float Damping );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Weld Joint Get Linear Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static float WeldJoint_GetLinearDampingRatio( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Weld Joint Set Angular Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static void WeldJoint_SetAngularHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Weld Joint Get Angular Hertz 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static float WeldJoint_GetAngularHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Weld Joint Set Angular Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static void WeldJoint_SetAngularDampingRatio( const FB3JointHandle JointHandle, float Damping );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Weld Joint Get Angular Damping Ratio 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Joint|WeldJoint")
	static float WeldJoint_GetAngularDampingRatio( const FB3JointHandle JointHandle );





	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Enable Suspension"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_EnableSuspension( const FB3JointHandle JointHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Is Suspension Enabled"), Category = "Box3D|Joint|WheelJoint")
	static bool WheelJoint_IsSuspensionEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Suspension Hertz"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetSuspensionHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Suspension Hertz"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSuspensionHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Suspension Damping Ratio"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetSuspensionDampingRatio( const FB3JointHandle JointHandle, float DampingRatio );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Suspension Damping Ratio"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSuspensionDampingRatio( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Enable Suspension Limit"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_EnableSuspensionLimit( const FB3JointHandle JointHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Is Suspension Limit Enabled"), Category = "Box3D|Joint|WheelJoint")
	static bool WheelJoint_IsSuspensionLimitEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Lower Suspension Limit"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetLowerSuspensionLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Upper Suspension Limit"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetUpperSuspensionLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Suspension Limits"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetSuspensionLimits( const FB3JointHandle JointHandle, float Lower, float Upper );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Enable Spin Motor"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_EnableSpinMotor( const FB3JointHandle JointHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Is Spin Motor Enabled"), Category = "Box3D|Joint|WheelJoint")
	static bool WheelJoint_IsSpinMotorEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Spin Motor Speed"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetSpinMotorSpeed( const FB3JointHandle JointHandle, float Speed );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Spin Motor Speed"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSpinMotorSpeed( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Max Spin Torque"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetMaxSpinTorque( const FB3JointHandle JointHandle, float Torque );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Max Spin Torque"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetMaxSpinTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Spin Speed"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSpinSpeed( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Spin Torque"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSpinTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Enable Steering"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_EnableSteering( const FB3JointHandle JointHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Is Steering Enabled"), Category = "Box3D|Joint|WheelJoint")
	static bool WheelJoint_IsSteeringEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Steering Hertz"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetSteeringHertz( const FB3JointHandle JointHandle, float Hertz );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Steering Hertz"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSteeringHertz( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Steering Damping Ratio"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetSteeringDampingRatio( const FB3JointHandle JointHandle, float DampingRatio );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Steering Damping Ratio"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSteeringDampingRatio( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Max Steering Torque"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetMaxSteeringTorque( const FB3JointHandle JointHandle, float Torque );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Max Steering Torque"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetMaxSteeringTorque( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Enable Steering Limit"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_EnableSteeringLimit( const FB3JointHandle JointHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Is Steering Limit Enabled"), Category = "Box3D|Joint|WheelJoint")
	static bool WheelJoint_IsSteeringLimitEnabled( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Lower Steering Limit"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetLowerSteeringLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Upper Steering Limit"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetUpperSteeringLimit( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Steering Limits"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetSteeringLimits( const FB3JointHandle JointHandle, float LowerRadians, float UpperRadians );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Wheel Joint Set Target Steering Angle"), Category = "Box3D|Joint|WheelJoint")
	static void WheelJoint_SetTargetSteeringAngle( const FB3JointHandle JointHandle, float Radians );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Target Steering Angle"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetTargetSteeringAngle( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Steering Angle"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSteeringAngle( const FB3JointHandle JointHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Wheel Joint Get Steering Torque"), Category = "Box3D|Joint|WheelJoint")
	static float WheelJoint_GetSteeringTorque( const FB3JointHandle JointHandle );
};

#define B3JOINT UBox3DJoint