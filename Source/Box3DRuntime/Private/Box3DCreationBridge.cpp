// Copyright (c) 2026 LiamLeo


#include "Box3DCreationBridge.h"
#include "Box3DTypes.h"
#include "Box3DWorld.h"
#include "Box3DCreation.h"
#include "Box3DWorldSubsystem.h"
#include "Box3DAsserts.h"
#include "Box3DRuntimeLogging.h"

FB3WorldHandle UBox3DCreationBridge::CreateWorld(const FB3WorldDef& WorldDef)
{
    return CreateInternal::B3Inside_CreateWorld(WorldDef);
}
FB3BodyHandle UBox3DCreationBridge::CreateBody(UWorld* World, const FB3BodyDef& BodyDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateBody called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateBody is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateBody(Subsystem->GetWorldHandle(), BodyDef);
    }
    return FB3BodyHandle();
}
FB3ShapeHandle UBox3DCreationBridge::CreateSphereShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, FB3Sphere Sphere , const FVector3f& ComponentScale, bool MaxScaleAxis)
{
    return CreateInternal::B3Inside_CreateSphereShape(BodyHandle, ShapeDef, Sphere, ComponentScale, MaxScaleAxis);
}
FB3ShapeHandle UBox3DCreationBridge::CreateCapsuleShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, FB3Capsule Capsule)
{
    return CreateInternal::B3Inside_CreateCapsuleShape(BodyHandle,ShapeDef,Capsule);
}
FB3ShapeHandle UBox3DCreationBridge::CreateCapsuleShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, float Length, float Radius)
{
    return CreateInternal::B3Inside_CreateCapsuleShape(BodyHandle,ShapeDef,Transform,Length,Radius);
}
FB3ShapeHandle UBox3DCreationBridge::CreateBoxShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, const FVector3f& ComponentScale )
{
    return CreateInternal::B3Inside_CreateBoxShape(BodyHandle, ShapeDef, Transform, ComponentScale);
}
FB3ShapeHandle UBox3DCreationBridge::CreateHullShape( const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const TArray<FVector>& Points, int MaxVertexCount, const FTransform3f& Transform, const FVector3f& ComponentScale)
{
    return CreateInternal::B3Inside_CreateHullShape(BodyHandle, ShapeDef, Points, MaxVertexCount, Transform, ComponentScale);
}

FB3MeshData UBox3DCreationBridge::CreateMeshData(FB3MeshDef& MeshDef)
{
    return CreateInternal::B3Inside_CreateMeshData(MeshDef);
}
FB3ShapeHandle UBox3DCreationBridge::CreateMeshShape(const FB3BodyHandle& BodyHandle, const FB3ShapeDef& ShapeDef, const FB3MeshData* MeshData, const FVector3f& Scale)
{
    return CreateInternal::B3Inside_CreateMeshShape(BodyHandle, ShapeDef, MeshData, Scale);
}






FB3JointHandle UBox3DCreationBridge::CreateParallelJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3ParallelJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateParallelJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateParallelJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateParallelJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreateDistanceJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3DistanceJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateDistanceJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateDistanceJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateDistanceJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreateMotorJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3MotorJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateMotorJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateMotorJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateMotorJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreateFilterJoint(UWorld* World,const FB3JointDef& BaseDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateFilterJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateFilterJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateFilterJoint(Subsystem->GetWorldHandle(), BaseDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreatePrismaticJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3PrismaticJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreatePrismaticJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreatePrismaticJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreatePrismaticJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreateRevoluteJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3RevoluteJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateRevoluteJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateRevoluteJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateRevoluteJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreateSphericalJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3SphericalJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateSphericalJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateSphericalJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateSphericalJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreateWeldJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3WeldJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateWeldJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateWeldJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateWeldJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
FB3JointHandle UBox3DCreationBridge::CreateWheelJoint(UWorld* World,const FB3JointDef& BaseDef, const FB3WheelJointDef& SpecifiedJointDef)
{
    B3_ENSURE_MSG(World, TEXT("CreateWheelJoint called wih an invalid World Handle"));
    UBox3DWorldSubsystem* Subsystem =UWorld::GetSubsystem<UBox3DWorldSubsystem>(World);
    B3_ENSURE_MSG(Subsystem, TEXT("CreateWheelJoint is called but Box3DWorldSubsystem is null or not supported in this world!"));
    if(Subsystem)
    {
        return CreateInternal::B3Inside_CreateWheelJoint(Subsystem->GetWorldHandle(), BaseDef,SpecifiedJointDef);
    }
    return FB3JointHandle{};
}
