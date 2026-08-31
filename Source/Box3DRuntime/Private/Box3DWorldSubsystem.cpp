// Copyright (c) 2026 LiamLeo

#include "Box3DWorldSubsystem.h"
#include "Box3DTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Box3DWorldLibrary.h"
#include "Box3DCreationBridge.h"
#include "Box3DConstant.h"
#include "Box3DRecord.h"
#include "Box3DShape.h"
#include "Box3DRuntimeLogging.h"
#include "Engine/World.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

bool UBox3DWorldSubsystem::EnableProfile = false;
bool UBox3DWorldSubsystem::EnableCounters = false;
UBox3DWorldSubsystem::UBox3DWorldSubsystem()
{
    Box3DSettings = GetDefault<UBox3DSettings>();
    SmoothDeltaTime = Box3DSettings->FixedTimeStep;
    DeltaTimeAccumulator = 0;
}
bool UBox3DWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
    return WorldType == EWorldType::Game
        || WorldType == EWorldType::PIE
        || WorldType == EWorldType::Editor
        || WorldType == EWorldType::EditorPreview
        || WorldType == EWorldType::GamePreview
        || WorldType == EWorldType::Inactive;
}
void UBox3DWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(Box3DRuntimeLog, Log, TEXT("____________________________________"));
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Started WorldSubsystem initilization"));
    
    if(GetWorld()->IsGameWorld())
    {
        PhysicsTickFunction.Owner = this;
        PhysicsTickFunction.TickGroup = TG_StartPhysics;
        PhysicsTickFunction.bCanEverTick = true;
        PhysicsTickFunction.bRunOnAnyThread = false;
        PhysicsTickFunction.bHighPriority = true;
        PhysicsTickFunction.RegisterTickFunction(GetWorld()->PersistentLevel);
    }


    B3CONST::SetLengthUnitsPerMeter(100.0f);
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Worlds before new world is created: %u"),B3WORLD::GetWorldCount());
    WorldHandle = B3CREATE::CreateWorld(Box3DSettings->WorldProperties);
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Total worlds after world creation: %u"),B3WORLD::GetWorldCount());
    B3WORLD::SetFrictionCallback(GetWorld());
    B3WORLD::SetRestitutionCallback(GetWorld());
    if(Box3DSettings->bRecordPhysics && GetWorld()->IsGameWorld())
    {
        UE_LOG(Box3DRuntimeLog, Verbose, TEXT("Initializing recording with : %i ByteCapacity"),Box3DSettings->ByteCapacity);
        RecordingHandle = B3RECORD::CreateRecording(Box3DSettings->ByteCapacity);
        B3RECORD::StartRecording(WorldHandle,RecordingHandle);
    }
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Ended WorldSubsystem initilization:  Subsystem: %p  World: %p  WorldType: %s"), this, GetWorld(), LexToString(GetWorld()->WorldType));
    UE_LOG(Box3DRuntimeLog, Log, TEXT("____________________________________"));
}

void UBox3DWorldSubsystem::Deinitialize()
{   
    UE_LOG(Box3DRuntimeLog, Log, TEXT("____________________________________"));
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Started WorldSubsystem Deinitialization"));
    PhysicsTickFunction.UnRegisterTickFunction();
    if(Box3DSettings->bRecordPhysics && RecordingHandle)
    {
        B3RECORD::StopRecording(WorldHandle);
        FString UnrealPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Box3D"), Box3DSettings->RecordingFilename);
        IFileManager::Get().MakeDirectory(*FPaths::GetPath(UnrealPath), true);
        bool Saved = B3RECORD::SaveRecordingToFile(RecordingHandle,UnrealPath);
        UE_LOG(Box3DRuntimeLog, Warning, TEXT("%s"), Saved ? *(TEXT("Box3D: Physics World Recording Saved to: ") + UnrealPath) : TEXT("Box3D: Recording Not Saved"));
        B3RECORD::DestroyRecording(RecordingHandle);
    }
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Worlds before world is destroyed: %u"),B3WORLD::GetWorldCount());
    B3WORLD::DestroyWorld(GetWorld());
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Total worlds after world is destoryed: %u"),B3WORLD::GetWorldCount());
    UE_LOG(Box3DRuntimeLog, Log, TEXT("Ended WorldSubsystem Deinitialization:  Subsystem: %p  World: %p  WorldType: %s"), this, GetWorld(), LexToString(GetWorld()->WorldType));
    UE_LOG(Box3DRuntimeLog, Log, TEXT("____________________________________"));
    Super::Deinitialize();
}


