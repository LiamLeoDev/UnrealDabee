#pragma once
#include "Box3DTypes.h"
#include "box3d/box3d.h"
#include "Tasks/Task.h"

namespace B3Callbacks
{
    void* Box3DEnqueueTaskCallback(b3TaskCallback* Task, void* TaskContext, void* UserContext, const char* TaskName);
    void Box3DFinishTaskCallback(void* UserTask, void* UserContext);
    float CastResultFcnSingleCallback( b3ShapeId shapeId, b3Pos point, b3Vec3 normal, float fraction, uint64_t userMaterialId, int triangleIndex, int childIndex, void* context );
    float CastResultFcnMultipleCallback( b3ShapeId shapeId, b3Pos point, b3Vec3 normal, float fraction, uint64_t userMaterialId, int triangleIndex, int childIndex, void* context );
    float FrictionCallback( float frictionA, uint64_t userMaterialIdA, float frictionB, uint64_t userMaterialIdB );
    float RestitutionCallback( float restitutionA, uint64_t userMaterialIdA, float restitutionB, uint64_t userMaterialIdB );
}