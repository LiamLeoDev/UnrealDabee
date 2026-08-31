// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Box3DTypes.h"
#include "Box3DSettings.generated.h"




UCLASS(Config=Game, DefaultConfig)
class BOX3DRUNTIME_API UBox3DSettings : public UDeveloperSettings
{
	GENERATED_BODY()	
	virtual FName GetCategoryName() const override
	{
		return "Game";
	}

#if WITH_EDITOR

	virtual FText GetSectionText() const override
	{
		return FText::FromString("BOX3D");
	}

#endif
public:
	UPROPERTY(Config, EditAnywhere, Category="Physics")
    FB3WorldDef WorldProperties;

	
	UPROPERTY(Config, EditAnywhere, Category="Physics|Recording")
	bool bRecordPhysics = false;
	UPROPERTY(Config, EditAnywhere, Category="Physics|Recording", meta=(EditCondition="bRecordPhysics", EditConditionHides))
	FString RecordingFilename = TEXT("PhysicsWorld.b3rec");
	UPROPERTY(Config, EditAnywhere, Category="Physics|Recording", meta=(ForceUnits="Bytes", EditCondition="bRecordPhysics", EditConditionHides))
	uint32 ByteCapacity = 1000;

	UPROPERTY(Config, EditAnywhere, Category="Physics|Tick")
	float FixedTimeStep = 0.016666f;
	UPROPERTY(Config, EditAnywhere, Category="Physics|Tick")
	uint8 SubStepCount = 4;
	UPROPERTY(Config, EditAnywhere, Category="Physics|Tick")
	uint8 MaxExtraStepsForBelowTimeStep = 2;
	UPROPERTY(Config, EditAnywhere, Category="Physics|Tick")
	float DeltaTimeSmoothness = 0.8f;
};	
