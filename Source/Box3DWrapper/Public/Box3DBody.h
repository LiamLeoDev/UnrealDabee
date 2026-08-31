// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Box3DTypes.h"
#include "Box3DBody.generated.h"




UCLASS()
class BOX3DWRAPPER_API UBox3DBody : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()

public:	
	static void DestroyBody(FB3BodyHandle& BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get IsValid 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static bool IsValid(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Body Type 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetType(const FB3BodyHandle BodyHandle,const EB3BodyType Type);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Body Name 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Name"), Category = "Box3D|Body")
	static void SetName(const FB3BodyHandle BodyHandle, const FName& Name);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Body Name 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Name") FName GetName(const FB3BodyHandle BodyHandle);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get User Data 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="ObjRef") UObject* BP_GetUserData(const FB3BodyHandle BodyHandle);
	static FB3BodyUserData* GetUserData(const FB3BodyHandle BodyHandle);
	static void SetUserData(const FB3BodyHandle BodyHandle,FB3BodyUserData* UserData);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Body Type 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="BodyType") EB3BodyType GetType(const FB3BodyHandle BodyHandle);

	static FVector GetPosition(const FB3BodyHandle BodyHandle);
	static FQuat4f GetRotation(const FB3BodyHandle BodyHandle);
	static FTransform GetTransform(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Transform 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Transform"), Category = "Box3D|Body")
	static void SetTransform(const FB3BodyHandle BodyHandle,const FTransform& Transform);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Local Point 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="WorldPoint"), Category = "Box3D|Body")
	static UPARAM(DisplayName="LocalPoint") FVector3f GetLocalPoint(const FB3BodyHandle BodyHandle,const FVector& WorldPoint);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get World Point 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="LocalPoint"), Category = "Box3D|Body")
	static UPARAM(DisplayName="WorldPoint") FVector GetWorldPoint(const FB3BodyHandle BodyHandle,const FVector3f& LocalPoint);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Local Vector 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="WorldVector"), Category = "Box3D|Body")
	static UPARAM(DisplayName="LocalVector") FVector3f GetLocalVector(const FB3BodyHandle BodyHandle,const FVector3f& WorldVector);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get World Vector 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="LocalVector"), Category = "Box3D|Body")
	static UPARAM(DisplayName="WorldVector") FVector3f GetWorldVector(const FB3BodyHandle BodyHandle,const FVector3f& LocalVector);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Linear Velocity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="LinearVelocity") FVector3f GetLinearVelocity(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Linear Velocity 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Velocity"), Category = "Box3D|Body")
	static void SetLinearVelocity(const FB3BodyHandle BodyHandle,const FVector3f& Velocity);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Angular Velocity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="AngularVelocity") FVector3f GetAngularVelocity(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Angular Velocity 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Velocity"), Category = "Box3D|Body")
	static void SetAngularVelocity(const FB3BodyHandle BodyHandle,const FVector3f& Velocity);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Target Transform 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Transform"), Category = "Box3D|Body")
	static void SetTargetTransform(const FB3BodyHandle BodyHandle,const FTransform& Transform, float TimeStep, bool Wake);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Local Point Velocity 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="LocalPoint"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Vec") FVector3f GetLocalPointVelocity(const FB3BodyHandle BodyHandle,const FVector3f& LocalPoint);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get World Point Velocity 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="WorldPoint"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Vec") FVector3f GetWorldPointVelocity(const FB3BodyHandle BodyHandle,const FVector& WorldPoint);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Force 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Force,Point"), Category = "Box3D|Body")
	static void ApplyForce(const FB3BodyHandle BodyHandle,const FVector3f& Force,const FVector& Point, bool Wake);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Force To Center 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Force"), Category = "Box3D|Body")
	static void ApplyForceToCenter(const FB3BodyHandle BodyHandle,const FVector3f& Force, bool Wake);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Torque 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Torque"), Category = "Box3D|Body")
	static void ApplyTorque(const FB3BodyHandle BodyHandle,const FVector3f& Torque, bool Wake);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Linear Impulse 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Impulse,Point"), Category = "Box3D|Body")
	static void ApplyLinearImpulse(const FB3BodyHandle BodyHandle,const FVector3f& Impulse,const FVector& Point, bool Wake);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Linear Impulse To Center 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Impulse"), Category = "Box3D|Body")
	static void ApplyLinearImpulseToCenter(const FB3BodyHandle BodyHandle,const FVector3f& Impulse, bool Wake);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Angular Impulse 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Impulse"), Category = "Box3D|Body")
	static void ApplyAngularImpulse(const FB3BodyHandle BodyHandle,const FVector3f& Impulse, bool Wake);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mass 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Mass") float GetMass(const FB3BodyHandle BodyHandle);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Local Rotational Inertia 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Inertia3x3") FMatrix GetLocalRotationalInertia(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get World Inverse Rotational Inertia 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Inertia3x3") FMatrix GetWorldInverseRotationalInertia(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Inverse Mass 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="InverseMass") float GetInverseMass(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Local Center 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Vec") FVector3f GetLocalCenter(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get World Center 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Vec") FVector GetWorldCenter(const FB3BodyHandle BodyHandle);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Mass Data 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetMassData(const FB3BodyHandle BodyHandle, const FB3MassData& MassData );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mass Data 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="MassData") FB3MassData GetMassData(const FB3BodyHandle BodyHandle );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Mass From Shapes 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void ApplyMassFromShapes(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Linear Damping 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetLinearDamping(const FB3BodyHandle BodyHandle, float LinearDamping);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Angular Damping 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetAngularDamping(const FB3BodyHandle BodyHandle, float AngularDamping);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Linear Damping 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="LinearDamping") float GetLinearDamping(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Angular Damping 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="AngularDamping") float GetAngularDamping(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Gravity Scale 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetGravityScale(const FB3BodyHandle BodyHandle, float GravityScale);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Gravity Scale 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="GravityScale") float GetGravityScale(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Awake 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static bool IsAwake(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Awake 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetAwake(const FB3BodyHandle BodyHandle, bool Awake);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Sleep 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void EnableSleep(const FB3BodyHandle BodyHandle, bool EnableSleep);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Sleep Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static bool IsSleepEnabled(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Sleep Threshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetSleepThreshold(const FB3BodyHandle BodyHandle, float SleepThreshold);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sleep Threshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static float GetSleepThreshold(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static bool IsEnabled(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disable Body 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void Disable(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Body 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void Enable(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Motion Locks 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetMotionLocks(const FB3BodyHandle BodyHandle,const FB3MotionLocks MotionLocks);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Motion Locks 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="MotionLocks") FB3MotionLocks GetMotionLocks(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Bullet 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void SetBullet(const FB3BodyHandle BodyHandle, bool Flag);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Bullet 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static bool IsBullet(const FB3BodyHandle BodyHandle);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Allow Fast Rotation 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void AllowFastRotation(const FB3BodyHandle BodyHandle, bool Flag );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Fast Rotation Allowed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static bool IsFastRotationAllowed(const FB3BodyHandle BodyHandle );

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Contact Recycling 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void EnableContactRecycling(const FB3BodyHandle BodyHandle, bool Flag);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Contact Recycling Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static bool IsContactRecyclingEnabled(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Hit Events 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void EnableHitEvents(const FB3BodyHandle BodyHandle, bool Flag);

	static FB3WorldHandle GetPhysicsWorld(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Shape Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Count") int32 GetShapeCount(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Shapes 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void GetShapes(const FB3BodyHandle BodyHandle, TArray<FB3ShapeHandle>& OutShapeHandles);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Joints 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static void GetJoints(const FB3BodyHandle BodyHandle, TArray<FB3JointHandle>& OutJointHandles);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Joint Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Count") int32 GetJointCount(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Contact Capacity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="Capacity") int32 GetContactCapacity(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Compute AABB 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Body")
	static UPARAM(DisplayName="AABB") FB3AABB ComputeAABB(const FB3BodyHandle BodyHandle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Closest Point 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="OutPoint,Target"), Category = "Box3D|Body")
	static void GetClosestPoint(const FB3BodyHandle BodyHandle, UPARAM(DisplayName = "Point") FVector3f& OutPoint,const FVector3f& Target);
};

#define B3BODY UBox3DBody