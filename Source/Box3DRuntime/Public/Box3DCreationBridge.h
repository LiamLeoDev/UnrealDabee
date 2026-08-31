// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Box3DTypes.h"
#include "Engine/World.h"
#include "Box3DCreationBridge.generated.h"



UCLASS()
class BOX3DRUNTIME_API UBox3DCreationBridge : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

    static FB3WorldHandle CreateWorld(const FB3WorldDef& WorldDef);
	static FB3BodyHandle  CreateBody(UWorld* World, const FB3BodyDef& BodyDef);
	static FB3ShapeHandle CreateSphereShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, FB3Sphere Sphere, const FVector3f& ComponentScale = FVector3f(1.0f, 1.0f, 1.0f), bool MaxScaleAxis = false);
	static FB3ShapeHandle CreateCapsuleShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, FB3Capsule Capsule);
	static FB3ShapeHandle CreateCapsuleShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, float Length, float Radius);
	static FB3ShapeHandle CreateBoxShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, const FVector3f& ComponentScale = FVector3f(1.0f, 1.0f, 1.0f) );
	static FB3ShapeHandle CreateHullShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const TArray<FVector>& Points, int MaxVertexCount, const FTransform3f& Transform, const FVector3f& ComponentScale = FVector3f(1.0f, 1.0f, 1.0f));
	static FB3MeshData    CreateMeshData(FB3MeshDef& MeshDef);
    static FB3ShapeHandle CreateMeshShape(const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const FB3MeshData* MeshData, const FVector3f& Scale);
	static FB3JointHandle CreateParallelJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3ParallelJointDef& SpecifiedJointDef);
	static FB3JointHandle CreateDistanceJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3DistanceJointDef& SpecifiedJointDef);
	static FB3JointHandle CreateMotorJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3MotorJointDef& SpecifiedJointDef);
	static FB3JointHandle CreateFilterJoint(UWorld* World,const FB3JointDef& BaseDef);
	static FB3JointHandle CreatePrismaticJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3PrismaticJointDef& SpecifiedJointDef);
	static FB3JointHandle CreateRevoluteJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3RevoluteJointDef& SpecifiedJointDef);
	static FB3JointHandle CreateSphericalJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3SphericalJointDef& SpecifiedJointDef);
	static FB3JointHandle CreateWeldJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3WeldJointDef& SpecifiedJointDef);
	static FB3JointHandle CreateWheelJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3WheelJointDef& SpecifiedJointDef);
};

#define B3CREATE UBox3DCreationBridge