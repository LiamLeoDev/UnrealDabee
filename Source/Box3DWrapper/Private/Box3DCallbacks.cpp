// Copyright (c) 2026 LiamLeo


#include "Box3DCallbacks.h"
#include "Box3DTypes.h"
#include "box3d/box3d.h"
#include "Tasks/Task.h"
#include "Containers/AnsiString.h"

namespace B3Callbacks
{
    void* Box3DEnqueueTaskCallback(b3TaskCallback* Task, void* TaskContext, void* UserContext, const char* TaskName)
    {
        FAnsiString SafeTaskName = FAnsiString(TaskName);
        UE::Tasks::FTask* Handle = new UE::Tasks::FTask(
            UE::Tasks::Launch(TEXT("Box3DTask"),
                [Task, TaskContext, UserContext, SafeTaskName]()
                {
                    TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(*SafeTaskName);
                    Task(TaskContext);
                },
                UE::Tasks::ETaskPriority::High,
                UE::Tasks::EExtendedTaskPriority::None,
                UE::Tasks::ETaskFlags::None));
        return Handle;
    }
    void Box3DFinishTaskCallback(void* UserTask, void* UserContext)
    {
        TRACE_CPUPROFILER_EVENT_SCOPE(Box3DTaskFinsished);
        UE::Tasks::FTask* Handle = static_cast<UE::Tasks::FTask*>(UserTask);
        Handle->Wait();
        delete Handle;
    }
    float CastResultFcnSingleCallback( b3ShapeId shapeId, b3Pos point, b3Vec3 normal, float fraction, uint64_t userMaterialId, int triangleIndex, int childIndex, void* context )
    {
        TArray<FB3RayResult>* RayResults = static_cast<TArray<FB3RayResult>*>(context);
        FB3RayResult GotResult;
        GotResult.bHit = true;
        GotResult.Point = ToUnreal(point);
        GotResult.Normal = ToUnreal(normal);
        GotResult.Fraction = fraction;
        GotResult.ShapeHandle = FB3ShapeHandle(shapeId);
        GotResult.UserMaterialId = userMaterialId;
        GotResult.TriangleIndex = triangleIndex;
        GotResult.ChildIndex = childIndex;
        RayResults->Add(GotResult);
        return fraction;
    }
    float CastResultFcnMultipleCallback( b3ShapeId shapeId, b3Pos point, b3Vec3 normal, float fraction, uint64_t userMaterialId, int triangleIndex, int childIndex, void* context )
    {
        TArray<FB3RayResult>* RayResults = static_cast<TArray<FB3RayResult>*>(context);
        FB3RayResult GotResult;
        GotResult.bHit = true;
        GotResult.Point = ToUnreal(point);
        GotResult.Normal = ToUnreal(normal);
        GotResult.Fraction = fraction;
        GotResult.ShapeHandle = FB3ShapeHandle(shapeId);
        GotResult.UserMaterialId = userMaterialId;
        GotResult.TriangleIndex = triangleIndex;
        GotResult.ChildIndex = childIndex;
        RayResults->Add(GotResult);
        return 1.0;
    }
    float FrictionCallback( float frictionA, uint64_t userMaterialIdA, float frictionB, uint64_t userMaterialIdB )
    {
        const EB3CombineMode FrictionModeA = static_cast<EB3CombineMode>(userMaterialIdA >> 32);
        const EB3CombineMode FrictionModeB = static_cast<EB3CombineMode>(userMaterialIdB >> 32);
        return FrictionModeA == FrictionModeB? CalculateRubbing(FrictionModeA, frictionA, frictionB):
                                            (CalculateRubbing(FrictionModeA, frictionA, frictionB)+
                                                CalculateRubbing(FrictionModeB, frictionA, frictionB))*0.5f;
        
    }
    float RestitutionCallback( float restitutionA, uint64_t userMaterialIdA, float restitutionB, uint64_t userMaterialIdB )
    {
        const EB3CombineMode FrictionModeA = static_cast<EB3CombineMode>(userMaterialIdA);
        const EB3CombineMode FrictionModeB = static_cast<EB3CombineMode>(userMaterialIdB);
        return FrictionModeA == FrictionModeB? CalculateRubbing(FrictionModeA, restitutionA, restitutionB):
                                            (CalculateRubbing(FrictionModeA, restitutionA, restitutionB)+
                                                CalculateRubbing(FrictionModeB, restitutionA, restitutionB))*0.5f;
    }
}