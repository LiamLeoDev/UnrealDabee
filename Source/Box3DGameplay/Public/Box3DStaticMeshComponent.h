// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Box3DTypes.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "Box3DDelegates.h"
#include "Box3DStaticMeshComponent.generated.h"



UCLASS(ClassGroup=(Box3D), meta=(BlueprintSpawnableComponent, DisplayName = "Box3D Static Mesh Component"),HideCategories=("Physics","Collision","HLOD","ComponentReplication", "MeshPainting"))
class BOX3DGAMEPLAY_API UBox3DStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UBox3DStaticMeshComponent();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual bool SetStaticMesh(class UStaticMesh* NewMesh) override;
    virtual void OnRegister() override;
    virtual void OnUnregister() override;
    virtual bool AttachToComponent(USceneComponent* InParent, const FAttachmentTransformRules& AttachmentRules, FName InSocketName = NAME_None) override;
    virtual void DetachFromComponent(const FDetachmentTransformRules& DetachmentRules) override;

    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody", meta=(ShowOnlyInnerProperties))
    FB3BodyDef BodyDef;
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|CollisionDef", meta=(ShowOnlyInnerProperties))
    FB3ShapeDef ShapeDef;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "Box3D On Begin Overlap 𝘽𝙊𝙓3𝘿"), Category="Box3D|Events")
    FB3OnBeginOverlap OnBeginOverlap;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "Box3D On End Overlap 𝘽𝙊𝙓3𝘿"), Category="Box3D|Events")
    FB3OnEndOverlap OnEndOverlap;
    UFUNCTION(BlueprintPure, Category="Box3D", meta=(CompactNodeTitle="BODY Handle"))
    FB3BodyHandle GetRigidBodyHandle();
    
    static void BodyMoveCallback(FB3BodyUserData* BodyUserData, UObject* Object, const FTransform& Transform);
    static void BeginCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent);
    static void EndCallback(FB3ShapeUserData* ShapeUserData, UObject* Object, const FB3SensorTouchEvent& SensorTouchEvent);


private:
    FB3BodyHandle BodyHandle = FB3BodyHandle(b3_nullBodyId);
    FB3BodyUserData BodyUserData;
    FB3ShapeUserData ShapeUserData;
    FB3JointHandle WeldJointHandle;
    void CreateBody();
    void CreateShape();
    
protected:
    bool LinkToParent();
    void UnlinkFromParent();
public:
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};

