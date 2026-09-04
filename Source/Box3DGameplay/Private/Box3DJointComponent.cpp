// Copyright (c) 2026 LiamLeo


#include "Box3DJointComponent.h"
#include "Box3DStaticMeshComponent.h"
#include "Box3DWorld.h"
#include "Box3DCreationBridge.h"
#include "Box3DJoint.h"
#include "Box3DAsserts.h"

UBox3DJointComponent::UBox3DJointComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBox3DJointComponent::BeginPlay()
{
	Super::BeginPlay();
	for(FJointsInDetailPanel Joint: JointsInDetailPanel){
		if(PreaperJointDef(Joint.FirstComponentName,Joint.SecondComponentName,Joint.JointDef))
		{
			FB3JointHandle JointHandle;
			switch(Joint.JointType){
				case EB3JointType::DistanceJoint: JointHandle = B3CREATE::CreateDistanceJoint(GetWorld(), Joint.JointDef, Joint.DistanceJointDef); break;
				case EB3JointType::SphericalJoint: JointHandle = B3CREATE::CreateSphericalJoint(GetWorld(), Joint.JointDef, Joint.SphericalJointDef); break;
				case EB3JointType::MotorJoint: JointHandle = B3CREATE::CreateMotorJoint(GetWorld(), Joint.JointDef, Joint.MotorJointDef); break;
				case EB3JointType::ParallelJoint: JointHandle = B3CREATE::CreateParallelJoint(GetWorld(), Joint.JointDef, Joint.ParallelJointDef); break;
				case EB3JointType::PrismaticJoint: JointHandle = B3CREATE::CreatePrismaticJoint(GetWorld(), Joint.JointDef, Joint.PrismaticJointDef); break;
				case EB3JointType::FilterJoint: JointHandle = B3CREATE::CreateFilterJoint(GetWorld(), Joint.JointDef); break;
				case EB3JointType::RevoluteJoint: JointHandle = B3CREATE::CreateRevoluteJoint(GetWorld(), Joint.JointDef, Joint.RevoluteJointDef); break;
				case EB3JointType::WeldJoint: JointHandle = B3CREATE::CreateWeldJoint(GetWorld(), Joint.JointDef, Joint.WeldJointDef); break;
				case EB3JointType::WheelJoint: JointHandle = B3CREATE::CreateWheelJoint(GetWorld(), Joint.JointDef, Joint.WheelJointDef); break;
			}
			CreatedJoints.Add(JointHandle);
		}
	}
}
void UBox3DJointComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for(FB3JointHandle JointHandle: CreatedJoints)
	{
		if(B3JOINT::IsValid(JointHandle))
		{
			B3JOINT::DestroyJoint(JointHandle, true);
		}
	}
	CreatedJoints.Empty();
	Super::EndPlay(EndPlayReason);
}
void UBox3DJointComponent::GetCreatedJoints(TArray<FB3JointHandle>& OutCreatedJoints)
{
	OutCreatedJoints = CreatedJoints;
}
FB3JointHandle UBox3DJointComponent::AddDistanceJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3DistanceJointDef& DistanceJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateDistanceJoint(GetWorld(), JointDef, DistanceJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
FB3JointHandle UBox3DJointComponent::AddSphericalJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3SphericalJointDef& SphericalJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateSphericalJoint(GetWorld(), JointDef, SphericalJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
FB3JointHandle UBox3DJointComponent::AddMotorJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3MotorJointDef& MotorJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateMotorJoint(GetWorld(), JointDef, MotorJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
FB3JointHandle UBox3DJointComponent::AddParallelJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3ParallelJointDef& ParallelJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateParallelJoint(GetWorld(), JointDef, ParallelJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
FB3JointHandle UBox3DJointComponent::AddPrismaticJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3PrismaticJointDef& PrismaticJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreatePrismaticJoint(GetWorld(), JointDef, PrismaticJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
FB3JointHandle UBox3DJointComponent::AddFilterJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateFilterJoint(GetWorld(), JointDef);
		CreatedJoints.Add(JointHandle);
		return JointHandle;
	}
	return FB3JointHandle{};
}
FB3JointHandle UBox3DJointComponent::AddRevoluteJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3RevoluteJointDef& RevoluteJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateRevoluteJoint(GetWorld(), JointDef, RevoluteJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
FB3JointHandle UBox3DJointComponent::AddWeldJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3WeldJointDef& WeldJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateWeldJoint(GetWorld(), JointDef, WeldJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
FB3JointHandle UBox3DJointComponent::AddWheelJoint(const FString FirstComponentName,const FString& SecondComponentName,FB3JointDef JointDef,const FB3WheelJointDef& WheelJointDef)
{
	FB3JointHandle JointHandle;
	if(PreaperJointDef(FirstComponentName,SecondComponentName,JointDef))
	{
		JointHandle = B3CREATE::CreateWheelJoint(GetWorld(), JointDef, WheelJointDef);
		CreatedJoints.Add(JointHandle);
	}
	return JointHandle;
}
bool UBox3DJointComponent::PreaperJointDef(const FString& FirstComponentName, const FString& SecondComponentName, FB3JointDef& OutJointDef)
{
	UBox3DStaticMeshComponent* FirstComponent = FindComponentByName(FirstComponentName);
	UBox3DStaticMeshComponent* SecondComponent = FindComponentByName(SecondComponentName);
	B3_ENSURE_MSG(FirstComponent, TEXT("FirstComponent is not found"));
	B3_ENSURE_MSG(SecondComponent, TEXT("SecondComponent is not found"));
	if(FirstComponent && SecondComponent)
	{
		OutJointDef.BodyHandleA = FirstComponent->GetRigidBodyHandle();
		OutJointDef.BodyHandleB = SecondComponent->GetRigidBodyHandle();
		return true;
	}
	return false;
}
void UBox3DJointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UBox3DStaticMeshComponent* UBox3DJointComponent::FindComponentByName(FString ComponentName)
{
    TArray<UBox3DStaticMeshComponent*> Components;
    GetOwner()->GetComponents(Components);
    for (UBox3DStaticMeshComponent* Component : Components)
    {
        if (Component && Component->GetName() == ComponentName)
        {
            return Component;
        }
    }

    return nullptr;
}
