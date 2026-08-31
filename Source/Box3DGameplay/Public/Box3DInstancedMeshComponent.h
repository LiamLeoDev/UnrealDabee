// Copyright (c) 2026 LiamLeo


#pragma once

#include "Box3DDelegates.h"
#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Box3DTypes.h"
#include "Box3DInstancedMeshComponent.generated.h"

struct FB3InstancedBodyUserData : public FB3BodyUserData
{
    int32 InstanceIndex = 0;
    int32 StableSlot = INDEX_NONE; 
};
struct FB3InstanceData
{
    FB3InstancedBodyUserData BodyUserData;
    FB3ShapeUserData ShapeUserData;
    FB3BodyHandle BodyHandle;
};
UCLASS(ClassGroup=(Box3D), meta=(BlueprintSpawnableComponent, DisplayName = "Box3D Instanced Mesh Component"),HideCategories=("Physics","Collision","HLOD","ComponentReplication", "MeshPainting"))
class BOX3DGAMEPLAY_API UBox3DInstancedMeshComponent : public UInstancedStaticMeshComponent
{
    GENERATED_BODY()

public:
    UBox3DInstancedMeshComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnRegister() override;
    virtual void OnUnregister() override;
    virtual int32 AddInstance(const FTransform& InstanceTransform, bool bWorldSpace = false) override;
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|InstancesCreation")
    FVector GridSpacing = FVector(150,150,110);

    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|InstancesCreation")
    FVector GridDim = FVector(5,5,10);


    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody", meta=(ShowOnlyInnerProperties))
    FB3BodyDef BodyDef;
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|CollisionDef", meta=(ShowOnlyInnerProperties))
    FB3ShapeDef ShapeDef;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "Box3D On Begin Overlap 𝘽𝙊𝙓3𝘿"), Category="Box3D|Events")
    FB3OnBeginOverlap OnBeginOverlap;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "Box3D On End Overlap 𝘽𝙊𝙓3𝘿"), Category="Box3D|Events")
    FB3OnEndOverlap OnEndOverlap;
    
    
private:
    static void BeginCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent);
    static void BodyMoveCallback(FB3BodyUserData* BodyUserData, UObject* Object, const FTransform& Transform);
    static void EndCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent);
    void CreateBodyAndCollisionForInstance(int32 InstanceIndex, FTransform Transform);
    TSparseArray<FB3InstanceData> InstancesData;
    void BodiesUpdatedCallback();
};