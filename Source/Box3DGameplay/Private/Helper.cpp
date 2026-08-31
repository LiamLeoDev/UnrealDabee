// Copyright (c) 2026 LiamLeo


#include "Helper.h"

#include "Box3DTypes.h"
#include "Box3DCreationBridge.h"
#include "Engine/World.h"
#include "Box3DAsserts.h"
#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/AggregateGeom.h"
#include "Chaos/Core.h"
#include "Chaos/TriangleMeshImplicitObject.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "Box3DMeshDataSubsystem.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
namespace CollisionHelper
{
    ECollisionTraceFlag GetCollisionComplexity(UBodySetup* BodySetup)
    {
        ECollisionTraceFlag Flag = BodySetup->CollisionTraceFlag;
        if (Flag == ECollisionTraceFlag::CTF_UseDefault)
        {
            Flag = UPhysicsSettings::Get()->DefaultShapeComplexity;
        }
        return Flag;
    }
    void GetMeshDef(UBodySetup* BodySetup, FB3MeshDef& MeshDefOut)
    {
        if(!IsValid(BodySetup))
        {
            return;
        }
        for (const Chaos::FTriangleMeshImplicitObjectPtr& TriMeshPtr : BodySetup->TriMeshGeometries)
        {
            if (!TriMeshPtr.IsValid()) continue;
            const Chaos::FTriangleMeshImplicitObject* TriMesh = TriMeshPtr.GetReference();
            if (!TriMesh) continue;
            const Chaos::FTriangleMeshImplicitObject::ParticlesType& Particles = TriMesh->Particles();
            const Chaos::FTrimeshIndexBuffer& Elements = TriMesh->Elements();
            int32 VertexCount = Particles.Size();
            int32 TriangleCount = Elements.GetNumTriangles();
            if (VertexCount < 3) continue;

            const int32 BaseVertexIndex = MeshDefOut.Vertices.Num();
            MeshDefOut.VertexCount += VertexCount;
            MeshDefOut.TriangleCount += TriangleCount;
            MeshDefOut.bWeldVertices = false;
            MeshDefOut.WeldTolerance = 0.0f;
            MeshDefOut.bUseMedianSplit = false;
            MeshDefOut.bIdentifyEdges = false;
            MeshDefOut.Vertices.Reserve(MeshDefOut.VertexCount);
            MeshDefOut.TriangleIndices.Reserve(MeshDefOut.TriangleCount*3);

            for (int32 i = 0; i < VertexCount; ++i)
            {
                MeshDefOut.Vertices.Add((FVector3f)Particles.GetX(i));
            }
            if(Elements.RequiresLargeIndices())
            {
                const TArray<Chaos::TVec3<int32>>& LargeBuffer = Elements.GetLargeIndexBuffer();
                for (int32 i = 0; i < TriangleCount; ++i)
                {
                    MeshDefOut.TriangleIndices.Add(BaseVertexIndex + LargeBuffer[i][0]);
                    MeshDefOut.TriangleIndices.Add(BaseVertexIndex + LargeBuffer[i][1]);
                    MeshDefOut.TriangleIndices.Add(BaseVertexIndex + LargeBuffer[i][2]);
                }
            }
            else
            {
                const TArray<Chaos::TVec3<uint16>>& SmallBuffer = Elements.GetSmallIndexBuffer();
                for (int32 i = 0; i < TriangleCount; ++i)
                {
                    MeshDefOut.TriangleIndices.Add(BaseVertexIndex + SmallBuffer[i][0]);
                    MeshDefOut.TriangleIndices.Add(BaseVertexIndex + SmallBuffer[i][1]);
                    MeshDefOut.TriangleIndices.Add(BaseVertexIndex + SmallBuffer[i][2]);
                }
            }
        }
    }
    void CreateCollisionForMesh(UWorld* World, UStaticMesh* StaticMesh, const FB3BodyHandle& BodyHandle, FB3ShapeDef& ShapeDef,const FVector3f& ComponentScale, TArray<FB3ShapeHandle>* OutShapeHandles)
    {
        if(World && IsValid(StaticMesh) && IsValid(StaticMesh->GetBodySetup()))
        {
            if (GetCollisionComplexity(StaticMesh->GetBodySetup()) != ECollisionTraceFlag::CTF_UseComplexAsSimple)
            {
                const FKAggregateGeom& AggGeom = StaticMesh->GetBodySetup()->AggGeom;
                int32 CurrentBoxes = AggGeom.BoxElems.Num();
                int32 CurrentSpheres = AggGeom.SphereElems.Num();
                int32 CurrentCapsules = AggGeom.SphylElems.Num();
                int32 CurrentConvexs = AggGeom.ConvexElems.Num();
                FB3ShapeHandle ShapeHandle;
                while (CurrentBoxes > 0)
                {
                    CurrentBoxes--;
                    const FKBoxElem& Box = AggGeom.BoxElems[CurrentBoxes];
                    const FKShapeElem* ShapeElem = AggGeom.GetElement(EAggCollisionShape::Box,CurrentBoxes);
                    ShapeDef.Name = ShapeElem->GetName();
                    FTransform3f BoxTransform = FTransform3f(FRotator3f(Box.Rotation),FVector3f(Box.Center),FVector3f(Box.X*0.5f,Box.Y*0.5f,Box.Z*0.5f));
                    ShapeHandle = B3CREATE::CreateBoxShape(BodyHandle, ShapeDef, BoxTransform,ComponentScale);
                    if(ShapeHandle && OutShapeHandles){OutShapeHandles->Add(ShapeHandle);}
                }
                while (CurrentSpheres > 0)
                {
                    CurrentSpheres--;
                    const FKSphereElem& Sphere = AggGeom.SphereElems[CurrentSpheres];
                    const FKShapeElem* ShapeElem = AggGeom.GetElement(EAggCollisionShape::Sphere,CurrentSpheres);
                    ShapeDef.Name = ShapeElem->GetName();
                    ShapeHandle = B3CREATE::CreateSphereShape(BodyHandle,ShapeDef,FB3Sphere{FVector3f(Sphere.Center),Sphere.Radius},ComponentScale);
                    if(ShapeHandle && OutShapeHandles){OutShapeHandles->Add(ShapeHandle);}
                }
                while (CurrentCapsules > 0)
                {
                    CurrentCapsules--;
                    const FKSphylElem& Capsule = AggGeom.SphylElems[CurrentCapsules];
                    const FKShapeElem* ShapeElem = AggGeom.GetElement(EAggCollisionShape::Sphyl,CurrentCapsules);
                    ShapeDef.Name = ShapeElem->GetName();
                    ShapeHandle = B3CREATE::CreateCapsuleShape(
                        BodyHandle,
                        ShapeDef,
                        FTransform3f(FRotator3f(Capsule.Rotation),FVector3f(Capsule.Center)*ComponentScale),
                        Capsule.GetScaledCylinderLength(FVector(ComponentScale)),
                        Capsule.GetScaledRadius(FVector(ComponentScale)));
                    if(ShapeHandle && OutShapeHandles){OutShapeHandles->Add(ShapeHandle);}
                }
                while (CurrentConvexs > 0)
                {
                    CurrentConvexs--;
                    const FKConvexElem& Convex = AggGeom.ConvexElems[CurrentConvexs];
                    const FKShapeElem* ShapeElem = AggGeom.GetElement(EAggCollisionShape::Convex,CurrentConvexs);
                    ShapeDef.Name = ShapeElem->GetName();
                    ShapeHandle = B3CREATE::CreateHullShape(BodyHandle, ShapeDef, Convex.VertexData, Convex.VertexData.Num(),FTransform3f(Convex.GetTransform()),ComponentScale);
                    if(ShapeHandle && OutShapeHandles){OutShapeHandles->Add(ShapeHandle);}
                }
            }
            else
            {
                UBox3DMeshDataSubsystem* MeshDataSubsystem = World->GetSubsystem<UBox3DMeshDataSubsystem>();
                B3_ENSURE_ALWAYS_MSG(MeshDataSubsystem, TEXT("Creating Static Mesh but MeshDataSubsystem is null"));
                if(MeshDataSubsystem)
                {
                    FB3MeshData* MeshData = MeshDataSubsystem->RegisterAndGetMeshData(StaticMesh);
                    FB3ShapeHandle ShapeHandle = B3CREATE::CreateMeshShape(BodyHandle, ShapeDef, MeshData, ComponentScale);
                    if(ShapeHandle && OutShapeHandles){OutShapeHandles->Add(ShapeHandle);}
                }
            }
        }
    }
}
