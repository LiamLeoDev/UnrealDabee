// Copyright (c) 2026 LiamLeo

#include "Box3DCreation.h"
#include "Box3DTypes.h"
#include "Box3DCallbacks.h"
#include "box3d/box3d.h"
#include "Box3DAsserts.h"
namespace CreateInternal
{
    FB3WorldHandle B3Inside_CreateWorld(const FB3WorldDef& WorldDef)
    {
        b3WorldDef NativeWorldDef = ToNative(WorldDef);
        NativeWorldDef.enqueueTask = &B3Callbacks::Box3DEnqueueTaskCallback;
        NativeWorldDef.finishTask = &B3Callbacks::Box3DFinishTaskCallback;
        return FB3WorldHandle(b3CreateWorld(&NativeWorldDef));
    }
    FB3BodyHandle B3Inside_CreateBody(const FB3WorldHandle WorldHandle,const FB3BodyDef& BodyDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3BodyHandle{}, TEXT("B3Inside_CreateBody called wih an invalid World Handle"))
        b3BodyDef NativeBodyDef = ToNative(BodyDef);
        NativeBodyDef.name = BodyDef.Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*BodyDef.Name.ToString());
        return FB3BodyHandle(b3CreateBody(WorldHandle.GetID(), &NativeBodyDef));
    }
    FB3ShapeHandle B3Inside_CreateSphereShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, FB3Sphere Sphere , const FVector3f& ComponentScale, bool MaxScaleAxis)
    {
        B3_ENSURE_MSG_RET(BodyHandle, FB3ShapeHandle{}, TEXT("B3Inside_CreateSphereShape called wih an invalid Body Handle"));
        Sphere.Center *= ComponentScale;
        Sphere.Radius *= MaxScaleAxis?ComponentScale.GetAbsMax():ComponentScale.GetAbsMin();
        b3Sphere SphereNative = ToNative(Sphere);
        b3ShapeDef NativeShapeDef = ToNative(ShapeDef);
        NativeShapeDef.density /= (100.0f*100.0f*100.0f);
        NativeShapeDef.name = ShapeDef.Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*ShapeDef.Name.ToString());
        return  FB3ShapeHandle(b3CreateSphereShape(BodyHandle.GetID(),&NativeShapeDef,&SphereNative ));
    }
    FB3ShapeHandle B3Inside_CreateCapsuleShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, FB3Capsule Capsule)
    {
        B3_ENSURE_MSG_RET(BodyHandle, FB3ShapeHandle{}, TEXT("B3Inside_CreateCapsuleShape called wih an invalid Body Handle"));
        b3Capsule CapsuleNative = ToNative(Capsule);
        b3ShapeDef NativeShapeDef = ToNative(ShapeDef);
        NativeShapeDef.density /= (100.0f*100.0f*100.0f);
        NativeShapeDef.name = ShapeDef.Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*ShapeDef.Name.ToString());
        return FB3ShapeHandle(b3CreateCapsuleShape(BodyHandle.GetID(), &NativeShapeDef, &CapsuleNative));
    }
    FB3ShapeHandle B3Inside_CreateCapsuleShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, float Length, float Radius)
    {
        B3_ENSURE_MSG_RET(BodyHandle, FB3ShapeHandle{}, TEXT("B3Inside_CreateCapsuleShape called wih an invalid Body Handle"));
        FB3Capsule Capsule;
        Capsule.Center1 = Transform.GetLocation() + Transform.GetRotation().RotateVector(Capsule.Center1*Length*0.5f);
        Capsule.Center2 = Transform.GetLocation() + Transform.GetRotation().RotateVector(Capsule.Center2*Length*0.5f);
        Capsule.Radius = Radius;
        b3Capsule CapsuleNative = ToNative(Capsule);
        b3ShapeDef NativeShapeDef = ToNative(ShapeDef);
        NativeShapeDef.density /= (100.0f*100.0f*100.0f);
        NativeShapeDef.name = ShapeDef.Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*ShapeDef.Name.ToString());
        return FB3ShapeHandle(b3CreateCapsuleShape(BodyHandle.GetID(), &NativeShapeDef, &CapsuleNative));
    }
    FB3ShapeHandle B3Inside_CreateBoxShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const FTransform3f& Transform, const FVector3f& ComponentScale )
    {
        B3_ENSURE_MSG_RET(BodyHandle, FB3ShapeHandle{}, TEXT("B3Inside_CreateBoxShape called wih an invalid Body Handle"));
        FTransform3f Final = FTransform3f( Transform.GetRotation(), Transform.GetLocation() * ComponentScale, Transform.GetScale3D() * ComponentScale);
        b3BoxHull Hull = b3MakeTransformedBoxHull(Final.GetScale3D().X,Final.GetScale3D().Y,Final.GetScale3D().Z,ToNativeTransform(Final));
        b3ShapeDef NativeShapeDef = ToNative(ShapeDef);
        NativeShapeDef.density /= (100.0f*100.0f*100.0f);
        NativeShapeDef.name = ShapeDef.Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*ShapeDef.Name.ToString());
        return FB3ShapeHandle(b3CreateHullShape( BodyHandle.GetID(), &NativeShapeDef, &Hull.base));
    }
    FB3ShapeHandle B3Inside_CreateHullShape( const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const TArray<FVector>& Points, int MaxVertexCount, const FTransform3f& Transform, const FVector3f& ComponentScale)
    {
        B3_ENSURE_MSG_RET(BodyHandle, FB3ShapeHandle{}, TEXT("B3Inside_CreateHullShape called wih an invalid Body Handle"));
        TArray<b3Vec3> PointsNative;
        PointsNative.Reserve(Points.Num());
        for (const FVector& Point : Points)
        {
            PointsNative.Add(ToNativeVec(FVector3f(Point)));
        }
        b3ShapeId ShapeID = b3_nullShapeId;
        if(b3HullData* Hull = b3CreateHull(PointsNative.GetData(),PointsNative.Num(),MaxVertexCount))
        {
            FTransform3f Final = FTransform3f( Transform.GetRotation(), Transform.GetLocation() * ComponentScale, Transform.GetScale3D() * ComponentScale);
            b3ShapeDef NativeShapeDef = ToNative(ShapeDef);
            NativeShapeDef.density /= (100.0f*100.0f*100.0f);
            NativeShapeDef.name = ShapeDef.Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*ShapeDef.Name.ToString());
            ShapeID = b3CreateTransformedHullShape(BodyHandle.GetID(), &NativeShapeDef, Hull, ToNativeTransform(Final) ,ToNativeVec(Final.GetScale3D()));
            b3DestroyHull(Hull);
        }
        return FB3ShapeHandle(ShapeID);
    }
	FB3MeshData B3Inside_CreateMeshData(FB3MeshDef& MeshDef)
    {
        B3_ENSURE_ALWAYS_MSG_RET(MeshDef.VertexCount > 2, FB3MeshData{}, TEXT("B3Inside_CreateMeshData the passed in MeshDef have less then three vertices"));
        B3_ENSURE_ALWAYS_MSG_RET(MeshDef.TriangleCount > 0, FB3MeshData{}, TEXT("B3Inside_CreateMeshData the passed in MeshDef have less then three TriangleVertexIndices"));
        b3MeshDef MeshDefNative = ToNative(MeshDef);
        return FB3MeshData(b3CreateMesh(&MeshDefNative, nullptr, 0));
    }
    FB3ShapeHandle B3Inside_CreateMeshShape(const FB3BodyHandle BodyHandle, const FB3ShapeDef& ShapeDef, const FB3MeshData* MeshData, const FVector3f& Scale)
    {
        B3_ENSURE_MSG_RET(BodyHandle, FB3ShapeHandle{}, TEXT("B3Inside_CreateMeshShape called wih an invalid Body Handle"));
        B3_ENSURE_MSG_RET(MeshData, FB3ShapeHandle{}, TEXT("B3Inside_CreateMeshShape called wih an invalid Mesh Data")); 
        B3_ENSURE_MSG_RET(MeshData->GetData(), FB3ShapeHandle{}, TEXT("B3Inside_CreateMeshShape The data inside MeshData is invalid")); 
        b3ShapeDef  NativeShapeDef = ToNative(ShapeDef);
        NativeShapeDef.density/=(100.0f*100.0f*100.0f);
        NativeShapeDef.name = ShapeDef.Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*ShapeDef.Name.ToString());
        return FB3ShapeHandle(b3CreateMeshShape(BodyHandle.GetID(), &NativeShapeDef, MeshData->GetData(), ToNativeVec(Scale)));
    }





    FB3JointHandle B3Inside_CreateParallelJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3ParallelJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateParallelJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateParallelJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateParallelJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3ParallelJointDef ParallelJointDefNative = ToNative(SpecifiedJointDef);
        ParallelJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreateParallelJoint(WorldHandle.GetID(), &ParallelJointDefNative));
    }
	FB3JointHandle B3Inside_CreateDistanceJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3DistanceJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateDistanceJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateDistanceJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateDistanceJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3DistanceJointDef DistanceJointDefNative = ToNative(SpecifiedJointDef);
        DistanceJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreateDistanceJoint(WorldHandle.GetID(), &DistanceJointDefNative));
    }
	FB3JointHandle B3Inside_CreateMotorJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3MotorJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateMotorJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateMotorJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateMotorJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3MotorJointDef MotorJointDefNative = ToNative(SpecifiedJointDef);
        MotorJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreateMotorJoint(WorldHandle.GetID(), &MotorJointDefNative));
    }
	FB3JointHandle B3Inside_CreateFilterJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateFilterJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateFilterJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateFilterJoint BaseDef BodyHandle B Is not valid"));
        b3FilterJointDef FilterJointDefNative = {ToNative(BaseDef)};
        return FB3JointHandle(b3CreateFilterJoint(WorldHandle.GetID(), &FilterJointDefNative));
    }
	FB3JointHandle B3Inside_CreatePrismaticJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3PrismaticJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreatePrismaticJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreatePrismaticJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreatePrismaticJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3PrismaticJointDef PrismaticJointDefNative = ToNative(SpecifiedJointDef);
        PrismaticJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreatePrismaticJoint(WorldHandle.GetID(), &PrismaticJointDefNative));
    }
	FB3JointHandle B3Inside_CreateRevoluteJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3RevoluteJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateRevoluteJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateRevoluteJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateRevoluteJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3RevoluteJointDef RevoluteJointDefNative = ToNative(SpecifiedJointDef);
        RevoluteJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreateRevoluteJoint(WorldHandle.GetID(), &RevoluteJointDefNative));
    }
	FB3JointHandle B3Inside_CreateSphericalJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3SphericalJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateSphericalJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateSphericalJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateSphericalJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3SphericalJointDef SphericalJointDefNative = ToNative(SpecifiedJointDef);
        SphericalJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreateSphericalJoint(WorldHandle.GetID(), &SphericalJointDefNative));
    }
	FB3JointHandle B3Inside_CreateWeldJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3WeldJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateWeldJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateWeldJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateWeldJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3WeldJointDef WeldJointDefNative = ToNative(SpecifiedJointDef);
        WeldJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreateWeldJoint(WorldHandle.GetID(), &WeldJointDefNative));
    }
	FB3JointHandle B3Inside_CreateWheelJoint(const FB3WorldHandle WorldHandle,const FB3JointDef& BaseDef, const FB3WheelJointDef& SpecifiedJointDef)
    {
        B3_ENSURE_MSG_RET(WorldHandle, FB3JointHandle{}, TEXT("B3Inside_CreateWheelJoint called wih an invalid World Handle"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleA, FB3JointHandle{}, TEXT("B3Inside_CreateWheelJoint BaseDef BodyHandle A Is not valid"));
        B3_ENSURE_MSG_RET(BaseDef.BodyHandleB, FB3JointHandle{}, TEXT("B3Inside_CreateWheelJoint BaseDef BodyHandle B Is not valid"));
        b3JointDef JointDefNative = ToNative(BaseDef);
        b3WheelJointDef WheelJointDefNative = ToNative(SpecifiedJointDef);
        WheelJointDefNative.base = JointDefNative;
        return FB3JointHandle(b3CreateWheelJoint(WorldHandle.GetID(), &WheelJointDefNative));
    }
}
