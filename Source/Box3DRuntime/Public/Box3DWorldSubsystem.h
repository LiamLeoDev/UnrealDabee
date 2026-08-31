// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Engine/EngineBaseTypes.h"
#include "Box3DTypes.h"
#include "Box3DSettings.h"
#include "Box3DWorldSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBodiesUpdated);

struct FBox3DPhysicsTickFunction : public FTickFunction
{
    UBox3DWorldSubsystem* Owner = nullptr;
    virtual void ExecuteTick( float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;
    virtual FString DiagnosticMessage() override;
    virtual FName DiagnosticContext(bool bDetailed) override;
};

UCLASS()
class BOX3DRUNTIME_API UBox3DWorldSubsystem final: public UWorldSubsystem
{
	GENERATED_BODY()

public:
    UBox3DWorldSubsystem();
    virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    FOnBodiesUpdated OnBodiesUpdated;
    FB3WorldHandle& GetWorldHandle();
    static bool EnableProfile;
    static bool EnableCounters;
private:
    friend struct FBox3DPhysicsTickFunction;
    FB3WorldHandle WorldHandle;
    FB3RecordingHandle RecordingHandle;
    TArray<FB3BodyMoveEvent> BodyMoveEvents;
    TArray<FB3SensorTouchEvent> BeginSensorEvents;
    TArray<FB3SensorTouchEvent> EndSensorEvents;
    FBox3DPhysicsTickFunction PhysicsTickFunction;
    const UBox3DSettings* Box3DSettings;
    float DeltaTimeAccumulator;
    float SmoothDeltaTime;
    void UpdateBodies(const TArray<FB3BodyMoveEvent>& BodyMoveEvents);
    void UpdateBeginSensors(const TArray<FB3SensorTouchEvent>& SensorTouchEvents);
    void UpdateEndSensors(const TArray<FB3SensorTouchEvent>& SensorTouchEvents);
    void PhysicsTick(float DeltaTime);
};