void FBox3DPhysicsTickFunction::ExecuteTick( float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
    if (Owner)
    {
        Owner->PhysicsTick(DeltaTime);
    }
}
FString FBox3DPhysicsTickFunction::DiagnosticMessage()
{
    return TEXT("Box3D Tick DiagnosticMessage");
}
FName FBox3DPhysicsTickFunction::DiagnosticContext(bool bDetailed)
{
    return FName(TEXT("Box3DTick"));
}

void UBox3DWorldSubsystem::PhysicsTick(float DeltaTime)
{
    SmoothDeltaTime = FMath::Lerp(DeltaTime, SmoothDeltaTime, Box3DSettings->DeltaTimeSmoothness);
    DeltaTimeAccumulator += SmoothDeltaTime;
    int StepCount = 0;
    while (DeltaTimeAccumulator >= Box3DSettings->FixedTimeStep)
    {
        ++StepCount;
        B3WORLD::WorldStep(GetWorld(), Box3DSettings->FixedTimeStep, Box3DSettings->SubStepCount);
        DeltaTimeAccumulator -= Box3DSettings->FixedTimeStep;
        if(StepCount == Box3DSettings->MaxExtraStepsForBelowTimeStep)
        {
            DeltaTimeAccumulator = 0.0f;
        }
        if(DeltaTimeAccumulator < Box3DSettings->FixedTimeStep)
        {
            B3WORLD::GetBodyEvents(GetWorld(),BodyMoveEvents);
            UpdateBodies(BodyMoveEvents);
            OnBodiesUpdated.Broadcast();
        }
        B3WORLD::GetSensorEvents(GetWorld(),BeginSensorEvents,EndSensorEvents);
        UpdateBeginSensors(BeginSensorEvents);
        UpdateEndSensors(EndSensorEvents);
    }

#if WITH_EDITOR
    FB3Counters Counters = B3WORLD::GetCounters(GetWorld());
    FB3Profile Profile = B3WORLD::GetProfile(GetWorld());
    if (GEngine)
	{
        if(EnableCounters)
        { 
            FString CounterStr = FString::Printf(TEXT(
                    "BodyCount:            %d\n"
                    "ShapeCount:           %d\n"
                    "ContactCount:         %d\n"
                    "JointCount:           %d\n"
                    "IslandCount:          %d\n"
                    "StackUsed:            %d\n"
                    "ArenaCapacity:        %d\n"
                    "StaticTreeHeight:     %d\n"
                    "TreeHeight:           %d\n"
                    "SatCallCount:         %d\n"
                    "SatCacheHitCount:     %d\n"
                    "ByteCount:            %d\n"
                    "TaskCount:            %d\n"
                    "AwakeContactCount:    %d\n"
                    "RecycledContactCount: %d\n"
                    "DistanceIterations:   %d\n"
                    "PushBackIterations:   %d\n"
                    "RootIterations:       %d"
                ), 
                    Counters.BodyCount,
                    Counters.ShapeCount,
                    Counters.ContactCount,
                    Counters.JointCount,
                    Counters.IslandCount,
                    Counters.StackUsed,
                    Counters.ArenaCapacity,
                    Counters.StaticTreeHeight,
                    Counters.TreeHeight,
                    Counters.SatCallCount,
                    Counters.SatCacheHitCount,
                    Counters.ByteCount,
                    Counters.TaskCount,
                    Counters.AwakeContactCount,
                    Counters.RecycledContactCount,
                    Counters.DistanceIterations,
                    Counters.PushBackIterations,
                    Counters.RootIterations);
            GEngine->AddOnScreenDebugMessage(-101, 0.0f, FColor(0,220,130,255), CounterStr);
            GEngine->AddOnScreenDebugMessage(-102, 0.0f, FColor::Black, FString::Printf(TEXT("COUNTERS______________________")));
        }
        if(EnableProfile)
		{
                FString ProfileStr = FString::Printf(TEXT(
                    "Step:                  %f\n" 
                    "__Pairs:                 %f\n"  
                    "__Collide:               %f\n"    
                    "__Solve:                 %f\n"  
                    "__SolverSetup:           %f\n"        
                    "__Constraints:           %f\n"        
                    "__PrepareConstraints:    %f\n"               
                    "__IntegrateVelocities:   %f\n"                
                    "__WarmStart:             %f\n"      
                    "__SolveImpulses:         %f\n"          
                    "__IntegratePositions:    %f\n"               
                    "__RelaxImpulses:         %f\n"          
                    "__ApplyRestitution:      %f\n"             
                    "__StoreImpulses:         %f\n"          
                    "__SplitIslands:          %f\n"         
                    "__Transforms:            %f\n"       
                    "__SensorHits:            %f\n"       
                    "__JointEvents:           %f\n"        
                    "__HitEvents:             %f\n"      
                    "__Refit:                 %f\n"  
                    "__Bullets:               %f\n"    
                    "__SleepIslands:          %f\n"         
                    "__Sensors:               %f"
                ),
                    Profile.Step,
                    Profile.Pairs,
                    Profile.Collide,
                    Profile.Solve,
                    Profile.SolverSetup,
                    Profile.Constraints,
                    Profile.PrepareConstraints,
                    Profile.IntegrateVelocities,
                    Profile.WarmStart,
                    Profile.SolveImpulses,
                    Profile.IntegratePositions,
                    Profile.RelaxImpulses,
                    Profile.ApplyRestitution,
                    Profile.StoreImpulses,
                    Profile.SplitIslands,
                    Profile.Transforms,
                    Profile.SensorHits,
                    Profile.JointEvents,
                    Profile.HitEvents,
                    Profile.Refit,
                    Profile.Bullets,
                    Profile.SleepIslands,
                    Profile.Sensors);
            GEngine->AddOnScreenDebugMessage(-103, 0.0f, FColor(0,220,130,255), ProfileStr);
            GEngine->AddOnScreenDebugMessage(-104, 0.0f, FColor::Black, FString::Printf(TEXT("PROFILES______________________")));
        }
	}
#endif
}

