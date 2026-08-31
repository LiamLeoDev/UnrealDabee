// Copyright (c) 2026 LiamLeo


#include "Box3DWorldLibrary.h"
#include "Box3DTypes.h"
#include "Box3DWorld.h"
#include "Box3DWorldSubsystem.h"
#include "Box3DRuntimeLogging.h"
#include "Engine/Engine.h" 
#include "Engine/World.h" 
#include "Engine/EngineTypes.h"
#include "Box3DAsserts.h"

void UBox3DWorldLibrary::DestroyWorld(UWorld* World)
{
    B3_ENSURE_MSG(World, TEXT("DestroyWorld called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("DestroyWorld is called but Box3DWorldSubsystem is null or not supported in this world!"));
    B3_ENSURE_MSG(B3WORLD::WorldIsValid(World), TEXT("DestroyWorld is called but The World is already destroyed"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_DestroyWorld(Subsystem->GetWorldHandle());
    }
}



int UBox3DWorldLibrary::BP_GetWorldCount()
{
    return B3WORLD::GetWorldCount();
}
int UBox3DWorldLibrary::GetWorldCount()
{
    return WorldInternal::B3Inside_GetWorldCount();
}




int UBox3DWorldLibrary::BP_GetMaxWorldCount()
{
    return B3WORLD::GetMaxWorldCount();
}
int UBox3DWorldLibrary::GetMaxWorldCount()
{
    return WorldInternal::B3Inside_GetMaxWorldCount();
}





bool UBox3DWorldLibrary::WorldIsValid(UWorld* World)
{
    B3_ENSURE_MSG(World, TEXT("WorldIsValid called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("WorldIsValid is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return bool(Subsystem->GetWorldHandle());
    }
    return false;
}




void UBox3DWorldLibrary::WorldStep(UWorld* World, float TimeStep, int SubStepCount )
{
    B3_ENSURE_MSG(World, TEXT("WorldStep called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("WorldStep is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_WorldStep(Subsystem->GetWorldHandle(), TimeStep, SubStepCount);
    }
}



FB3AABB UBox3DWorldLibrary::BP_WorldGetBounds(const UObject* WorldContextObject)
{
    return B3WORLD::WorldGetBounds(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
FB3AABB UBox3DWorldLibrary::WorldGetBounds(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, FB3AABB{}, TEXT("WorldGetBounds called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, FB3AABB{}, TEXT("WorldGetBounds is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_WorldGetBounds(Subsystem->GetWorldHandle());
    }
    return FB3AABB{};
}

void UBox3DWorldLibrary::BP_GetBodyEvents(const UObject* WorldContextObject,TArray<FB3BodyMoveEvent>& AllBodyMoveEvents)
{
    return B3WORLD::GetBodyEvents(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull),AllBodyMoveEvents);
}
void UBox3DWorldLibrary::GetBodyEvents(UWorld* World,TArray<FB3BodyMoveEvent>& AllBodyMoveEvents)
{
    B3_ENSURE_MSG(World, TEXT("GetBodyEvents called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("GetBodyEvents is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_GetBodyEvents(Subsystem->GetWorldHandle(), AllBodyMoveEvents);
    }
}
void UBox3DWorldLibrary::BP_GetSensorEvents(const UObject* WorldContextObject,TArray<FB3SensorTouchEvent>& AllBeginSensorEvents,TArray<FB3SensorTouchEvent>& AllEndSensorEvents)
{
    return B3WORLD::GetSensorEvents(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), AllBeginSensorEvents, AllEndSensorEvents);
}
void UBox3DWorldLibrary::GetSensorEvents(UWorld* World,TArray<FB3SensorTouchEvent>& AllBeginSensorEvents,TArray<FB3SensorTouchEvent>& AllEndSensorEvents)
{
    B3_ENSURE_MSG(World, TEXT("GetSensorEvents called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("GetSensorEvents is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_GetSensorEvents(Subsystem->GetWorldHandle(), AllBeginSensorEvents, AllEndSensorEvents);
    }
}



FB3RayResult UBox3DWorldLibrary::BP_LineTraceSingle(const UObject* WorldContextObject, const FVector& Start, const FVector& End, int32 TraceType, int32 ObjectsToIgnore)
{
    return B3WORLD::LineTraceSingle(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Start, End, TraceType, ObjectsToIgnore);
}
FB3RayResult UBox3DWorldLibrary::LineTraceSingle(UWorld* World, const FVector& Start, const FVector& End, uint32 TraceType, uint32 ObjectsToIgnore)
{
    B3_ENSURE_MSG_RET(World, FB3RayResult{}, TEXT("LineTraceSingle called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, FB3RayResult{}, TEXT("LineTraceSingle is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return  WorldInternal::B3Inside_LineTraceSingle(Subsystem->GetWorldHandle(), Start, End, TraceType, ObjectsToIgnore);
    }
    return FB3RayResult{};
}



FB3RayResult UBox3DWorldLibrary::BP_ShapeTraceSingle(const UObject* WorldContextObject, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy, int32 TraceType, int32 ObjectsToIgnore)
{
    return B3WORLD::ShapeTraceSingle(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Start, End, ShapeProxy, TraceType, ObjectsToIgnore);
}
FB3RayResult UBox3DWorldLibrary::ShapeTraceSingle(UWorld* World, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy, uint32 TraceType, uint32 ObjectsToIgnore)
{
    B3_ENSURE_MSG_RET(World, FB3RayResult{}, TEXT("ShapeTraceSingle called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, FB3RayResult{}, TEXT("ShapeTraceSingle is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_ShapeTraceSingle(Subsystem->GetWorldHandle(), Start, End, ShapeProxy, TraceType, ObjectsToIgnore);
    }
    return FB3RayResult{};
}




TArray<FB3RayResult> UBox3DWorldLibrary::BP_LineTraceMultiple(const UObject* WorldContextObject, const FVector& Start, const FVector& End,ESortType SortType, int32 TraceType, int32 ObjectsToIgnore)
{
    return B3WORLD::LineTraceMultiple(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Start, End,SortType, TraceType, ObjectsToIgnore);
}
TArray<FB3RayResult> UBox3DWorldLibrary::LineTraceMultiple(UWorld* World, const FVector& Start, const FVector& End,ESortType SortType, uint32 TraceType, uint32 ObjectsToIgnore)
{
    B3_ENSURE_MSG_RET(World, TArray<FB3RayResult>{}, TEXT("LineTraceMultiple called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, TArray<FB3RayResult>{}, TEXT("LineTraceMultiple is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_LineTraceMultiple(Subsystem->GetWorldHandle(), Start, End, SortType, TraceType, ObjectsToIgnore);
    }
    return TArray<FB3RayResult>{};
}




TArray<FB3RayResult> UBox3DWorldLibrary::BP_ShapeTraceMultiple(const UObject* WorldContextObject, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy,ESortType SortType, int32 TraceType, int32 ObjectsToIgnore)
{
    return B3WORLD::ShapeTraceMultiple(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Start, End, ShapeProxy,SortType, TraceType, ObjectsToIgnore);
}
TArray<FB3RayResult> UBox3DWorldLibrary::ShapeTraceMultiple(UWorld* World, const FVector& Start, const FVector& End, const FB3ShapeProxy& ShapeProxy,ESortType SortType, uint32 TraceType, uint32 ObjectsToIgnore)
{
    B3_ENSURE_MSG_RET(World, TArray<FB3RayResult>{}, TEXT("ShapeTraceMultiple called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, TArray<FB3RayResult>{}, TEXT("ShapeTraceMultiple is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {   
        return WorldInternal::B3Inside_ShapeTraceMultiple(Subsystem->GetWorldHandle(), Start, End, ShapeProxy,SortType, TraceType, ObjectsToIgnore);
    }
    return TArray<FB3RayResult>{};
}





void UBox3DWorldLibrary::WorldEnableSleeping(UWorld* World, bool Flag)
{
    B3_ENSURE_MSG(World, TEXT("WorldEnableSleeping called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("WorldEnableSleeping is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_WorldEnableSleeping(Subsystem->GetWorldHandle(), Flag);
    }
}




bool UBox3DWorldLibrary::BP_IsSleepingEnabled(const UObject* WorldContextObject)
{
    return B3WORLD::IsSleepingEnabled(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
bool UBox3DWorldLibrary::IsSleepingEnabled(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, false, TEXT("IsSleepingEnabled called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, false, TEXT("IsSleepingEnabled is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_IsSleepingEnabled(Subsystem->GetWorldHandle());
    }
	return false;
}





void UBox3DWorldLibrary::BP_EnableContinuous(const UObject* WorldContextObject, bool Flag)
{
    B3WORLD::EnableContinuous(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Flag);
}
void UBox3DWorldLibrary::EnableContinuous(UWorld* World, bool Flag)
{
    B3_ENSURE_MSG(World, TEXT("EnableContinuous called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("EnableContinuous is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_EnableContinuous(Subsystem->GetWorldHandle(), Flag);
    }
}





bool UBox3DWorldLibrary::BP_IsContinuousEnabled(const UObject* WorldContextObject)
{
    return B3WORLD::IsContinuousEnabled(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
bool UBox3DWorldLibrary::IsContinuousEnabled(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, false, TEXT("IsContinuousEnabled called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, false, TEXT("IsContinuousEnabled is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_IsContinuousEnabled(Subsystem->GetWorldHandle());
    }
	return false;
}





void UBox3DWorldLibrary::BP_SetRestitutionThreshold(const UObject* WorldContextObject, float Value)
{
    B3WORLD::SetRestitutionThreshold(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Value);
}
void UBox3DWorldLibrary::SetRestitutionThreshold(UWorld* World, float Value)
{
    B3_ENSURE_MSG(World, TEXT("SetRestitutionThreshold called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetRestitutionThreshold is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetRestitutionThreshold(Subsystem->GetWorldHandle(), Value);
    }
}





float UBox3DWorldLibrary::BP_GetRestitutionThreshold(const UObject* WorldContextObject)
{
    return B3WORLD::GetRestitutionThreshold(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
float UBox3DWorldLibrary::GetRestitutionThreshold(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, 0.0f, TEXT("GetRestitutionThreshold called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, 0.0f, TEXT("GetRestitutionThreshold is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetRestitutionThreshold(Subsystem->GetWorldHandle());
    }
    return 0.0f;
}





void UBox3DWorldLibrary::BP_SetHitEventThreshold(const UObject* WorldContextObject, float Value)
{
    B3WORLD::SetHitEventThreshold(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Value);
}
void UBox3DWorldLibrary::SetHitEventThreshold(UWorld* World, float Value)
{
    B3_ENSURE_MSG(World, TEXT("SetHitEventThreshold called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetHitEventThreshold is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetHitEventThreshold(Subsystem->GetWorldHandle(), Value);
    }
}





float UBox3DWorldLibrary::BP_GetHitEventThreshold(const UObject* WorldContextObject)
{
    return B3WORLD::GetHitEventThreshold(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
float UBox3DWorldLibrary::GetHitEventThreshold(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, 0.0f, TEXT("GetHitEventThreshold called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, 0.0f, TEXT("GetHitEventThreshold is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetHitEventThreshold(Subsystem->GetWorldHandle());
    }
    return 0.0f;
}





void UBox3DWorldLibrary::BP_SetGravity(const UObject* WorldContextObject, const FVector3f& Gravity)
{
    B3WORLD::SetGravity(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Gravity);
}
void UBox3DWorldLibrary::SetGravity(UWorld* World, const FVector3f& Gravity)
{
    B3_ENSURE_MSG(World, TEXT("SetGravity called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetGravity is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetGravity(Subsystem->GetWorldHandle(), Gravity);
    }
}





FVector3f UBox3DWorldLibrary::BP_GetGravity(const UObject* WorldContextObject)
{
    return B3WORLD::GetGravity(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
FVector3f UBox3DWorldLibrary::GetGravity(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, FVector3f::ZeroVector, TEXT("GetGravity called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, FVector3f::ZeroVector, TEXT("GetGravity is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetGravity(Subsystem->GetWorldHandle());
    }
	return FVector3f::ZeroVector;
}




void UBox3DWorldLibrary::BP_ExplodeWorld(const UObject* WorldContextObject, const FB3ExplosionDef& ExplosionDef)
{
    B3WORLD::ExplodeWorld(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), ExplosionDef);
}
void UBox3DWorldLibrary::ExplodeWorld(UWorld* World, const FB3ExplosionDef& ExplosionDef)
{
    B3_ENSURE_MSG(World, TEXT("ExplodeWorld called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("ExplodeWorld is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_ExplodeWorld(Subsystem->GetWorldHandle(), ExplosionDef);
    }
}









void UBox3DWorldLibrary::BP_SetContactTuning(const UObject* WorldContextObject, float Hertz, float DampingRatio, float ContactSpeed)
{
    B3WORLD::SetContactTuning(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Hertz, DampingRatio, ContactSpeed);
}
void UBox3DWorldLibrary::SetContactTuning(UWorld* World, float Hertz, float DampingRatio, float ContactSpeed)
{
    B3_ENSURE_MSG(World, TEXT("SetContactTuning called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetContactTuning is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetContactTuning(Subsystem->GetWorldHandle(), Hertz, DampingRatio, ContactSpeed);
    }
}





void UBox3DWorldLibrary::BP_SetContactRecycleDistance(const UObject* WorldContextObject, float RecycleDistance)
{
    B3WORLD::SetContactRecycleDistance(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), RecycleDistance);
}
void UBox3DWorldLibrary::SetContactRecycleDistance(UWorld* World, float RecycleDistance)
{
    B3_ENSURE_MSG(World, TEXT("SetContactRecycleDistance called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetContactRecycleDistance is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetContactRecycleDistance(Subsystem->GetWorldHandle(), RecycleDistance);
    }
}




float UBox3DWorldLibrary::BP_GetContactRecycleDistance(const UObject* WorldContextObject)
{
    return B3WORLD::GetContactRecycleDistance(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
float UBox3DWorldLibrary::GetContactRecycleDistance(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, 0.0f, TEXT("GetContactRecycleDistance called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, 0.0f, TEXT("GetContactRecycleDistance is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetContactRecycleDistance(Subsystem->GetWorldHandle());
    }
	return 0.0f;
}





void UBox3DWorldLibrary::BP_SetMaximumLinearSpeed(const UObject* WorldContextObject, float MaximumLinearSpeed)
{
    B3WORLD::SetMaximumLinearSpeed(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), MaximumLinearSpeed);
}
void UBox3DWorldLibrary::SetMaximumLinearSpeed(UWorld* World, float MaximumLinearSpeed)
{
    B3_ENSURE_MSG(World, TEXT("SetMaximumLinearSpeed called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetMaximumLinearSpeed is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetMaximumLinearSpeed(Subsystem->GetWorldHandle(), MaximumLinearSpeed);
    }
}




float UBox3DWorldLibrary::BP_GetMaximumLinearSpeed(const UObject* WorldContextObject)
{
    return B3WORLD::GetMaximumLinearSpeed(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
float UBox3DWorldLibrary::GetMaximumLinearSpeed(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, 0.0f, TEXT("GetMaximumLinearSpeed called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, 0.0f, TEXT("GetMaximumLinearSpeed is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetMaximumLinearSpeed(Subsystem->GetWorldHandle());
    }
	return 0.0f;
}






void UBox3DWorldLibrary::EnableWarmStarting(UWorld* World, bool Flag)
{
    B3_ENSURE_MSG(World, TEXT("EnableWarmStarting called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("EnableWarmStarting is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_EnableWarmStarting(Subsystem->GetWorldHandle(), Flag);
    }
}




bool UBox3DWorldLibrary::BP_IsWarmStartingEnabled(const UObject* WorldContextObject)
{
    return B3WORLD::IsWarmStartingEnabled(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
bool UBox3DWorldLibrary::IsWarmStartingEnabled(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, false, TEXT("IsWarmStartingEnabled called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, false, TEXT("IsWarmStartingEnabled is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_IsWarmStartingEnabled(Subsystem->GetWorldHandle());
    }
	return false;
}




int UBox3DWorldLibrary::BP_GetAwakeBodyCount(const UObject* WorldContextObject)
{
    return B3WORLD::GetAwakeBodyCount(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
int UBox3DWorldLibrary::GetAwakeBodyCount(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, 0, TEXT("GetAwakeBodyCount called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, 0, TEXT("GetAwakeBodyCount is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetAwakeBodyCount(Subsystem->GetWorldHandle());
    }
	return 0;
}




FB3Profile UBox3DWorldLibrary::BP_GetProfile(const UObject* WorldContextObject)
{
    return B3WORLD::GetProfile(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
FB3Profile UBox3DWorldLibrary::GetProfile(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, FB3Profile{}, TEXT("GetProfile called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, FB3Profile{}, TEXT("GetProfile is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetProfile(Subsystem->GetWorldHandle());
    }
	return FB3Profile{};
}




FB3Counters UBox3DWorldLibrary::BP_GetCounters(const UObject* WorldContextObject)
{
    return B3WORLD::GetCounters(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
FB3Counters UBox3DWorldLibrary::GetCounters(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, FB3Counters{}, TEXT("GetCounters called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, FB3Counters{}, TEXT("GetCounters is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetCounters(Subsystem->GetWorldHandle());
    }
    return FB3Counters{};
}




FB3Capacity UBox3DWorldLibrary::BP_GetMaxCapacity(const UObject* WorldContextObject)
{
    return B3WORLD::GetMaxCapacity(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
FB3Capacity UBox3DWorldLibrary::GetMaxCapacity(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, FB3Capacity{}, TEXT("GetMaxCapacity called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, FB3Capacity{}, TEXT("GetMaxCapacity is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetMaxCapacity(Subsystem->GetWorldHandle());
    }
    return FB3Capacity{};
}





void UBox3DWorldLibrary::SetFrictionCallback(UWorld* World, b3FrictionCallback* Callback)
{
    B3_ENSURE_MSG(World, TEXT("SetFrictionCallback called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetFrictionCallback is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetFrictionCallback(Subsystem->GetWorldHandle(), Callback);
    }
}
void UBox3DWorldLibrary::SetRestitutionCallback(UWorld* World, b3RestitutionCallback* Callback)
{
    B3_ENSURE_MSG(World, TEXT("SetRestitutionCallback called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetRestitutionCallback is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetRestitutionCallback(Subsystem->GetWorldHandle(),Callback);
    }   
}




void UBox3DWorldLibrary::BP_SetWorkerCount(const UObject* WorldContextObject, int Count)
{
    B3WORLD::SetWorkerCount(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull), Count);
}
void UBox3DWorldLibrary::SetWorkerCount(UWorld* World, int Count)
{
    B3_ENSURE_MSG(World, TEXT("SetWorkerCount called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("SetWorkerCount is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        WorldInternal::B3Inside_SetWorkerCount(Subsystem->GetWorldHandle(), Count);
    }
}




int UBox3DWorldLibrary::BP_GetWorkerCount(const UObject* WorldContextObject)
{
    return B3WORLD::GetWorkerCount(GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::ReturnNull));
}
int UBox3DWorldLibrary::GetWorkerCount(UWorld* World)
{
    B3_ENSURE_MSG_RET(World, 0, TEXT("GetWorkerCount called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem = UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG_RET(Subsystem, 0, TEXT("GetWorkerCount is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return WorldInternal::B3Inside_GetWorkerCount(Subsystem->GetWorldHandle());
    }
    return 0;
}