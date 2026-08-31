// Copyright (c) 2026 LiamLeo


#include "Box3DShape.h"
#include "Box3DTypes.h"
#include "box3d/box3d.h"
#include "box3d/id.h"
#include "box3d/types.h"
#include "DrawDebugHelpers.h"
#include "Box3DAsserts.h"

void UBox3DShape::DestroyShape(FB3ShapeHandle& ShapeHandle, bool UpdateBodyMass )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("DestroyShape called wih an invalid Shape Handle")); 
    b3DestroyShape(ShapeHandle.GetID(),UpdateBodyMass);
    ShapeHandle = FB3ShapeHandle(b3_nullShapeId);
}
bool UBox3DShape::IsValid(const FB3ShapeHandle ShapeHandle)
{
    B3_ENSURE_MSG_RET(ShapeHandle, false, TEXT("IsValid called wih an invalid Shape Handle"));
    return bool(ShapeHandle);
}
EB3ShapeType UBox3DShape::GetType(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, EB3ShapeType::None, TEXT("GetType called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetType(ShapeHandle.GetID()));
}
FB3BodyHandle UBox3DShape::GetBody(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FB3BodyHandle{b3_nullBodyId}, TEXT("GetBody called wih an invalid Shape Handle"));
    return FB3BodyHandle(b3Shape_GetBody(ShapeHandle.GetID()));
}
FB3WorldHandle UBox3DShape::GetPhysicsWorld(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FB3WorldHandle{b3_nullWorldId}, TEXT("GetPhysicsWorld called wih an invalid Shape Handle"));
    return FB3WorldHandle(b3Shape_GetWorld(ShapeHandle.GetID()));
}
bool UBox3DShape::IsSensor(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, false, TEXT("IsSensor called wih an invalid Shape Handle"));
    return b3Shape_IsSensor(ShapeHandle.GetID());
}
void UBox3DShape::SetName(const FB3ShapeHandle ShapeHandle,const FName& Name )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("SetName called wih an invalid Shape Handle")); 
    b3Shape_SetName( ShapeHandle.GetID(),Name.IsNone() ? nullptr : TCHAR_TO_UTF8(*Name.ToString()));
}
FName UBox3DShape::GetName(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, NAME_None, TEXT("GetName called wih an invalid Shape Handle"));
    return FName(UTF8_TO_TCHAR(b3Shape_GetName(ShapeHandle.GetID())));
}
UObject* UBox3DShape::BP_GetUserData(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, nullptr, TEXT(":: called wih an invalid Shape Handle"));
    if(FB3ShapeUserData* UserData = GetUserData(ShapeHandle))
    {
        return UserData->Object.Get();
    }
    return nullptr;
}
FB3ShapeUserData* UBox3DShape::GetUserData(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, nullptr, TEXT(":: called wih an invalid Shape Handle"));
    return static_cast<FB3ShapeUserData*>(b3Shape_GetUserData(ShapeHandle.GetID()));
}
void UBox3DShape::SetUserData(const FB3ShapeHandle ShapeHandle, FB3ShapeUserData* UserData )
{
    if(!ShapeHandle) return;
    b3Shape_SetUserData(ShapeHandle.GetID(), UserData);
}
void UBox3DShape::SetDensity(const FB3ShapeHandle ShapeHandle, float Density, bool UpdateBodyMass )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("SetDensity called wih an invalid Shape Handle")); 
    b3Shape_SetDensity(ShapeHandle.GetID(), Density, UpdateBodyMass);
}
float UBox3DShape::GetDensity(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, 0.0f, TEXT("GetDensity called wih an invalid Shape Handle"));
    return b3Shape_GetDensity(ShapeHandle.GetID());
}
void UBox3DShape::SetFriction(const FB3ShapeHandle ShapeHandle, float Friction )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("SetFriction called wih an invalid Shape Handle")); 
    b3Shape_SetFriction(ShapeHandle.GetID(), Friction);
}
float UBox3DShape::GetFriction(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, 0.0f, TEXT("GetFriction called wih an invalid Shape Handle"));
    return b3Shape_GetFriction(ShapeHandle.GetID());
}
void UBox3DShape::SetRestitution(const FB3ShapeHandle ShapeHandle, float Restitution )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("SetRestitution called wih an invalid Shape Handle")); 
    b3Shape_SetRestitution(ShapeHandle.GetID(), Restitution);
}
float UBox3DShape::GetRestitution(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, 0.0f, TEXT("GetRestitution called wih an invalid Shape Handle"));
    return b3Shape_GetRestitution(ShapeHandle.GetID());
}
void UBox3DShape::SetSurfaceMaterial(const FB3ShapeHandle ShapeHandle,const FB3SurfaceMaterial& SurfaceMaterial )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("SetSurfaceMaterial called wih an invalid Shape Handle")); 
    b3Shape_SetSurfaceMaterial(ShapeHandle.GetID(), ToNative(SurfaceMaterial));
}
FB3SurfaceMaterial UBox3DShape::GetSurfaceMaterial(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, (FB3SurfaceMaterial{0.0f,EB3CombineMode::None,0.0f,EB3CombineMode::None}), TEXT("GetSurfaceMaterial called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetSurfaceMaterial(ShapeHandle.GetID()));
}
int UBox3DShape::GetMeshMaterialCount(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, 0, TEXT("GetMeshMaterialCount called wih an invalid Shape Handle"));
    return b3Shape_GetMeshMaterialCount(ShapeHandle.GetID());
}
void UBox3DShape::SetMeshMaterial(const FB3ShapeHandle ShapeHandle,const FB3SurfaceMaterial& SurfaceMaterial, int Index )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("SetMeshMaterial called wih an invalid Shape Handle")); 
    b3Shape_SetMeshMaterial(ShapeHandle.GetID(), ToNative(SurfaceMaterial), Index);
}
FB3SurfaceMaterial UBox3DShape::GetMeshSurfaceMaterial(const FB3ShapeHandle ShapeHandle, int Index )
{
    B3_ENSURE_MSG_RET(ShapeHandle, (FB3SurfaceMaterial{0.0f,EB3CombineMode::None,0.0f,EB3CombineMode::None}), TEXT("GetMeshSurfaceMaterial called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetMeshSurfaceMaterial(ShapeHandle.GetID(), Index));
}
FB3Filter UBox3DShape::GetFilter(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FB3Filter{}, TEXT("GetFilter called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetFilter(ShapeHandle.GetID()));
}
void UBox3DShape::SetFilter(const FB3ShapeHandle ShapeHandle,const FB3Filter& Filter, bool InvokeContacts )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("SetFilter called wih an invalid Shape Handle")); 
    b3Shape_SetFilter(ShapeHandle.GetID(), ToNative(Filter), InvokeContacts);
}
void UBox3DShape::EnableSensorEvents(const FB3ShapeHandle ShapeHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("EnableSensorEvents called wih an invalid Shape Handle")); 
    b3Shape_EnableSensorEvents(ShapeHandle.GetID(), Flag);
}
bool UBox3DShape::AreSensorEventsEnabled(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, false, TEXT("AreSensorEventsEnabled called wih an invalid Shape Handle"));
    return b3Shape_AreSensorEventsEnabled(ShapeHandle.GetID());
}
void UBox3DShape::EnableContactEvents(const FB3ShapeHandle ShapeHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("EnableContactEvents called wih an invalid Shape Handle")); 
    b3Shape_EnableContactEvents(ShapeHandle.GetID(), Flag);
}
bool UBox3DShape::AreContactEventsEnabled(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, false, TEXT("AreContactEventsEnabled called wih an invalid Shape Handle"));
    return b3Shape_AreContactEventsEnabled(ShapeHandle.GetID());
}
void UBox3DShape::EnablePreSolveEvents(const FB3ShapeHandle ShapeHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("EnablePreSolveEvents called wih an invalid Shape Handle")); 
    b3Shape_EnablePreSolveEvents(ShapeHandle.GetID(), Flag);
}
bool UBox3DShape::ArePreSolveEventsEnabled(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, false, TEXT("ArePreSolveEventsEnabled called wih an invalid Shape Handle"));
    return b3Shape_ArePreSolveEventsEnabled(ShapeHandle.GetID());
}
void UBox3DShape::EnableHitEvents(const FB3ShapeHandle ShapeHandle, bool Flag )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("EnableHitEvents called wih an invalid Shape Handle")); 
    b3Shape_EnableHitEvents(ShapeHandle.GetID(), Flag);
}
bool UBox3DShape::AreHitEventsEnabled(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, false, TEXT("AreHitEventsEnabled called wih an invalid Shape Handle"));
    return b3Shape_AreHitEventsEnabled(ShapeHandle.GetID());
}
FB3Sphere UBox3DShape::GetSphere(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FB3Sphere{}, TEXT("GetSphere called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetSphere(ShapeHandle.GetID()));
}
FB3Capsule UBox3DShape::GetCapsule(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FB3Capsule{}, TEXT("GetCapsule called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetCapsule(ShapeHandle.GetID()));
}

int UBox3DShape::GetContactCapacity(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, 0, TEXT("GetContactCapacity called wih an invalid Shape Handle"));
    return b3Shape_GetContactCapacity(ShapeHandle.GetID());
}
// int GetContactData(const FB3ShapeHandle ShapeHandle, b3ContactData* contactData, int Capacity ) // Will add this later
int UBox3DShape::GetSensorCapacity(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, 0, TEXT("GetSensorCapacity called wih an invalid Shape Handle"));
    return b3Shape_GetSensorCapacity(ShapeHandle.GetID());
}
// int GetSensorData(const FB3ShapeHandle ShapeHandle, b3ShapeId* visitorIds, int Capacity ) // Will add this later
FB3AABB UBox3DShape::GetAABB(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FB3AABB{}, TEXT("GetAABB called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetAABB(ShapeHandle.GetID()));
}
FB3MassData UBox3DShape::ComputeMassData(const FB3ShapeHandle ShapeHandle )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FB3MassData{}, TEXT("ComputeMassData called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_ComputeMassData(ShapeHandle.GetID()));
}
FVector3f UBox3DShape::GetClosestPoint(const FB3ShapeHandle ShapeHandle, const FVector3f& Target )
{
    B3_ENSURE_MSG_RET(ShapeHandle, FVector3f::ZeroVector, TEXT("GetClosestPoint called wih an invalid Shape Handle"));
    return ToUnreal(b3Shape_GetClosestPoint(ShapeHandle.GetID(), ToNativeVec(Target)));
}
void UBox3DShape::ApplyWind(const FB3ShapeHandle ShapeHandle, const FVector3f& Wind, float Drag, float Lift, float MaxSpeed, bool Wake )
{
    B3_ENSURE_MSG_RET(ShapeHandle,, TEXT("ApplyWind called wih an invalid Shape Handle")); 
    b3Shape_ApplyWind(ShapeHandle.GetID(), ToNativeVec(Wind), Drag, Lift, MaxSpeed, Wake);
}
