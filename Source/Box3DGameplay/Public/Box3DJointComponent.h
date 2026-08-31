// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Box3DStaticMeshComponent.h"
#include "Box3DTypes.h"
#include "Box3DJointComponent.generated.h"

USTRUCT()
struct BOX3DGAMEPLAY_API FJointsInDetailPanel
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint")
	EB3JointType JointType = EB3JointType::None;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint",meta = (DisplayName = "Body A",EditCondition = "JointType != EB3JointType::None", EditConditionHides))
	FString FirstComponentName;
    UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint",meta = (DisplayName = "Body B",EditCondition = "JointType != EB3JointType::None", EditConditionHides))
	FString SecondComponentName;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint",meta=(DisplayName = "Base Settings",EditCondition = "JointType != EB3JointType::None", EditConditionHides))
	FB3JointDef JointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Distance Joint Settings",EditCondition = "JointType == EB3JointType::DistanceJoint", EditConditionHides))
	FB3DistanceJointDef DistanceJointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Motor Joint Settings",EditCondition = "JointType == EB3JointType::MotorJoint", EditConditionHides))
	FB3MotorJointDef MotorJointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Parallel Joint Settings",EditCondition = "JointType == EB3JointType::ParallelJoint", EditConditionHides))
	FB3ParallelJointDef ParallelJointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Prismatic Joint Settings",EditCondition = "JointType == EB3JointType::PrismaticJoint", EditConditionHides))
	FB3PrismaticJointDef PrismaticJointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Revolute Joint Settings",EditCondition = "JointType == EB3JointType::RevoluteJoint", EditConditionHides))
	FB3RevoluteJointDef RevoluteJointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Spherical Joint Settings",EditCondition = "JointType == EB3JointType::SphericalJoint", EditConditionHides))
	FB3SphericalJointDef SphericalJointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Weld Joint Settings",EditCondition = "JointType == EB3JointType::WeldJoint", EditConditionHides))
	FB3WeldJointDef WeldJointDef;
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿|Joint", meta=(DisplayName = "Wheel Joint Settings",EditCondition = "JointType == EB3JointType::WheelJoint", EditConditionHides))
	FB3WheelJointDef WheelJointDef;
};

UCLASS( ClassGroup=(Box3D),  meta=(BlueprintSpawnableComponent, DisplayName = "Box3D Joint Component"))
class BOX3DGAMEPLAY_API UBox3DJointComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBox3DJointComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "Created joints")void GetCreatedJoints(TArray<FB3JointHandle>& OutCreatedJoints);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddDistanceJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3DistanceJointDef& DistanceJointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddSphericalJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3SphericalJointDef& SphericalJointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddMotorJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3MotorJointDef& MotorJointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddParallelJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3ParallelJointDef& ParallelJointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddPrismaticJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3PrismaticJointDef& PrismaticJointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddFilterJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddRevoluteJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3RevoluteJointDef& RevoluteJointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddWeldJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3WeldJointDef& WeldJointDef);
	UFUNCTION(BlueprintCallable, Category="Box3D|JointComponent")
	UPARAM(DisplayName = "JointHandle")FB3JointHandle AddWheelJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3WheelJointDef& WheelJointDef);

private:
	UPROPERTY(EditDefaultsOnly, Category="𝘽𝙊𝙓3𝘿", meta=(DisplayName = "Joints", TitleProperty = "{JointType}",ShowOnlyInnerProperties))
	TArray<FJointsInDetailPanel> JointsInDetailPanel;
	UBox3DStaticMeshComponent* FindComponentByName(FString ComponentName);
	bool PreaperJointDef(const FString& FirstComponentName, const FString& SecondComponentName, FB3JointDef& OutJointDef);
	TArray<FB3JointHandle> CreatedJoints;
};
