// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Box3DTypes.h"

namespace CreateInternal
{
	BOX3DWRAPPER_API FB3WorldHandle B3Inside_CreateWorld(const FB3WorldDef& WorldDef);
	BOX3DWRAPPER_API FB3BodyHandle  B3Inside_CreateBody(const FB3WorldHandle WorldHandle,const FB3BodyDef& BodyDef);
	BOX3DWRAPPER_API FB3ShapeHandle B3Inside_CreateSphereShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, FB3Sphere Sphere, const FVector3f& ComponentScale = FVector3f(1.0f, 1.0f, 1.0f), bool MaxScaleAxis = false);
	BOX3DWRAPPER_API FB3ShapeHandle B3Inside_CreateCapsuleShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, FB3Capsule Capsule);
	BOX3DWRAPPER_API FB3ShapeHandle B3Inside_CreateCapsuleShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, float Length, float Radius);
	BOX3DWRAPPER_API FB3ShapeHandle B3Inside_CreateBoxShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, const FVector3f& ComponentScale = FVector3f(1.0f, 1.0f, 1.0f) );
	BOX3DWRAPPER_API FB3ShapeHandle B3Inside_CreateHullShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const TArray<FVector>& Points, int MaxVertexCount, const FTransform3f& Transform, const FVector3f& ComponentScale = FVector3f(1.0f, 1.0f, 1.0f));
	BOX3DWRAPPER_API FB3MeshData    B3Inside_CreateMeshData(FB3MeshDef& MeshDef);
	BOX3DWRAPPER_API FB3ShapeHandle B3Inside_CreateMeshShape(const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const FB3MeshData* MeshData, const FVector3f& Scale);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateParallelJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3ParallelJointDef& SpecifiedJointDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateDistanceJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3DistanceJointDef& SpecifiedJointDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateMotorJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3MotorJointDef& SpecifiedJointDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateFilterJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreatePrismaticJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3PrismaticJointDef& SpecifiedJointDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateRevoluteJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3RevoluteJointDef& SpecifiedJointDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateSphericalJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3SphericalJointDef& SpecifiedJointDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateWeldJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3WeldJointDef& SpecifiedJointDef);
	BOX3DWRAPPER_API FB3JointHandle B3Inside_CreateWheelJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3WheelJointDef& SpecifiedJointDef);
}