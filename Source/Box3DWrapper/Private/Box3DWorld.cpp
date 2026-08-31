// Copyright (c) 2026 LiamLeo


#include "Box3DWorld.h"
#include "Box3DTypes.h"
#include "box3d/box3d.h"
#include "Box3DCallbacks.h"
#include "Box3DAsserts.h"

namespace WorldInternal
{
    void B3Inside_DestroyWorld(FB3WorldHandle& WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("DestroyWorld called wih an invalid World Handle"));
        b3DestroyWorld(WorldHandle.GetID());
        WorldHandle = FB3WorldHandle(b3_nullWorldId);
    }
    int B3Inside_GetWorldCount()
    {
        return b3GetWorldCount();
    }
    int B3Inside_GetMaxWorldCount()
    {
        return b3GetMaxWorldCount();
    }
    bool B3Inside_WorldIsValid(const FB3WorldHandle WorldHandle)
    {
        return bool(WorldHandle);
    }
    void B3Inside_WorldStep(const FB3WorldHandle WorldHandle, float TimeStep, int SubStepCount )
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("WorldStep called wih an invalid World Handle"));
        b3World_Step(WorldHandle.GetID(), TimeStep, SubStepCount);
    }
    FB3AABB B3Inside_WorldGetBounds(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3AABB{}, TEXT("WorldGetBounds called wih an invalid World Handle"));
        return ToUnreal(b3World_GetBounds(WorldHandle.GetID()));
    }


    void B3Inside_GetBodyEvents(const FB3WorldHandle WorldHandle, TArray<FB3BodyMoveEvent>& AllBodyMoveEvents)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("GetBodyEvents called wih an invalid World Handle"));
        b3BodyEvents BodyEvents = b3World_GetBodyEvents(WorldHandle.GetID());
        AllBodyMoveEvents.Reset();
        AllBodyMoveEvents.Reserve(BodyEvents.moveCount);
        for(int32 i = 0; i < BodyEvents.moveCount; ++i)
        {
            AllBodyMoveEvents.Add(ToUnreal(BodyEvents.moveEvents[i]));
        }
    }
    void B3Inside_GetSensorEvents(const FB3WorldHandle WorldHandle, TArray<FB3SensorTouchEvent>& AllBeginSensorEvents,TArray<FB3SensorTouchEvent>& AllEndSensorEvents)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("GetSensorEvents called wih an invalid World Handle"));
        b3SensorEvents SensorEvents = b3World_GetSensorEvents(WorldHandle.GetID());
        AllBeginSensorEvents.Reset();
        AllEndSensorEvents.Reset();
        AllBeginSensorEvents.Reserve(SensorEvents.beginCount);
        AllEndSensorEvents.Reserve(SensorEvents.endCount);
        for(int32 i = 0; i < SensorEvents.beginCount; ++i)
        {
            AllBeginSensorEvents.Add(ToUnreal(SensorEvents.beginEvents[i]));
        }
        for(int32 i = 0; i < SensorEvents.endCount; ++i)
        {
            AllEndSensorEvents.Add(ToUnreal(SensorEvents.endEvents[i]));
        }
    }

    FB3RayResult B3Inside_LineTraceSingle(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End,uint32 TraceType, uint32 ObjectsToIgnore)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3RayResult{}, TEXT("LineTraceSingle called wih an invalid World Handle"));
        b3QueryFilter QueryFilter = {(static_cast<uint64_t>(TraceType) << 32),~(static_cast<uint64_t>(ObjectsToIgnore))};
        b3RayResult RayResult = b3World_CastRayClosest(WorldHandle.GetID(), ToNativePos(Start), ToNativeVec(FVector3f(End-Start)), QueryFilter);
        return ToUnreal(RayResult);
    }

    FB3RayResult B3Inside_ShapeTraceSingle(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy, uint32 TraceType, uint32 ObjectsToIgnore)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3RayResult{}, TEXT("ShapeTraceSingle called wih an invalid World Handle"));
        b3QueryFilter QueryFilter = {(static_cast<uint64_t>(TraceType) << 32),~(static_cast<uint64_t>(ObjectsToIgnore))};
        TArray<FB3RayResult> RayResults;
        const b3ShapeProxy ShapeProxyNative = ToNative(ShapeProxy);
        b3TreeStats TreeStats = b3World_CastShape(WorldHandle.GetID(), ToNativePos(Start), &ShapeProxyNative, ToNativeVec(FVector3f(End-Start)), QueryFilter, B3Callbacks::CastResultFcnSingleCallback, &RayResults);
        RayResults.Sort([](const FB3RayResult& A, const FB3RayResult& B)
        {
            return A.Fraction < B.Fraction;
        });
        return RayResults.Num() > 0? RayResults[0]: FB3RayResult{};
    }
    TArray<FB3RayResult> B3Inside_LineTraceMultiple(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End,ESortType SortType, uint32 TraceType, uint32 ObjectsToIgnore)
    {
        TArray<FB3RayResult> RayResults;
        B3_ENSURE_MSG_RET(WorldHandle, RayResults, TEXT("LineTraceMultiple called wih an invalid World Handle"));
        b3QueryFilter QueryFilter = {(static_cast<uint64_t>(TraceType) << 32),~(static_cast<uint64_t>(ObjectsToIgnore))};
        b3TreeStats TreeStats = b3World_CastRay(WorldHandle.GetID(), ToNativePos(Start), ToNativeVec(FVector3f(End-Start)),QueryFilter, B3Callbacks::CastResultFcnMultipleCallback, &RayResults);
        if(!(SortType == ESortType::None))
        {
            RayResults.Sort([SortType](const FB3RayResult& A, const FB3RayResult& B)
            {
                return SortType == ESortType::Ascending?A.Fraction < B.Fraction:A.Fraction > B.Fraction;
            });
        }
        return RayResults;
    }
    TArray<FB3RayResult> B3Inside_ShapeTraceMultiple(const FB3WorldHandle WorldHandle, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy,ESortType SortType, uint32 TraceType, uint32 ObjectsToIgnore)
    {
        TArray<FB3RayResult> RayResults;
        B3_ENSURE_MSG_RET(WorldHandle, RayResults, TEXT("ShapeTraceMultiple called wih an invalid World Handle"));
        b3QueryFilter QueryFilter = {(static_cast<uint64_t>(TraceType) << 32),~(static_cast<uint64_t>(ObjectsToIgnore))};
        const b3ShapeProxy ShapeProxyNative = ToNative(ShapeProxy);
        b3TreeStats TreeStats = b3World_CastShape(WorldHandle.GetID(), ToNativePos(Start), &ShapeProxyNative, ToNativeVec(FVector3f(End-Start)), QueryFilter, B3Callbacks::CastResultFcnMultipleCallback, &RayResults);
        if(!(SortType == ESortType::None))
        {
            RayResults.Sort([SortType](const FB3RayResult& A, const FB3RayResult& B)
            {
                return SortType == ESortType::Ascending?A.Fraction < B.Fraction:A.Fraction > B.Fraction;
            });
        }
        return RayResults;
    }
    void B3Inside_WorldEnableSleeping(const FB3WorldHandle WorldHandle, bool Flag)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("WorldEnableSleeping called wih an invalid World Handle"));
        b3World_EnableSleeping(WorldHandle.GetID(),Flag);
    }

    bool B3Inside_IsSleepingEnabled(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, false, TEXT("IsSleepingEnabled called wih an invalid World Handle"));
        return b3World_IsSleepingEnabled(WorldHandle.GetID());
    }

    void B3Inside_EnableContinuous(const FB3WorldHandle WorldHandle,bool Flag)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("EnableContinuous called wih an invalid World Handle"));
        b3World_EnableContinuous(WorldHandle.GetID(), Flag);
    }

    bool B3Inside_IsContinuousEnabled(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, false, TEXT("IsContinuousEnabled called wih an invalid World Handle"));
        return b3World_IsContinuousEnabled(WorldHandle.GetID());
    }

    void B3Inside_SetRestitutionThreshold(const FB3WorldHandle WorldHandle, float Value)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetRestitutionThreshold called wih an invalid World Handle"));
        b3World_SetRestitutionThreshold(WorldHandle.GetID(), Value);
    }

    float B3Inside_GetRestitutionThreshold(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, 0.0f, TEXT("GetRestitutionThreshold called wih an invalid World Handle"));
        return b3World_GetRestitutionThreshold(WorldHandle.GetID());
    }

    void B3Inside_SetHitEventThreshold(const FB3WorldHandle WorldHandle, float Value)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetHitEventThreshold called wih an invalid World Handle"));
        b3World_SetHitEventThreshold(WorldHandle.GetID(), Value);
    }

    float B3Inside_GetHitEventThreshold(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, 0.0f, TEXT("GetHitEventThreshold called wih an invalid World Handle"));
        return b3World_GetHitEventThreshold(WorldHandle.GetID());
    }

    void B3Inside_SetGravity(const FB3WorldHandle WorldHandle,const FVector3f& Gravity)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetGravity called wih an invalid World Handle"));
        b3World_SetGravity(WorldHandle.GetID(), ToNativeVec(Gravity));
    }

    FVector3f B3Inside_GetGravity(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FVector3f::ZeroVector, TEXT("GetGravity called wih an invalid World Handle"));
        return ToUnreal(b3World_GetGravity(WorldHandle.GetID()));
    }
    void B3Inside_ExplodeWorld(const FB3WorldHandle WorldHandle,const FB3ExplosionDef& ExplosionDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("ExplodeWorld called wih an invalid World Handle"));
        b3ExplosionDef ExplosionDefNative = ToNative(ExplosionDef);
        b3World_Explode(WorldHandle.GetID(), &ExplosionDefNative );
    }
    void B3Inside_SetContactTuning(const FB3WorldHandle WorldHandle, float Hertz, float DampingRatio, float ContactSpeed)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetContactTuning called wih an invalid World Handle"));
        b3World_SetContactTuning(WorldHandle.GetID(),Hertz,DampingRatio,ContactSpeed);
    }

    void B3Inside_SetContactRecycleDistance(const FB3WorldHandle WorldHandle, float RecycleDistance)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetContactRecycleDistance called wih an invalid World Handle"));
        b3World_SetContactRecycleDistance(WorldHandle.GetID(), RecycleDistance);
    }

    float B3Inside_GetContactRecycleDistance(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, 0.0f, TEXT("GetContactRecycleDistance called wih an invalid World Handle"));
        return b3World_GetContactRecycleDistance(WorldHandle.GetID());
    }

    void B3Inside_SetMaximumLinearSpeed(const FB3WorldHandle WorldHandle, float MaximumLinearSpeed)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetMaximumLinearSpeed called wih an invalid World Handle"));
        b3World_SetMaximumLinearSpeed(WorldHandle.GetID(), MaximumLinearSpeed);
    }

    float B3Inside_GetMaximumLinearSpeed(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, 0.0f, TEXT("GetMaximumLinearSpeed called wih an invalid World Handle"));
        return b3World_GetMaximumLinearSpeed(WorldHandle.GetID());
    }

    void B3Inside_EnableWarmStarting(const FB3WorldHandle WorldHandle, bool Flag)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("EnableWarmStarting called wih an invalid World Handle"));
        b3World_EnableWarmStarting(WorldHandle.GetID(), Flag);
    }

    bool B3Inside_IsWarmStartingEnabled(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, false, TEXT("IsWarmStartingEnabled called wih an invalid World Handle"));
        return b3World_IsWarmStartingEnabled(WorldHandle.GetID());
    }

    int B3Inside_GetAwakeBodyCount(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, 0, TEXT("GetAwakeBodyCount called wih an invalid World Handle"));
        return b3World_GetAwakeBodyCount(WorldHandle.GetID());
    }

    FB3Profile B3Inside_GetProfile(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3Profile{}, TEXT("GetProfile called wih an invalid World Handle"));
        return ToUnreal(b3World_GetProfile(WorldHandle.GetID()));
    }

    FB3Counters B3Inside_GetCounters(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3Counters{}, TEXT("GetCounters called wih an invalid World Handle"));
        return ToUnreal(b3World_GetCounters(WorldHandle.GetID()));
    }

    FB3Capacity B3Inside_GetMaxCapacity(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3Capacity{}, TEXT("GetMaxCapacity called wih an invalid World Handle"));
        return ToUnreal(b3World_GetMaxCapacity(WorldHandle.GetID()));
    }
    void B3Inside_SetFrictionCallback(const FB3WorldHandle WorldHandle, b3FrictionCallback* Callback)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetFrictionCallback called wih an invalid World Handle"));
        b3World_SetFrictionCallback(WorldHandle.GetID(), (Callback?Callback:B3Callbacks::FrictionCallback));
    }
    void B3Inside_SetRestitutionCallback(const FB3WorldHandle WorldHandle, b3RestitutionCallback* Callback)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetRestitutionCallback called wih an invalid World Handle"));
        b3World_SetRestitutionCallback(WorldHandle.GetID(), (Callback?Callback:B3Callbacks::RestitutionCallback));
    }
    void B3Inside_SetWorkerCount(const FB3WorldHandle WorldHandle, int Count)
    {
        B3_ENSURE_MSG_RET(WorldHandle,, TEXT("SetWorkerCount called wih an invalid World Handle"));
        b3World_SetWorkerCount(WorldHandle.GetID(), Count);
    }

    int B3Inside_GetWorkerCount(const FB3WorldHandle WorldHandle)
    {
        B3_ENSURE_MSG_RET(WorldHandle, 0, TEXT("GetWorkerCount called wih an invalid World Handle"));
        return b3World_GetWorkerCount(WorldHandle.GetID());
    }
}