void UBox3DWorldSubsystem::UpdateBodies(const TArray<FB3BodyMoveEvent>& BodyMoveEventsGot)
{
    for (const FB3BodyMoveEvent& Event : BodyMoveEventsGot)
    {
        if(Event.UserData && Event.UserData->MoveCallback)
        {
            if(UObject* Object = Event.UserData->Object.Get())
            {
                Event.UserData->MoveCallback(Event.UserData, Object, Event.Transform);
            }
        }
    }
}
void UBox3DWorldSubsystem::UpdateBeginSensors(const TArray<FB3SensorTouchEvent>& SensorTouchEvents)
{
    for (const FB3SensorTouchEvent& Event: SensorTouchEvents)
    {
        FB3ShapeUserData* SensorShapeUserData = B3SHAPE::GetUserData(Event.SensorShapeHandle);
        FB3ShapeUserData* VisitorShapeUserData = B3SHAPE::GetUserData(Event.VisitorShapeHandle);
        if(SensorShapeUserData  && SensorShapeUserData->BeginOverlapCallback)
        {
            if(UObject* Object = SensorShapeUserData->Object.Get())
            {
                SensorShapeUserData->BeginOverlapCallback(SensorShapeUserData, Object, Event);
            }
        }
        if(VisitorShapeUserData  && VisitorShapeUserData->BeginOverlapCallback)
        {
            if (UObject* Object = VisitorShapeUserData->Object.Get())
            {
                VisitorShapeUserData->BeginOverlapCallback(VisitorShapeUserData, Object, Event);
            }
        }
    }
}
void UBox3DWorldSubsystem::UpdateEndSensors(const TArray<FB3SensorTouchEvent>& SensorTouchEvents)
{
    for (const FB3SensorTouchEvent& Event: SensorTouchEvents)
    {
        FB3ShapeUserData* SensorShapeUserData = B3SHAPE::GetUserData(Event.SensorShapeHandle);
        FB3ShapeUserData* VisitorShapeUserData = B3SHAPE::GetUserData(Event.VisitorShapeHandle);
        if(SensorShapeUserData  && SensorShapeUserData->EndOverlapCallback)
        {
            if(UObject* Object = SensorShapeUserData->Object.Get())
            {
                SensorShapeUserData->EndOverlapCallback(SensorShapeUserData, Object, Event);
            }
        }
        if(VisitorShapeUserData  && VisitorShapeUserData->EndOverlapCallback)
        {
            if (UObject* Object = VisitorShapeUserData->Object.Get())
            {
                VisitorShapeUserData->EndOverlapCallback(VisitorShapeUserData, Object, Event);
            }
        }
    }
}

FB3WorldHandle& UBox3DWorldSubsystem::GetWorldHandle()
{
    return WorldHandle;
}
