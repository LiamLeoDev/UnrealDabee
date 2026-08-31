// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Box3DTypes.h"
#include "Box3DShape.generated.h"




UCLASS()
class BOX3DWRAPPER_API UBox3DShape : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	static void DestroyShape(FB3ShapeHandle& ShapeHandle, bool UpdateBodyMass );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsValid 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static bool IsValid(const FB3ShapeHandle ShapeHandle);
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Type 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="ShapeType") EB3ShapeType GetType(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Body 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="BodyHandle") FB3BodyHandle GetBody(const FB3ShapeHandle ShapeHandle );
	static FB3WorldHandle GetPhysicsWorld(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Sensor 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static bool IsSensor(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Name 𝘽𝙊𝙓3𝘿",AutoCreateRefTerm="Name"), Category = "Box3D|Shape")
	static void SetName(const FB3ShapeHandle ShapeHandle,const FName& Name );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Name 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Name") FName GetName(const FB3ShapeHandle ShapeHandle );

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get User Data 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="ObjRef") UObject* BP_GetUserData(const FB3ShapeHandle ShapeHandle );
	static FB3ShapeUserData* GetUserData(const FB3ShapeHandle ShapeHandle );
	static void SetUserData(const FB3ShapeHandle ShapeHandle, FB3ShapeUserData* UserData );
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Density 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static void SetDensity(const FB3ShapeHandle ShapeHandle, float Density, bool UpdateBodyMass );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Density 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Density") float GetDensity(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Friction 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static void SetFriction(const FB3ShapeHandle ShapeHandle, float Friction );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Friction 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Friction") float GetFriction(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Restitution 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static void SetRestitution(const FB3ShapeHandle ShapeHandle, float Restitution );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Restitution 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Restitution") float GetRestitution(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set SurfaceMaterial 𝘽𝙊𝙓3𝘿",AutoCreateRefTerm="SurfaceMaterial"), Category = "Box3D|Shape")
	static void SetSurfaceMaterial(const FB3ShapeHandle ShapeHandle, const FB3SurfaceMaterial& SurfaceMaterial );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get SurfaceMaterial 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="SurfaceMaterial") FB3SurfaceMaterial GetSurfaceMaterial(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mesh Material Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Count") int GetMeshMaterialCount(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Mesh Material 𝘽𝙊𝙓3𝘿",AutoCreateRefTerm="SurfaceMaterial"), Category = "Box3D|Shape")
	static void SetMeshMaterial(const FB3ShapeHandle ShapeHandle, const FB3SurfaceMaterial& SurfaceMaterial, int Index );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Mesh Surface Material 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="SurfaceMaterial") FB3SurfaceMaterial GetMeshSurfaceMaterial(const FB3ShapeHandle ShapeHandle, int Index );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Filter 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Filter") FB3Filter GetFilter(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Filter 𝘽𝙊𝙓3𝘿",AutoCreateRefTerm="Filter"), Category = "Box3D|Shape")
	static void SetFilter(const FB3ShapeHandle ShapeHandle, const FB3Filter& Filter, bool InvokeContacts );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Sensor Events 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static void EnableSensorEvents(const FB3ShapeHandle ShapeHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Are Sensor Events Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static bool AreSensorEventsEnabled(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Contact Events 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static void EnableContactEvents(const FB3ShapeHandle ShapeHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Are Contact Events Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static bool AreContactEventsEnabled(const FB3ShapeHandle ShapeHandle );
	static void EnablePreSolveEvents(const FB3ShapeHandle ShapeHandle, bool Flag );
	static bool ArePreSolveEventsEnabled(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enable Hit Events 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static void EnableHitEvents(const FB3ShapeHandle ShapeHandle, bool Flag );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Are Hit Events Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static bool AreHitEventsEnabled(const FB3ShapeHandle ShapeHandle );
	// static b3WorldCastOutput RayCast(const FB3ShapeHandle ShapeHandle,const FVector& Origin, const FVector& Translation );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sphere 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Sphere") FB3Sphere GetSphere(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Capsule 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Capsule") FB3Capsule GetCapsule(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Contact Capacity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static int GetContactCapacity(const FB3ShapeHandle ShapeHandle );
	// static int GetContactData(const FB3ShapeHandle ShapeHandle, b3ContactData* contactData, int Capacity );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sensor Capacity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Capacity") int GetSensorCapacity(const FB3ShapeHandle ShapeHandle );
	// static int GetSensorData(const FB3ShapeHandle ShapeHandle, b3ShapeId* visitorIds, int Capacity );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get AABB 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="AABB") FB3AABB GetAABB(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Compute Mass Data 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Mass Data") FB3MassData ComputeMassData(const FB3ShapeHandle ShapeHandle );
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Closest Point 𝘽𝙊𝙓3𝘿"), Category = "Box3D|Shape")
	static UPARAM(DisplayName="Point") FVector3f GetClosestPoint(const FB3ShapeHandle ShapeHandle, const FVector3f& Target );
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Wind 𝘽𝙊𝙓3𝘿",AutoCreateRefTerm="Wind"), Category = "Box3D|Shape")
	static void ApplyWind(const FB3ShapeHandle ShapeHandle, const FVector3f& Wind, float Drag, float Lift, float MaxSpeed, bool Wake );

};
#define B3SHAPE UBox3DShape