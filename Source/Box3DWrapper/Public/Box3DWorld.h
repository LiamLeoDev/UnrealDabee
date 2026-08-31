// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Box3DTypes.h"


namespace WorldInternal
{
	BOX3DWRAPPER_API void B3Inside_DestroyWorld(FB3WorldHandle& WorldHandle);
	BOX3DWRAPPER_API int B3Inside_GetWorldCount();
	BOX3DWRAPPER_API int B3Inside_GetMaxWorldCount();
	BOX3DWRAPPER_API bool B3Inside_WorldIsValid(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_WorldStep(const FB3WorldHandle WorldHandle, float TimeStep, int SubStepCount);
	BOX3DWRAPPER_API FB3AABB B3Inside_WorldGetBounds(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_GetBodyEvents(const FB3WorldHandle WorldHandle, TArray<FB3BodyMoveEvent>& AllBodyMoveEvents);
	BOX3DWRAPPER_API void B3Inside_GetSensorEvents(const FB3WorldHandle WorldHandle, TArray<FB3SensorTouchEvent>& AllBeginSensorEvents,TArray<FB3SensorTouchEvent>& AllEndSensorEvents);
	BOX3DWRAPPER_API FB3RayResult B3Inside_LineTraceSingle(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End,uint32 TraceType, uint32 ObjectsToIgnore);
	BOX3DWRAPPER_API TArray<FB3RayResult> B3Inside_LineTraceMultiple(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End, ESortType SortType, uint32 TraceType, uint32 ObjectsToIgnore);
	BOX3DWRAPPER_API FB3RayResult B3Inside_ShapeTraceSingle(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy,uint32 TraceType, uint32 ObjectsToIgnore);
	BOX3DWRAPPER_API TArray<FB3RayResult> B3Inside_ShapeTraceMultiple(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy, ESortType SortType, uint32 TraceType, uint32 ObjectsToIgnore);
	BOX3DWRAPPER_API void B3Inside_WorldEnableSleeping(const FB3WorldHandle WorldHandle, bool Flag);
	BOX3DWRAPPER_API bool B3Inside_IsSleepingEnabled(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_EnableContinuous(const FB3WorldHandle WorldHandle, bool Flag);
	BOX3DWRAPPER_API bool B3Inside_IsContinuousEnabled(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_SetRestitutionThreshold(const FB3WorldHandle WorldHandle, float Value);
	BOX3DWRAPPER_API float B3Inside_GetRestitutionThreshold(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_SetHitEventThreshold(const FB3WorldHandle WorldHandle, float Value);
	BOX3DWRAPPER_API float B3Inside_GetHitEventThreshold(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_SetGravity(const FB3WorldHandle WorldHandle, const FVector3f& Gravity);
	BOX3DWRAPPER_API FVector3f B3Inside_GetGravity(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_ExplodeWorld(const FB3WorldHandle WorldHandle, const FB3ExplosionDef& ExplosionDef);
	BOX3DWRAPPER_API void B3Inside_SetContactTuning(const FB3WorldHandle WorldHandle, float Hertz, float DampingRatio, float ContactSpeed);
	BOX3DWRAPPER_API void B3Inside_SetContactRecycleDistance(const FB3WorldHandle WorldHandle, float RecycleDistance);
	BOX3DWRAPPER_API float B3Inside_GetContactRecycleDistance(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_SetMaximumLinearSpeed(const FB3WorldHandle WorldHandle, float MaximumLinearSpeed);
	BOX3DWRAPPER_API float B3Inside_GetMaximumLinearSpeed(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_EnableWarmStarting(const FB3WorldHandle WorldHandle, bool Flag);
	BOX3DWRAPPER_API bool B3Inside_IsWarmStartingEnabled(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API int B3Inside_GetAwakeBodyCount(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API FB3Profile B3Inside_GetProfile(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API FB3Counters B3Inside_GetCounters(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API FB3Capacity B3Inside_GetMaxCapacity(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_SetWorkerCount(const FB3WorldHandle WorldHandle, int Count);
	BOX3DWRAPPER_API int B3Inside_GetWorkerCount(const FB3WorldHandle WorldHandle);
	BOX3DWRAPPER_API void B3Inside_SetFrictionCallback(const FB3WorldHandle WorldHandle, b3FrictionCallback* Callback = nullptr);
	BOX3DWRAPPER_API void B3Inside_SetRestitutionCallback(const FB3WorldHandle WorldHandle, b3RestitutionCallback* Callback = nullptr);
}