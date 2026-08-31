// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Box3DTypes.h"
#include "Engine/World.h"
#include "Box3DWorldLibrary.generated.h"



UCLASS()
class BOX3DRUNTIME_API UBox3DWorldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	static void DestroyWorld(UWorld* World);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get World Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="Count") int BP_GetWorldCount();
	static int GetWorldCount();

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Max World Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="MaxCount") int BP_GetMaxWorldCount();
	static int GetMaxWorldCount();

	static bool WorldIsValid(UWorld* World);
	static void WorldStep(UWorld* World,float TimeStep, int SubStepCount);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get World Bounds 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="AABB") FB3AABB BP_WorldGetBounds(const UObject* WorldContextObject);
	static FB3AABB WorldGetBounds(UWorld* World);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Body Events 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_GetBodyEvents(const UObject* WorldContextObject,TArray<FB3BodyMoveEvent>& AllBodyMoveEvents);
	static void GetBodyEvents(UWorld* World,TArray<FB3BodyMoveEvent>& AllBodyMoveEvents);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Sensor Events 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_GetSensorEvents(const UObject* WorldContextObject,TArray<FB3SensorTouchEvent>& AllBeginSensorEvents,TArray<FB3SensorTouchEvent>& AllEndSensorEvents);
	static void GetSensorEvents(UWorld* World,TArray<FB3SensorTouchEvent>& AllBeginSensorEvents,TArray<FB3SensorTouchEvent>& AllEndSensorEvents);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Line Trace Single 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Start,End"), Category = "Box3D|World")
	static UPARAM(DisplayName="RayResult") FB3RayResult BP_LineTraceSingle(const UObject* WorldContextObject,const FVector& Start, const FVector& End,UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3TraceFlags")) int32 TraceType = 1, UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3ObjectFlags")) int32 ObjectsToIgnore = 0);
	static FB3RayResult LineTraceSingle(UWorld* World, const FVector& Start, const FVector& End, uint32 TraceType = 1, uint32 ObjectsToIgnore = 0);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Line Trace Multiple 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Start,End,SortType"), Category = "Box3D|World")
	static UPARAM(DisplayName="RayResults") TArray<FB3RayResult> BP_LineTraceMultiple(const UObject* WorldContextObject,const FVector& Start, const FVector& End, ESortType SortType = ESortType::None,UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3TraceFlags")) int32 TraceType = 1, UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3ObjectFlags")) int32 ObjectsToIgnore = 0);
	static TArray<FB3RayResult> LineTraceMultiple(UWorld* World,const FVector& Start, const FVector& End, ESortType SortType = ESortType::None, uint32 TraceType = 1, uint32 ObjectsToIgnore = 0);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Shape Trace Single 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Start,End"), Category = "Box3D|World")
	static UPARAM(DisplayName="RayResult") FB3RayResult BP_ShapeTraceSingle(const UObject* WorldContextObject,const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy,UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3TraceFlags")) int32 TraceType = 1, UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3ObjectFlags")) int32 ObjectsToIgnore = 0);
	static FB3RayResult ShapeTraceSingle(UWorld* World,const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy, uint32 TraceType = 1, uint32 ObjectsToIgnore = 0);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Shape Trace Multiple 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Start,End,SortType"), Category = "Box3D|World")
	static UPARAM(DisplayName="RayResults") TArray<FB3RayResult> BP_ShapeTraceMultiple(const UObject* WorldContextObject,const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy, ESortType SortType = ESortType::None,UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3TraceFlags")) int32 TraceType = 1, UPARAM(meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3ObjectFlags")) int32 ObjectsToIgnore = 0);
	static TArray<FB3RayResult> ShapeTraceMultiple(UWorld* World,const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy, ESortType SortType = ESortType::None, uint32 TraceType = 1, uint32 ObjectsToIgnore = 0);

	static void WorldEnableSleeping(UWorld* World, bool Flag);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Is Sleeping Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static bool BP_IsSleepingEnabled(const UObject* WorldContextObject);
	static bool IsSleepingEnabled(UWorld* World);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Enable Continuous 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_EnableContinuous(const UObject* WorldContextObject,bool Flag);
	static void EnableContinuous(UWorld* World, bool Flag);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Is Continuous Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static bool BP_IsContinuousEnabled(const UObject* WorldContextObject);
	static bool IsContinuousEnabled(UWorld* World);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Set Restitution Threshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_SetRestitutionThreshold(const UObject* WorldContextObject,float Value);
	static void SetRestitutionThreshold(UWorld* World,float Value);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Restitution Threshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static float BP_GetRestitutionThreshold(const UObject* WorldContextObject);
	static float GetRestitutionThreshold(UWorld* World);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Set Hit Event Threshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_SetHitEventThreshold(const UObject* WorldContextObject,float Value);
	static void SetHitEventThreshold(UWorld* World,float Value);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Hit Event Threshold 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static float BP_GetHitEventThreshold(const UObject* WorldContextObject);
	static float GetHitEventThreshold(UWorld* World);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Set Gravity 𝘽𝙊𝙓3𝘿", AutoCreateRefTerm="Gravity"), Category = "Box3D|World")
	static void BP_SetGravity(const UObject* WorldContextObject,const FVector3f& Gravity);
	static void SetGravity(UWorld* World,const FVector3f& Gravity);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Gravity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="Gravity") FVector3f BP_GetGravity(const UObject* WorldContextObject);
	static FVector3f GetGravity(UWorld* World);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Explode World 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_ExplodeWorld(const UObject* WorldContextObject, const FB3ExplosionDef& ExplosionDef);
	static void ExplodeWorld(UWorld* World, const FB3ExplosionDef& ExplosionDef);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Set Contact Tuning 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_SetContactTuning(const UObject* WorldContextObject, float Hertz, float DampingRatio, float ContactSpeed);
	static void SetContactTuning(UWorld* World, float Hertz, float DampingRatio, float ContactSpeed);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Set Contact Recycle Distance 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_SetContactRecycleDistance(const UObject* WorldContextObject, float RecycleDistance);
	static void SetContactRecycleDistance(UWorld* World, float RecycleDistance);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Contact Recycle Distance 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static float BP_GetContactRecycleDistance(const UObject* WorldContextObject);
	static float GetContactRecycleDistance(UWorld* World);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Set Maximum Linear Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_SetMaximumLinearSpeed(const UObject* WorldContextObject,float MaximumLinearSpeed);
	static void SetMaximumLinearSpeed(UWorld* World,float MaximumLinearSpeed);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Maximum Linear Speed 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static float BP_GetMaximumLinearSpeed(const UObject* WorldContextObject);
	static float GetMaximumLinearSpeed(UWorld* World);

	static void EnableWarmStarting(UWorld* World,bool Flag);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Is Warm Starting Enabled 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static bool BP_IsWarmStartingEnabled(const UObject* WorldContextObject);
	static bool IsWarmStartingEnabled(UWorld* World);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Awake Body Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="Count") int BP_GetAwakeBodyCount(const UObject* WorldContextObject);
	static int GetAwakeBodyCount(UWorld* World);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Profile 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="Profile") FB3Profile BP_GetProfile(const UObject* WorldContextObject);
	static FB3Profile GetProfile(UWorld* World);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Counters 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="Counters") FB3Counters BP_GetCounters(const UObject* WorldContextObject);
	static FB3Counters GetCounters(UWorld* World);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Max Capacity 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="Capacity") FB3Capacity BP_GetMaxCapacity(const UObject* WorldContextObject);
	static FB3Capacity GetMaxCapacity(UWorld* World);

	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", DisplayName = "Set Worker Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static void BP_SetWorkerCount(const UObject* WorldContextObject,int Count);
	static void SetWorkerCount(UWorld* World,int Count);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContextObject", DisplayName = "Get Worker Count 𝘽𝙊𝙓3𝘿"), Category = "Box3D|World")
	static UPARAM(DisplayName="Count") int BP_GetWorkerCount(const UObject* WorldContextObject);
	static int GetWorkerCount(UWorld* World);
	

	static void SetFrictionCallback(UWorld* World, b3FrictionCallback* Callback = nullptr);
	static void SetRestitutionCallback(UWorld* World, b3RestitutionCallback* Callback = nullptr);
	
	// static void SetUserData(void* userData);

	// static void* GetUserData();

};

#define B3WORLD UBox3DWorldLibrary