// Copyright (c) 2026 LiamLeo

#pragma once

#include "CoreMinimal.h"
#include "box3d/box3d.h"
#include "Box3DTypes.generated.h"

FORCEINLINE b3Pos            ToNativePos(const FVector& V) { return b3Pos(V.X, V.Y, V.Z); }
FORCEINLINE b3Vec3           ToNativeVec(const FVector3f& V) { return b3Vec3(V.X, V.Y, V.Z); }
FORCEINLINE FVector          ToUnreal(const b3Pos& V) { return FVector(V.x, V.y, V.z); }
FORCEINLINE FVector3f        ToUnreal(const b3Vec3& V) { return FVector3f(V.x, V.y, V.z); }
FORCEINLINE b3Quat           ToNative(const FQuat& Q) { return b3Quat({static_cast<float>(Q.X), static_cast<float>(Q.Y), static_cast<float>(Q.Z)}, static_cast<float>(Q.W)); }
FORCEINLINE b3Quat           ToNative(const FQuat4f& Q) { return b3Quat({Q.X, Q.Y, Q.Z},Q.W); }
FORCEINLINE FQuat4f          ToUnreal(const b3Quat& Q) { return FQuat4f(Q.v.x, Q.v.y, Q.v.z, Q.s); }
FORCEINLINE b3WorldTransform ToNativeWorldTransform(const FTransform& Transform) { return {ToNativePos(Transform.GetLocation()), ToNative(Transform.GetRotation())}; }
FORCEINLINE b3Transform      ToNativeTransform(const FTransform3f& Transform) { return {ToNativeVec(Transform.GetLocation()), ToNative(Transform.GetRotation())}; }
FORCEINLINE FTransform       ToUnreal(const b3WorldTransform& Transform) { return FTransform(FQuat(ToUnreal(Transform.q)), ToUnreal(Transform.p), FVector::OneVector); }
FORCEINLINE FTransform3f     ToUnreal(const b3Transform& Transform) { return FTransform3f(ToUnreal(Transform.q), ToUnreal(Transform.p), FVector3f::OneVector); }
FORCEINLINE FMatrix          ToUnreal(const b3Matrix3& Matrix)
{
    FMatrix Result;
    Result.M[0][0] = Matrix.cx.x;
    Result.M[1][0] = Matrix.cx.y;
    Result.M[2][0] = Matrix.cx.z;

    Result.M[0][1] = Matrix.cy.x;
    Result.M[1][1] = Matrix.cy.y;
    Result.M[2][1] = Matrix.cy.z;

    Result.M[0][2] = Matrix.cz.x;
    Result.M[1][2] = Matrix.cz.y;
    Result.M[2][2] = Matrix.cz.z;
    return Result;
}
FORCEINLINE b3Matrix3 ToNative( const FMatrix& Matrix)
{
    b3Matrix3 Result;
    Result.cx.x = Matrix.M[0][0];
    Result.cx.y = Matrix.M[1][0];
    Result.cx.z = Matrix.M[2][0];

    Result.cy.x = Matrix.M[0][1];
    Result.cy.y = Matrix.M[1][1];
    Result.cy.z = Matrix.M[2][1];

    Result.cz.x = Matrix.M[0][2];
    Result.cz.y = Matrix.M[1][2];
    Result.cz.z = Matrix.M[2][2];
    return Result;
}

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EB3ObjectFlags : uint32
{
    Static       = 1 << 0,
    Dynamic      = 1 << 1,
    Player       = 1 << 2,
    Vehicle      = 1 << 3,
    Projectile   = 1 << 4,

    Custom_01    = 1 << 5,
    Custom_02    = 1 << 6,
    Custom_03    = 1 << 7,
    Custom_04    = 1 << 8,
    Custom_05    = 1 << 9,
    Custom_06    = 1 << 10,
    Custom_07    = 1 << 11,
    Custom_08    = 1 << 12,
    Custom_09    = 1 << 13,
    Custom_10    = 1 << 14,
    Custom_11    = 1 << 15,
    Custom_12    = 1 << 16,
    Custom_13    = 1 << 17,
    Custom_14    = 1 << 18,
    Custom_15    = 1 << 19,
    Custom_16    = 1 << 20,
    Custom_17    = 1 << 21,
    Custom_18    = 1 << 22,
    Custom_19    = 1 << 23,
    Custom_20    = 1 << 24,
    Custom_21    = 1 << 25,
    Custom_22    = 1 << 26,
    Custom_23    = 1 << 27,
    Custom_24    = 1 << 28,
    Custom_25    = 1 << 29,
    Custom_26    = 1 << 30
};

ENUM_CLASS_FLAGS(EB3ObjectFlags)

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EB3TraceFlags : uint32
{
    Visibility   = 1 << 0,
    LineOfSight  = 1 << 1,
    Camera       = 1 << 2,
    Other_2      = 1 << 3,
    Other_3      = 1 << 4,

    Custom_01    = 1 << 5,
    Custom_02    = 1 << 6,
    Custom_03    = 1 << 7,
    Custom_04    = 1 << 8,
    Custom_05    = 1 << 9,
    Custom_06    = 1 << 10,
    Custom_07    = 1 << 11,
    Custom_08    = 1 << 12,
    Custom_09    = 1 << 13,
    Custom_10    = 1 << 14,
    Custom_11    = 1 << 15,
    Custom_12    = 1 << 16,
    Custom_13    = 1 << 17,
    Custom_14    = 1 << 18,
    Custom_15    = 1 << 19,
    Custom_16    = 1 << 20,
    Custom_17    = 1 << 21,
    Custom_18    = 1 << 22,
    Custom_19    = 1 << 23,
    Custom_20    = 1 << 24,
    Custom_21    = 1 << 25,
    Custom_22    = 1 << 26,
    Custom_23    = 1 << 27,
    Custom_24    = 1 << 28,
    Custom_25    = 1 << 29,
    Custom_26    = 1 << 30
};

ENUM_CLASS_FLAGS(EB3TraceFlags)

UENUM(BlueprintType)
enum class ESortType : uint8
{
	None,
	Ascending,
	Descending
};
UENUM(BlueprintType)
enum class EB3JointType : uint8
{
    None,
	DistanceJoint,
	SphericalJoint,
	ParallelJoint,
	FilterJoint,
	MotorJoint,
	PrismaticJoint,
	RevoluteJoint,
	WeldJoint,
	WheelJoint,
};
UENUM(BlueprintType)
enum class EB3ShapeType : uint8
{
    None,
	CapsuleShape,	/// A capsule is an extruded sphere
	CompoundShape,	/// A baked compound shape composed of spheres, capsules, hulls, and meshes
	HeightShape,	/// A height field useful for terrain
	HullShape,		/// A convex hull
	MeshShape,		/// A triangle soup
	SphereShape,	/// A sphere with an offset
	ShapeTypeCount	/// The number of shape types
};
UENUM(BlueprintType)
enum class EB3CombineMode : uint8
{
    None = 0 UMETA(Hidden),
    Average = 1 UMETA(DisplayName = "Average"),
    Min = 2 UMETA(DisplayName = "Min"),
    Multiply = 4 UMETA(DisplayName = "Multiply"),
    MultiplyThenSqrt = 8 UMETA(DisplayName = "Sqrt(Multiply)"),
    Max = 16 UMETA(DisplayName = "Max"),
    Harmonic = 32 UMETA(DisplayName = "Harmonic")
};

UENUM(BlueprintType)
enum class EB3BodyType : uint8
{
    None UMETA(Hidden),
    Static UMETA(DisplayName = "Static"),
    Kinematic UMETA(DisplayName = "Kinematic"),
    Dynamic UMETA(DisplayName = "Dynamic")
};
FORCEINLINE b3JointType ToNative(EB3JointType Type)
{
	switch(Type)
	{
		case EB3JointType::DistanceJoint : return b3_distanceJoint;
		case EB3JointType::SphericalJoint: return b3_sphericalJoint;
		case EB3JointType::ParallelJoint : return b3_parallelJoint;
		case EB3JointType::FilterJoint   : return b3_filterJoint;
		case EB3JointType::MotorJoint    : return b3_motorJoint;
		case EB3JointType::PrismaticJoint: return b3_prismaticJoint;
		case EB3JointType::RevoluteJoint : return b3_revoluteJoint;
		case EB3JointType::WeldJoint     : return b3_weldJoint;
		case EB3JointType::WheelJoint    : return b3_wheelJoint;
		default 						 : return b3_sphericalJoint; //Will chang in future fine for now if none is passed
	}
}
FORCEINLINE EB3JointType ToUnreal(b3JointType Type)
{
	switch(Type)
	{
		case b3JointType::b3_distanceJoint : return EB3JointType::DistanceJoint;
		case b3JointType::b3_sphericalJoint: return EB3JointType::SphericalJoint;
		case b3JointType::b3_parallelJoint : return EB3JointType::ParallelJoint;
		case b3JointType::b3_filterJoint   : return EB3JointType::FilterJoint;
		case b3JointType::b3_motorJoint    : return EB3JointType::MotorJoint;
		case b3JointType::b3_prismaticJoint: return EB3JointType::PrismaticJoint;
		case b3JointType::b3_revoluteJoint : return EB3JointType::RevoluteJoint;
		case b3JointType::b3_weldJoint     : return EB3JointType::WeldJoint;
		case b3JointType::b3_wheelJoint    : return EB3JointType::WheelJoint;
		default                            : return EB3JointType::None;
	}
}
FORCEINLINE b3ShapeType ToNative(EB3ShapeType Type)
{
	switch(Type)
	{
		case EB3ShapeType::CapsuleShape  : return b3_capsuleShape;
		case EB3ShapeType::CompoundShape : return b3_compoundShape;
		case EB3ShapeType::HeightShape   : return b3_heightShape;
		case EB3ShapeType::HullShape     : return b3_hullShape;
		case EB3ShapeType::MeshShape     : return b3_meshShape;
		case EB3ShapeType::SphereShape   : return b3_sphereShape;
		case EB3ShapeType::ShapeTypeCount: return b3_shapeTypeCount;
		default                          : return b3_shapeTypeCount;
	}
}
FORCEINLINE EB3ShapeType ToUnreal(b3ShapeType Type)
{
	switch(Type)
	{
		case b3ShapeType::b3_capsuleShape  : return EB3ShapeType::CapsuleShape;
		case b3ShapeType::b3_compoundShape : return EB3ShapeType::CompoundShape;
		case b3ShapeType::b3_heightShape   : return EB3ShapeType::HeightShape;
		case b3ShapeType::b3_hullShape     : return EB3ShapeType::HullShape;
		case b3ShapeType::b3_meshShape     : return EB3ShapeType::MeshShape;
		case b3ShapeType::b3_sphereShape   : return EB3ShapeType::SphereShape;
		case b3ShapeType::b3_shapeTypeCount: return EB3ShapeType::ShapeTypeCount;
		default                            : return EB3ShapeType::ShapeTypeCount;
	}
}
FORCEINLINE b3BodyType ToNative(EB3BodyType Type)
{
	switch(Type)
	{
		case EB3BodyType::Static   : return b3_staticBody;
		case EB3BodyType::Kinematic: return b3_kinematicBody;
		case EB3BodyType::Dynamic  : return b3_dynamicBody;
		default                    : return b3_staticBody;
	}
}
FORCEINLINE EB3BodyType ToUnreal(b3BodyType Type)
{
	switch(Type)
	{
		case b3_staticBody   : return EB3BodyType::Static;
		case b3_kinematicBody: return EB3BodyType::Kinematic;
		case b3_dynamicBody  : return EB3BodyType::Dynamic;
		default              : return EB3BodyType::Static;
	}
}

struct BOX3DWRAPPER_API FB3MeshData
{
public:
    FB3MeshData() = default;
    explicit FB3MeshData(b3MeshData* InMeshData):Data(InMeshData){}
    b3MeshData* GetData() const { return Data; }
private:
    b3MeshData* Data = nullptr;
};

struct BOX3DWRAPPER_API FB3RecordingHandle
{
    FB3RecordingHandle() = default;
    explicit FB3RecordingHandle(b3Recording* InRecording):Recording(InRecording){}
    b3Recording* GetRecording() const{return Recording;}
    explicit operator bool() const{return Recording != nullptr;}
private:
    b3Recording* Recording = nullptr;
};

struct BOX3DWRAPPER_API FB3WorldHandle
{
    FB3WorldHandle() = default;
    explicit FB3WorldHandle(b3WorldId InWorldId):StoredID(b3StoreWorldId(InWorldId)){}
    b3WorldId GetID() const {return b3LoadWorldId(StoredID);}
    explicit operator bool() const { return b3World_IsValid(b3LoadWorldId(StoredID)); }
private:
    uint32 StoredID = 0;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3BodyHandle
{
    GENERATED_BODY()
    FB3BodyHandle() = default;
    explicit FB3BodyHandle(b3BodyId InBodyId):StoredID(b3StoreBodyId(InBodyId)){}
    b3BodyId GetID() const {return b3LoadBodyId(StoredID);}
    explicit operator bool() const { return b3Body_IsValid(b3LoadBodyId(StoredID)); }
private:
    uint64 StoredID = 0;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3ShapeHandle
{
    GENERATED_BODY()
    FB3ShapeHandle() = default;
    explicit FB3ShapeHandle(b3ShapeId InShapeId):StoredID(b3StoreShapeId(InShapeId)){}
    b3ShapeId GetID() const {return b3LoadShapeId(StoredID);}
    explicit operator bool() const { return b3Shape_IsValid(b3LoadShapeId(StoredID)); }
private:
    uint64 StoredID = 0;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3JointHandle
{
    GENERATED_BODY()

    FB3JointHandle() = default;
    explicit FB3JointHandle(b3JointId InJointId):StoredID(b3StoreJointId(InJointId)){}
    b3JointId GetID() const {return b3LoadJointId(StoredID);}
    explicit operator bool() const { return b3Joint_IsValid(b3LoadJointId(StoredID)); }
private:
    uint64 StoredID = 0;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3ContactHandle
{
    GENERATED_BODY()
public:
    FB3ContactHandle() = default;
    explicit FB3ContactHandle(b3ContactId InContactId){b3StoreContactId(InContactId,StoredID);}
    b3ContactId GetID() {return b3LoadContactId(StoredID);}
    explicit operator bool() { return b3Contact_IsValid(b3LoadContactId(StoredID)); }
private:
    uint32 StoredID[3] = {};
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3MotionLocks
{
    GENERATED_BODY()
	
	/// Prevent translation along the x-axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionLocks")
    bool bLockLinearX = false;

	/// Prevent translation along the y-axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionLocks")
    bool bLockLinearY = false;

	/// Prevent translation along the z-axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionLocks")
    bool bLockLinearZ = false;

	/// Prevent rotation around the x-axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionLocks")
    bool bLockAngularX = false;

	/// Prevent rotation around the y-axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionLocks")
    bool bLockAngularY = false;

	/// Prevent rotation around the z-axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionLocks")
    bool bLockAngularZ = false;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3Capacity
{
	GENERATED_BODY()
	
	/// Number of expected static shapes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Capacity")
	int32 StaticShapeCount = 1000;
	
	/// Number of expected dynamic and kinematic shapes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Capacity")
	int32 DynamicShapeCount = 1000;
	
	/// Number of expected static bodies.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Capacity")
	int32 StaticBodyCount = 1000;
	
	/// Number of expected dynamic and kinematic bodies.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Capacity")
	int32 DynamicBodyCount = 1000;
	
	/// Number of expected contacts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Capacity")
	int32 ContactCount = 1000;

};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3MassData
{
	GENERATED_BODY()
	
	/// The shape mass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MassData")
	float Mass = 0.0f;
	
	/// The local center of mass position.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MassData")
	FVector3f CenterOfMass = FVector3f::ZeroVector;
	
	/// The inertia tensor about the shape center of mass.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MassData")
	FMatrix Inertia3x3 = FMatrix::Identity;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3Filter
{
	GENERATED_BODY()
	
	/// The collision category bits. Normally you would just set one bit. The category bits should
	/// represent your application object types. For example:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3ObjectFlags"), Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
    int32 ObjectType = 1;
	
	/// The ObjectsToIgnore bits. This states the categories that this shape would ignore for collision.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3ObjectFlags"), Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
	int32 ObjectsToIgnore = 0;
	
	/// The TracesToIgnore. This states the categories that this shape would ignore for collision.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3TraceFlags"), Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
	int32 TracesToIgnore = 0;
	
	/// Collision groups allow a certain group of objects to never collide (negative)
	/// or always collide (positive). A group index of zero has no effect. Non-zero group filtering
	/// always wins against the ObjectsToIgnore bits.
	/// For example, you may want ragdolls to collide with other ragdolls but you don't want
	/// ragdoll self-collision. In this case you would give each ragdoll a unique negative group index
	/// and apply that group index to all shapes on the ragdoll.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
    int32 GroupIndex = 0;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3SurfaceMaterial
{
	GENERATED_BODY()

	/// The Coulomb (dry) friction coefficient, usually in the range [0,1].
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="𝘽𝙊𝙓3𝘿|CollisionDef|PhysicsMaterial")
	float Friction = 0.6f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="𝘽𝙊𝙓3𝘿|CollisionDef|PhysicsMaterial")
    EB3CombineMode FrictionCombineMode = EB3CombineMode::MultiplyThenSqrt;

    /// The coefficient of restitution (bounce) usually in the range [0,1].
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="𝘽𝙊𝙓3𝘿|CollisionDef|PhysicsMaterial")
	float Restitution = 0.3f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="𝘽𝙊𝙓3𝘿|CollisionDef|PhysicsMaterial")
    EB3CombineMode RestitutionCombineMode = EB3CombineMode::Max;

	/// The rolling resistance usually in the range [0,1]. This is only used for spheres and capsules.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="𝘽𝙊𝙓3𝘿|CollisionDef|PhysicsMaterial")
	float RollingResistance = 0.0f;
    
	/// The tangent velocity for conveyor belts. This is local to the shape and will be projected
	/// onto the contact surface.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="𝘽𝙊𝙓3𝘿|CollisionDef|PhysicsMaterial")
	FVector3f TangentVelocity = FVector3f::ZeroVector;
};
struct FB3ShapeUserData;
struct FB3BodyUserData;
struct FB3JointUserData;
USTRUCT()
struct BOX3DWRAPPER_API FB3WorldDef
{
	GENERATED_BODY()


	/// Gravity vector. Box3D has no up-vector defined.
	UPROPERTY(EditAnywhere, Category="WorldDef")
	FVector3f Gravity = FVector3f(0.f, 0.f, -980.0f);

	/// Restitution speed threshold in cm/s. Collisions above this
	/// speed have restitution applied (will bounce).
	UPROPERTY(EditAnywhere, meta = (ForceUnits = "cm"), Category="WorldDef")
	float RestitutionThreshold = 100.0f;

	/// Hit event speed threshold in cm/s. Collisions above this
	/// speed can generate hit events if the shape also enables hit events.
	UPROPERTY(EditAnywhere, meta = (ForceUnits = "cm"), Category="WorldDef")
	float HitEventThreshold = 100.0f;

	/// Contact stiffness. Cycles per second. Increasing this increases the speed of overlap recovery, but can introduce jitter.
	UPROPERTY(EditAnywhere, Category="WorldDef")
	float ContactHertz = 30.0f;

	/// Contact bounciness. Non-dimensional. You can speed up overlap recovery by decreasing this with
	/// the trade-off that overlap resolution becomes more energetic.
	UPROPERTY(EditAnywhere, Category="WorldDef")
	float ContactDampingRatio = 10.0f;

	/// This parameter controls how fast overlap is resolved in cm/s. This only
	/// puts a cap on the resolution speed. The resolution speed is increased by increasing the hertz and/or
	/// decreasing the damping ratio.
	UPROPERTY(EditAnywhere, meta = (ForceUnits = "cm"), Category="WorldDef")
	float ContactSpeed = 300.0f;

	/// Maximum linear speed in cm/s.
	UPROPERTY(EditAnywhere, meta = (ForceUnits = "cm"), Category="WorldDef")
	float MaximumLinearSpeed = 40000.0f;

	/// Can bodies go to sleep to improve performance
	UPROPERTY(EditAnywhere, Category="WorldDef")
	bool bEnableSleep = true;

	/// Enable continuous collision
	UPROPERTY(EditAnywhere, Category="WorldDef")
	bool bEnableContinuous = true;

	UPROPERTY(EditAnywhere, Category="WorldDef")
    bool bAutoWorkers = true;

	/// Number of workers to use with the provided task system. Box3D performs best when using only
	/// performance cores and accessing a single L2 cache. Efficiency cores and hyper-threading provide
	/// little benefit and may even harm performance.
	/// This is clamped to the range [1, B3_MAX_WORKERS]. Using a value above 1 will turn on multithreading.
	UPROPERTY(EditAnywhere,meta=(EditCondition="!bAutoWorkers", EditConditionHides), Category="WorldDef")
	int32 WorkerCount = 1;

	/// Optional initial capacities
	UPROPERTY(EditAnywhere, Category="WorldDef")
	FB3Capacity Capacity;

};

USTRUCT()
struct BOX3DWRAPPER_API FB3BodyDef
{
    GENERATED_BODY()
	
	/// Use this to store application specific body data.
    FB3BodyUserData* UserData = nullptr;
	
	/// Used to disable a body. A disabled body does not move or collide.
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody")
    bool bIsEnabled = true;
	
	/// The body type: static, kinematic, or dynamic.
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody")
    EB3BodyType Type = EB3BodyType::Static;
	
	/// Linear damping is used to reduce the linear velocity. The damping parameter
	/// can be larger than 1 but the damping effect becomes sensitive to the
	/// time step when the damping parameter is large.
	/// Generally linear damping is undesirable because it makes objects move slowly
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody")
    float LinearDamping = 0.0f;
	
	/// Angular damping is used to reduce the angular velocity. The damping parameter
	/// can be larger than 1.0f but the damping effect becomes sensitive to the
	/// time step when the damping parameter is large.
	/// Angular damping can be used to slow down rotating bodies.
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody")
    float AngularDamping = 0.0f;
	
	/// Scale the gravity applied to this body. Non-dimensional.
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody")
    float GravityScale = 1.0f;
	
	/// Motions locks to restrict linear and angular movement
    UPROPERTY(EditAnywhere, Category="𝘽𝙊𝙓3𝘿|RigidBody")
    FB3MotionLocks MotionLocks;

    FVector Position = FVector::ZeroVector;

    FQuat Rotation = FQuat::Identity;
	
	/// Is this body initially awake or sleeping?
    UPROPERTY(EditAnywhere,meta=(DisplayName="Awake"),Category="𝘽𝙊𝙓3𝘿|RigidBody|Initial")
    bool bIsAwake = true;
	
	/// The initial linear velocity of the body's origin. Usually in meters per second.
    UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|RigidBody|Initial")
    FVector3f LinearVelocity = FVector3f::ZeroVector;
	
	/// The initial angular velocity of the body. Radians per second.
    UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|RigidBody|Initial")
    FVector3f AngularVelocity = FVector3f::ZeroVector;
	
	/// Set this flag to false if this body should never fall asleep.
    UPROPERTY(EditAnywhere,meta=(DisplayName="Should Sleep"),Category="𝘽𝙊𝙓3𝘿|RigidBody|Sleep")
    bool bEnableSleep = true;

    UPROPERTY(EditAnywhere,meta=(EditCondition="bEnableSleep", EditConditionHides),Category="𝘽𝙊𝙓3𝘿|RigidBody|Sleep")
    float SleepThreshold = 5.0f;
	
	/// Optional body name for debugging.
    UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|RigidBody|Misc")
    FName Name = NAME_None;
	
	/// Treat this body as a high speed object that performs continuous collision detection
	/// against dynamic and kinematic bodies, but not other bullet bodies.
	/// @warning Bullets should be used sparingly. They are not a solution for general dynamic-versus-dynamic
	/// continuous collision. They do not guarantee accurate collision if both bodies are fast moving because
	/// the bullet does a continuous check after all non-bullet bodies have moved. You could get unlucky and have
	/// the bullet body end a time step very close to a non-bullet body and the non-bullet body then moves over
	/// the bullet body. In continuous collision, initial overlap is ignored to avoid freezing bodies in place.
	/// I do not recommend using them for game projectiles if precise collision timing is needed. Instead consider
	/// using a ray or shape cast. You can use a marching ray or shape cast for projectile that moves over time.
	/// If you want a fast moving projectile to collide with a fast moving target, you need to consider the relative
	/// movement in your ray or shape cast. This is out of the scope of Box3D.
	/// So what are good use cases for bullets? Pinball games or games with dynamic containers that hold other objects.
	/// It should be a use case where it doesn't break the game if there is a collision missed, but having them
	/// captured improves the quality of the game.
    UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|RigidBody|Misc")
    bool bIsBullet = false;
	
	/// This allows this body to bypass rotational speed limits. Should only be used
	/// for circular objects, like wheels.
    UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|RigidBody|Misc")
    bool bAllowFastRotation = false;
	
	/// Enable contact recycling. True by default. Leaving this enabled improves performance
	/// but may lead to ghost collision that should be avoided on characters.
    UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|RigidBody|Misc")
    bool bEnableContactRecycling = true;
};

USTRUCT()
struct BOX3DWRAPPER_API FB3ShapeDef
{
	GENERATED_BODY()
	
	/// Use this to store application specific shape data.
    FB3ShapeUserData* UserData = nullptr;
	
	/// Should the body update the mass properties when this shape is created. Default is true.
	/// Warning: if this is false, you MUST call b3Body_ApplyMassFromShapes or b3Body_SetMassData before simulating the world.
	// UPROPERTY(EditAnywhere,meta=(DisplayName="Auto Mass") )
	bool bUpdateBodyMass = true;

    // UPROPERTY(EditAnywhere,meta = (ForceUnits = "kg", EditCondition="!bUpdateBodyMass", EditConditionHides))
    // float Mass = 1.0f;

    // UPROPERTY(EditAnywhere,meta = (EditCondition="!bUpdateBodyMass", EditConditionHides))
    // FVector CenterOfMass = FVector::ZeroVector;

	FName Name = NAME_None;

	/// Surface material used on mesh shapes per triangle. Ignored for convex shapes. Ignored for compound shapes.
    // b3SurfaceMaterial* materials;

	/// Surface material count.
    // int MaterialCount = 0;
	
	/// The base surface material. Ignored for compound shapes.
	UPROPERTY(EditAnywhere, meta=(ShowOnlyInnerProperties), Category="𝘽𝙊𝙓3𝘿|CollisionDef|PhysicsMaterial")
	FB3SurfaceMaterial BaseMaterial;
	
	/// Enable custom filtering. Only one of the two shapes needs to enable custom filtering. See b3WorldDef.
	bool bEnableCustomFiltering = false;
	/// A sensor shape generates overlap events but never generates a collision response.
	/// Sensors do not have continuous collision. Instead, use a ray or shape cast for those scenarios.
	/// Sensors still contribute to the body mass if they have non-zero density.
	/// @note Sensor events are disabled by default.
	/// @see enableSensorEvents
	UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
    bool bIsSensor = false;
	
	/// Enable sensor events for this shape. This applies to sensors and non-sensors. False by default, even for sensors.
	/// Only convex shapes may act as sensor visitors.
	UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
	bool bEnableSensorEvents = false;
	
	/// Enable contact events for this shape. Only applies to kinematic and dynamic bodies. Ignored for sensors. False by default.
	UPROPERTY(EditAnywhere,meta=(EditCondition="!bIsSensor", EditConditionHides),Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
	bool bEnableContactEvents = false;
	
	/// Enable hit events for this shape. Only applies to kinematic and dynamic bodies. Ignored for sensors. False by default.
	UPROPERTY(EditAnywhere,meta=(EditCondition="!bIsSensor", EditConditionHides),Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
	bool bEnableHitEvents = false;
	
	/// Enable pre-solve contact events for this shape. Only applies to dynamic bodies. These are expensive
	///	and must be carefully handled due to multithreading. Ignored for sensors.
	bool bEnablePreSolveEvents = false;
    
	UPROPERTY(EditAnywhere, meta=(ShowOnlyInnerProperties), Category="𝘽𝙊𝙓3𝘿|CollisionDef|Responses")
	FB3Filter Filter;

	/// When shapes are created they will scan the environment for collision the next time step. This can significantly slow down
	/// static body creation when there are many static shapes.
	/// This is flag is ignored for dynamic and kinematic shapes which always invoke contact creation.
	UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|CollisionDef|Misc")
	bool bInvokeContactCreation = true;

	/// Enable speculative collision. Leave this true unless you care about reducing ghost collision
	/// more than continuous collision under rotation.
	/// Experimental: this can only disable speculative contact between hulls and triangles (meshes and height fields).
	UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|CollisionDef|Misc")
	bool bEnableSpeculativeContact = true;
	
	/// Explosion scale for b3World_Explode. non-dimensional
	UPROPERTY(EditAnywhere,Category="𝘽𝙊𝙓3𝘿|CollisionDef|Misc")
	float ExplosionScale = 1.0;
	
	/// The density, in kg/m^3.
	UPROPERTY(EditAnywhere,meta = (ForceUnits = "kg/m3"),Category="𝘽𝙊𝙓3𝘿|CollisionDef|Misc")
    float Density = 1000.0f;
    
};

struct BOX3DWRAPPER_API FB3MeshDef
{
	/// Triangle vertices
	TArray<FVector3f> Vertices;

	/// Triangle vertex indices. 3 for each triangle. CCW winding.
	TArray<int32> TriangleIndices;

	/// Triangle material index. 1 per triangle. Indexes into b3ShapeDef::materials.
	/// This allows different run-time material data to be associated with different
	/// instances of this mesh.
	TArray<uint8> MaterialIndices;

	/// Tolerance for vertex welding in length units.
	float WeldTolerance = 0.0f;

	/// The vertex count. Must be 3 or more.
	int VertexCount = 0;

	/// The triangle count. Must be 1 or more.
	int TriangleCount = 0;

	/// Optionally weld nearby vertices.
	bool bWeldVertices = false;

	/// Use the median split instead of SAH to speed up mesh creation. Good
	/// for meshes that are structured like a grid.
	bool bUseMedianSplit = false;

	/// Compute triangle adjacency information using shared edges
	bool bIdentifyEdges = false;
    
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3JointDef
{
    GENERATED_BODY()

    /// User data pointer
    FB3JointUserData* UserData = nullptr;

	/// The first attached body
	FB3BodyHandle BodyHandleA;
    
	/// The second attached body
	FB3BodyHandle BodyHandleB;

	/// The first local joint frame
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef|Offset A")
	FVector3f LocationA = FVector3f::ZeroVector;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef|Offset A")
    FRotator3f RotationA = FRotator3f::ZeroRotator;
	/// The second local joint frame
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef|Offset B")
	FVector3f LocationB = FVector3f::ZeroVector;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef|Offset B")
    FRotator3f RotationB = FRotator3f::ZeroRotator;

	/// Set this flag to true if the attached bodies should collide
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef")
	bool bCollideConnected = false;

	/// Force threshold for joint events
	float ForceThreshold = FLT_MAX;

	/// Torque threshold for joint events
	float TorqueThreshold = FLT_MAX;

	/// Constraint hertz (advanced feature)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef")
	float ConstraintHertz = 60.0f;

	/// Constraint damping ratio (advanced feature)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef")
	float ConstraintDampingRatio = 2.0f;
    
	/// Debug draw scale
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointDef")
	float DrawScale = 100.0f;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3ShapeProxy
{
    GENERATED_BODY()
	
	/// The point cloud.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShapeProxy")
	TArray<FVector3f> Points = {FVector3f::ZeroVector};
	
	/// The external radius of the point cloud.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShapeProxy")
	float Radius = 0.0f;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3RayResult
{
    GENERATED_BODY()

	/// Did the ray hit? If false, all other data is invalid.
	UPROPERTY(BlueprintReadOnly, Category = "RayResult")
	bool bHit = false;

	/// The world point of the hit.
    UPROPERTY(BlueprintReadOnly, Category = "RayResult")
    FVector Point = FVector::ZeroVector;

	/// The world normal of the shape surface at the hit point.
    UPROPERTY(BlueprintReadOnly, Category = "RayResult")
    FVector3f Normal = FVector3f::UpVector;

	/// The fraction of the input ray.
    UPROPERTY(BlueprintReadOnly, Category = "RayResult")
    float Fraction = 0.0f;

	/// The shape Handle.
    UPROPERTY(BlueprintReadOnly, Category = "RayResult")
    FB3ShapeHandle ShapeHandle = FB3ShapeHandle(b3_nullShapeId);


	/// The user material id at the hit point. This can be per triangle
	/// if the shape is a mesh, height-field, or compound with child mesh.
    uint64 UserMaterialId = 0;

	/// The triangle index if the shape is a mesh, height-field, or compound with child mesh.
    UPROPERTY(BlueprintReadOnly, Category = "RayResult")
    int32 TriangleIndex = INDEX_NONE;

	/// The child index if the shape is a compound.
    UPROPERTY(BlueprintReadOnly, Category = "RayResult")
    int32 ChildIndex = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3ClosestPoint
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "ClosestPoint")
    FVector Point = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "ClosestPoint")
    float Distance = 0.0f;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3ExplosionDef
{
    GENERATED_BODY()

    
	/// The center of the explosion in world space
    UPROPERTY(BlueprintReadWrite, Category = "ExplosionDef")
	FVector Position = FVector::ZeroVector;
    
	/// The radius of the explosion
    UPROPERTY(BlueprintReadWrite, Category = "ExplosionDef")
	float Radius = 0.0f;;
    
	/// The falloff distance beyond the radius. Impulse is reduced to zero at this distance.
    UPROPERTY(BlueprintReadWrite, Category = "ExplosionDef")
	float Falloff = 0.0f;;
    
	/// Impulse per unit area. This applies an impulse according to the shape area that
	/// is facing the explosion. Explosions only apply to spheres, capsules, and hulls. This
	/// may be negative for implosions.
    UPROPERTY(BlueprintReadWrite, Category = "ExplosionDef")
	float ImpulsePerArea = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "ExplosionDef", meta=(Bitmask, BitmaskEnum="/Script/Box3DWrapper.EB3ObjectFlags"))
	int32 ObjectsToIgnore = 0;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3AABB
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AABB")
	FVector3f LowerBound = FVector3f::ZeroVector;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AABB")
	FVector3f UpperBound = FVector3f::ZeroVector;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3Profile
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Step = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Pairs = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Collide = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Solve = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float SolverSetup = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Constraints = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float PrepareConstraints = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float IntegrateVelocities = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float WarmStart = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float SolveImpulses = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float IntegratePositions = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float RelaxImpulses = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float ApplyRestitution = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float StoreImpulses = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float SplitIslands = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Transforms = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float SensorHits = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float JointEvents = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float HitEvents = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Refit = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Bullets = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float SleepIslands = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	float Sensors = 0;
};


USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3Counters
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 BodyCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 ShapeCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 ContactCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 JointCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 IslandCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 StackUsed = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 ArenaCapacity = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 StaticTreeHeight = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 TreeHeight = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 SatCallCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 SatCacheHitCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 ByteCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 TaskCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	TArray<int32> ColorCounts;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	TArray<int32> ManifoldCounts;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 AwakeContactCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 RecycledContactCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 DistanceIterations = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 PushBackIterations = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Counters")
	int32 RootIterations = 0;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3BodyMoveEvent
{
	GENERATED_BODY()
	
	/// The body user data.
    FB3BodyUserData* UserData = nullptr;
	
	/// The body transform.
	UPROPERTY(BlueprintReadOnly, Category="BodyMoveEvent")
	FTransform Transform = FTransform::Identity;
	
	/// The body Handle.
	UPROPERTY(BlueprintReadOnly, Category="BodyMoveEvent")
	FB3BodyHandle BodyHandle;
	
	/// Did the body fall asleep this time step?
	UPROPERTY(BlueprintReadOnly, Category="BodyMoveEvent")
	bool bFellAsleep = false;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3SensorTouchEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="SensorTouchEvent")
	FB3ShapeHandle SensorShapeHandle;
    
	UPROPERTY(BlueprintReadOnly, Category="SensorTouchEvent")
	FB3ShapeHandle VisitorShapeHandle;
};
struct BOX3DWRAPPER_API FB3BodyUserData
{
    FWeakObjectPtr Object = nullptr;
    void (*MoveCallback)(FB3BodyUserData* BodyUserData, UObject*, const FTransform&) = nullptr;
};
struct BOX3DWRAPPER_API FB3ShapeUserData
{
    FWeakObjectPtr Object = nullptr;
    void (*BeginOverlapCallback)(FB3ShapeUserData* ShapeUserData, UObject*,const FB3SensorTouchEvent&) = nullptr;
    void (*EndOverlapCallback)(FB3ShapeUserData* ShapeUserData, UObject*,const FB3SensorTouchEvent&) = nullptr;
};
struct BOX3DWRAPPER_API FB3JointUserData
{
    FWeakObjectPtr Object = nullptr;
    //will add callbacks here
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3Sphere
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
	FVector3f Center = FVector3f::ZeroVector;    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
	float Radius = 0;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3Capsule
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
	FVector3f Center1 = FVector3f::UpVector;    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
	FVector3f Center2 = -FVector3f::UpVector;    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
	float Radius = 0;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3DistanceJointDef
{
    GENERATED_BODY()
    
	/// The rest length of this joint. Clamped to a stable minimum value.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef")
	float Length = 200.0;
    
	/// Enable the distance constraint to behave like a spring. If false
	/// then the distance joint will be rigid, overriding the limit and motor.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef")
	bool bEnableSpring = false;

    /// The spring linear stiffness Hertz, cycles per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float Hertz = 5.0f;
    
	/// The spring linear damping ratio, non-dimensional
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float DampingRatio = 0.5f;
    
	/// The lower spring force controls how much tension it can sustain
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float LowerSpringForce = 2000.0f;
    
	/// The upper spring force controls how much compression it can sustain
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float UpperSpringForce = 100.0f;
    
	/// Enable/disable the joint limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef")
	bool bEnableLimit = false;
    
	/// Minimum length. Clamped to a stable minimum value.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableLimit", EditConditionHides))
	float MinLength = 0.0f;
    
	/// Maximum length. Must be greater than or equal to the minimum length.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableLimit", EditConditionHides))
	float MaxLength = 0.0f;
    
	/// Enable/disable the joint motor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef")
	bool bEnableMotor = false;
    
	/// The maximum motor force, usually in newtons
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	float MaxMotorForce = 0.0f;
    
	/// The desired motor speed, usually in meters per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	float MotorSpeed = 0.0f;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3MotorJointDef
{
    GENERATED_BODY()
	
	/// The desired linear velocity
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	FVector3f LinearVelocity = FVector3f::ZeroVector;
	
	/// The maximum motor force in newtons
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	FVector3f AngularVelocity = FVector3f::ZeroVector;
	
	/// The desired angular velocity
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float MaxVelocityForce = 0.0f;
	
	/// The maximum motor torque in newton-meters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float MaxVelocityTorque = 0.0f;
	
	/// Linear spring hertz for position control
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float LinearHertz = 0.0f;
	
	/// Linear spring damping ratio
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float LinearDampingRatio = 0.0f;
	
	/// Maximum spring force in newtons
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float MaxSpringForce = 0.0f;
	
	/// Angular spring hertz for position control
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float AngularHertz = 0.0f;
	
	/// Angular spring damping ratio
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float AngularDampingRatio = 0.0f;
	
	/// Maximum spring torque in newton-meters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotorJointDef")
	float MaxSpringTorque = 0.0f;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3ParallelJointDef
{
    GENERATED_BODY()
	
	/// The spring stiffness Hertz, cycles per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParallelJointDef")
	float Hertz = 1.0f;
	
	/// The spring damping ratio, non-dimensional
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParallelJointDef")
	float DampingRatio = 1.0f;
	
	/// The maximum spring torque, typically in newton-meters.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParallelJointDef")
	float MaxTorque = 0.0f;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3PrismaticJointDef
{
    GENERATED_BODY()
	
	/// Enable a linear spring along the prismatic joint axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef")
	bool bEnableSpring = false;
	
	/// The spring stiffness Hertz, cycles per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float Hertz = 5.0f;
	
	/// The spring damping ratio, non-dimensional
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float DampingRatio = 0.5f;
	
	/// The spring damping ratio, non-dimensional
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef")
	float TargetTranslation = 0.0f;
	
    /// Enable/disable the joint limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef")
	bool bEnableLimit = false;
	
	/// The lower translation limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef",meta=(EditCondition="bEnableLimit", EditConditionHides))
	float LowerTranslation = 0.0f;
	
	/// The upper translation limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef",meta=(EditCondition="bEnableLimit", EditConditionHides))
	float UpperTranslation = 0.0f;
	
    /// Enable/disable the joint motor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef")
	bool bEnableMotor = false;
	
	/// The maximum motor force, usually in newtons
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	float MaxMotorForce = 0.0f;
	
	/// The desired motor speed, usually in meters per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrismaticJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	float MotorSpeed = 0.0f;

};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3RevoluteJointDef
{
    GENERATED_BODY()
	
	/// The bodyB angle minus bodyA angle in the reference state (radians).
	/// This defines the zero angle for the joint limit.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef")
	float TargetAngle = 0.0f;
	
	/// Enable a rotational spring on the revolute hinge axis.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef")
	bool bEnableSpring = false;
	
	/// The spring stiffness Hertz, cycles per second.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float Hertz = 5.0f;
	
	/// The spring damping ratio, non-dimensional.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float DampingRatio = 0.5f;
	
	/// A flag to enable joint limits.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef")
	bool bEnableLimit = false;
	
    /// The lower angle for the joint limit in radians. Minimum of -0.99*pi radians.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef",meta=(EditCondition="bEnableLimit", EditConditionHides))
	float LowerAngle = 0.0f;
	
	/// The upper angle for the joint limit in radians. Maximum of 0.99*pi radians.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef",meta=(EditCondition="bEnableLimit", EditConditionHides))
	float UpperAngle = 0.0f;
	
	/// A flag to enable the joint motor.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef")
	bool bEnableMotor = false;
	
	/// The maximum motor torque, typically in newton-meters.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	float MaxMotorTorque = 0.0f;
	
	/// The desired motor speed in radians per second.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevoluteJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	float MotorSpeed = 0.0f;

};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3SphericalJointDef
{
    GENERATED_BODY()
	
	/// Enable a rotational spring that attempts to align the two joint frames.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef")
	bool bEnableSpring = false;
	
	/// The spring stiffness Hertz, cycles per second. This may be clamped internally
	/// according to the time step to maintain stability. Non-negative number.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float Hertz = 5.0f;
	
	/// The spring damping ratio, non-dimensional. Non-negative number.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	float DampingRatio = 0.5f;
	
	/// Target spring rotation, joint frame B relative to joint frame A.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableSpring", EditConditionHides))
	FQuat TargetRotation = FQuat::Identity;
	
	/// A flag to enable the cone limit. The cone is centered on the frameA z-axis.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef")
	bool bEnableConeLimit = false;
	
	/// The angle for the cone limit in radians. Valid range is [0, pi]
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableConeLimit", EditConditionHides))
	float ConeAngle = 0.0f;
	
	/// A flag to enable the twist limit. The twist is centered on the frameB z-axis.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableConeLimit", EditConditionHides))
	bool bEnableTwistLimit = false;
	
	/// The angle for the lower twist limit in radians. Minimum of -0.99*pi radians.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableTwistLimit", EditConditionHides))
	float LowerTwistAngle = 0.0f;
	
	/// The angle for the upper twist limit in radians. Maximum of 0.99*pi radians.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableTwistLimit", EditConditionHides))
	float UpperTwistAngle = 0.0f;
	
	/// A flag to enable the joint motor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef")
	bool bEnableMotor = false;
	
	/// The maximum motor torque, typically in newton-meters. Non-negative number.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	float MaxMotorTorque = 0.0f;
	
	/// The desired motor angular velocity in radians per second.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphericalJointDef",meta=(EditCondition="bEnableMotor", EditConditionHides))
	FVector3f MotorVelocity = FVector3f::ZeroVector;
};
USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3WeldJointDef
{
    GENERATED_BODY()

	
	/// Linear stiffness expressed as Hertz (cycles per second). Use zero for maximum stiffness.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeldJointDef")
	float LinearHertz = 0.0f;
	
	/// Angular stiffness as Hertz (cycles per second). Use zero for maximum stiffness.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeldJointDef")
	float AngularHertz = 0.0f;
	
	/// Linear damping ratio, non-dimensional. Use 1 for critical damping.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeldJointDef")
	float LinearDampingRatio = 0.0f;
	
	
	/// Linear damping ratio, non-dimensional. Use 1 for critical damping.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeldJointDef")
	float AngularDampingRatio = 0.0f;
};

USTRUCT(BlueprintType)
struct BOX3DWRAPPER_API FB3WheelJointDef
{
    GENERATED_BODY()

	/// Enable a linear spring along the local axis
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef")
    bool bEnableSuspensionSpring = false;

	/// Spring stiffness in Hertz
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSuspensionSpring", EditConditionHides))
    float SuspensionHertz = 0.0f;

	/// Spring damping ratio, non-dimensional
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSuspensionSpring", EditConditionHides))
    float SuspensionDampingRatio = 0.0f;

	/// Enable/disable the joint linear limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef")
    bool bEnableSuspensionLimit = false;

	/// The lower suspension translation limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSuspensionLimit", EditConditionHides))
    float LowerSuspensionLimit = 0.0f;

	/// The upper translation limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSuspensionLimit", EditConditionHides))
    float UpperSuspensionLimit = 0.0f;

	/// Enable/disable the joint rotational motor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef")
    bool bEnableSpinMotor = false;

	/// The maximum motor torque, typically in newton-meters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSpinMotor", EditConditionHides))
    float MaxSpinTorque = 0.0f;

	/// The desired motor speed in radians per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSpinMotor", EditConditionHides))
    float SpinSpeed = 0.0f;

	/// Enable steering, otherwise the steering is fixed forward
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef")
    bool bEnableSteering = false;

	/// Steering stiffness in Hertz
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSteering", EditConditionHides))
    float SteeringHertz = 0.0f;

	/// Spring damping ratio, non-dimensional
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSteering", EditConditionHides))
    float SteeringDampingRatio = 0.0f;

	/// The target steering angle in radians
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSteering", EditConditionHides))
    float TargetSteeringAngle = 0.0f;

	/// The maximum steering torque in N*m
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSteering", EditConditionHides))
    float MaxSteeringTorque = 0.0f;

	/// Enable/disable the steering angular limit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef")
    bool bEnableSteeringLimit = false;

	/// The lower steering angle in radians
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSteeringLimit", EditConditionHides))
    float LowerSteeringLimit = 0.0f;

	/// The upper steering angle in radians
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelJointDef",meta=(EditCondition="bEnableSteeringLimit", EditConditionHides))
    float UpperSteeringLimit = 0.0f;
};



















FORCEINLINE b3AABB ToNative(const FB3AABB& BoundingBox){return b3AABB{ToNativeVec(BoundingBox.LowerBound),ToNativeVec(BoundingBox.UpperBound)};}
FORCEINLINE FB3AABB ToUnreal(const b3AABB& BoundingBox){return FB3AABB{ToUnreal(BoundingBox.lowerBound),ToUnreal(BoundingBox.upperBound)};}
FORCEINLINE b3Sphere ToNative( const FB3Sphere& Sphere){return {ToNativeVec(Sphere.Center),Sphere.Radius};}
FORCEINLINE b3Capsule ToNative( const FB3Capsule& Capsule){return {ToNativeVec(Capsule.Center1),ToNativeVec(Capsule.Center2),Capsule.Radius};}
FORCEINLINE FB3Sphere ToUnreal( const b3Sphere& Sphere){return {ToUnreal(Sphere.center),Sphere.radius};}
FORCEINLINE FB3Capsule ToUnreal( const b3Capsule& Capsule){return {ToUnreal(Capsule.center1),ToUnreal(Capsule.center2),Capsule.radius};}
FORCEINLINE FB3Filter ToUnreal(const b3Filter& Filter)
{
	FB3Filter Result;
	Result.ObjectType      = static_cast<int32>(Filter.categoryBits);
	Result.ObjectsToIgnore = ~static_cast<int32>(Filter.maskBits);
	Result.TracesToIgnore  = ~static_cast<int32>(Filter.maskBits >> 32);
	Result.GroupIndex      = Filter.groupIndex;
	return Result;
}
FORCEINLINE b3Filter ToNative( const FB3Filter& Filter)
{
    b3Filter Result;
    Result.categoryBits = static_cast<uint64>(Filter.ObjectType);
    Result.maskBits     = ~((static_cast<uint64_t>(Filter.TracesToIgnore) << 32) | static_cast<uint64_t>(Filter.ObjectsToIgnore));
    Result.groupIndex   = Filter.GroupIndex;
    return Result;
}
FORCEINLINE float CalculateRubbing(EB3CombineMode CombineMode, float A, float B)
{
	switch(CombineMode) 
    {
		case EB3CombineMode::Average         : return (A + B) * 0.5f;
		case EB3CombineMode::Min             : return FMath::Min(A, B);
		case EB3CombineMode::Multiply        : return (A * B);
		case EB3CombineMode::MultiplyThenSqrt: return FMath::Sqrt(A * B);
		case EB3CombineMode::Max             : return FMath::Max(A, B);
		case EB3CombineMode::Harmonic        : return (A + B) != 0 ? (2 * A * B) / (A + B) : 0;
		default                              : return FMath::Sqrt(A * B);
	}
}
FORCEINLINE b3MassData ToNative( const FB3MassData& MassData)
{
    b3MassData Result{};
    Result.mass = MassData.Mass;
    Result.center = ToNativeVec(MassData.CenterOfMass);
    Result.inertia = ToNative(MassData.Inertia3x3);
    return Result;
}
FORCEINLINE FB3MassData ToUnreal( const b3MassData& MassData)
{
    FB3MassData Result{};
    Result.Mass = MassData.mass;
    Result.CenterOfMass = ToUnreal(MassData.center);
    Result.Inertia3x3 = ToUnreal(MassData.inertia);
    return Result;
}
FORCEINLINE b3ShapeProxy ToNative(const FB3ShapeProxy& Proxy)
{
    b3ShapeProxy Result;
    Result.points = reinterpret_cast<const b3Vec3*>(Proxy.Points.GetData());
    Result.count = Proxy.Points.Num();
    Result.radius = Proxy.Radius;
    return Result;
}
FORCEINLINE b3MotionLocks ToNative(const FB3MotionLocks MotionLocks)
{
    b3MotionLocks Result{};
    Result.linearX = MotionLocks.bLockLinearX;
    Result.linearY = MotionLocks.bLockLinearY;
    Result.linearZ = MotionLocks.bLockLinearZ;
    Result.angularX = MotionLocks.bLockAngularX;
    Result.angularY = MotionLocks.bLockAngularY;
    Result.angularZ = MotionLocks.bLockAngularZ;
    return Result;
}
FORCEINLINE FB3MotionLocks ToUnreal(const b3MotionLocks MotionLocks)
{
    FB3MotionLocks Result;
    Result.bLockLinearX = MotionLocks.linearX;
    Result.bLockLinearY = MotionLocks.linearY;
    Result.bLockLinearZ = MotionLocks.linearZ;
    Result.bLockAngularX = MotionLocks.angularX;
    Result.bLockAngularY = MotionLocks.angularY;
    Result.bLockAngularZ = MotionLocks.angularZ;
    return Result;
}
FORCEINLINE FB3RayResult ToUnreal(const b3RayResult& RayResult)
{
    FB3RayResult Result;
    Result.bHit = RayResult.hit;
    Result.Point = ToUnreal(RayResult.point);
    Result.Normal = ToUnreal(RayResult.normal);
    Result.Fraction = RayResult.fraction;
    Result.ShapeHandle = FB3ShapeHandle(RayResult.shapeId);
    Result.UserMaterialId = static_cast<int64>(RayResult.userMaterialId);
    Result.TriangleIndex = RayResult.triangleIndex;
    Result.ChildIndex = RayResult.childIndex;
    return Result;
}
FORCEINLINE FB3BodyMoveEvent ToUnreal(const b3BodyMoveEvent& BodyMoveEvent)
{
    return FB3BodyMoveEvent{
        static_cast<FB3BodyUserData*>(BodyMoveEvent.userData),
        ToUnreal(BodyMoveEvent.transform),
        FB3BodyHandle(BodyMoveEvent.bodyId),
        BodyMoveEvent.fellAsleep};
}
FORCEINLINE FB3SensorTouchEvent ToUnreal(const b3SensorBeginTouchEvent& SensorBeginTouchEvent)
{
    return FB3SensorTouchEvent{ FB3ShapeHandle(SensorBeginTouchEvent.sensorShapeId), FB3ShapeHandle(SensorBeginTouchEvent.visitorShapeId)};
}
FORCEINLINE FB3SensorTouchEvent ToUnreal(const b3SensorEndTouchEvent& SensorEndTouchEvent)
{
    return FB3SensorTouchEvent{ FB3ShapeHandle(SensorEndTouchEvent.sensorShapeId), FB3ShapeHandle(SensorEndTouchEvent.visitorShapeId)};
}
FORCEINLINE FB3Profile ToUnreal( const b3Profile& Profile)
{
    FB3Profile Result{};
	Result.Step = Profile.step;
	Result.Pairs = Profile.pairs;
	Result.Collide = Profile.collide;
	Result.Solve = Profile.solve;
	Result.SolverSetup = Profile.solverSetup;
	Result.Constraints = Profile.constraints;
	Result.PrepareConstraints = Profile.prepareConstraints;
	Result.IntegrateVelocities = Profile.integrateVelocities;
	Result.WarmStart = Profile.warmStart;
	Result.SolveImpulses = Profile.solveImpulses;
	Result.IntegratePositions = Profile.integratePositions;
	Result.RelaxImpulses = Profile.relaxImpulses;
	Result.ApplyRestitution = Profile.applyRestitution;
	Result.StoreImpulses = Profile.storeImpulses;
	Result.SplitIslands = Profile.splitIslands;
	Result.Transforms = Profile.transforms;
	Result.SensorHits = Profile.sensorHits;
	Result.JointEvents = Profile.jointEvents;
	Result.HitEvents = Profile.hitEvents;
	Result.Refit = Profile.refit;
	Result.Bullets = Profile.bullets;
	Result.SleepIslands = Profile.sleepIslands;
	Result.Sensors = Profile.sensors;
    return Result;
}
FORCEINLINE FB3Counters ToUnreal(const b3Counters& Counters)
{
    FB3Counters Result{};
    Result.BodyCount = Counters.bodyCount;
    Result.ShapeCount = Counters.shapeCount;
    Result.ContactCount = Counters.contactCount;
    Result.JointCount = Counters.jointCount;
    Result.IslandCount = Counters.islandCount;
    Result.StackUsed = Counters.stackUsed;
    Result.ArenaCapacity = Counters.arenaCapacity;
    Result.StaticTreeHeight = Counters.staticTreeHeight;
    Result.TreeHeight = Counters.treeHeight;
    Result.SatCallCount = Counters.satCallCount;
    Result.SatCacheHitCount = Counters.satCacheHitCount;
    Result.ByteCount = Counters.byteCount;
    Result.TaskCount = Counters.taskCount;
    Result.AwakeContactCount = Counters.awakeContactCount;
    Result.RecycledContactCount = Counters.recycledContactCount;
    Result.DistanceIterations = Counters.distanceIterations;
    Result.PushBackIterations = Counters.pushBackIterations;
    Result.RootIterations = Counters.rootIterations;
    Result.ColorCounts.Append(Counters.colorCounts, 24);
    Result.ManifoldCounts.Append(Counters.manifoldCounts, B3_CONTACT_MANIFOLD_COUNT_BUCKETS);
    return Result;
}
FORCEINLINE b3Capacity ToNative(const FB3Capacity& Capacity)
{
    b3Capacity Result{};
    Result.staticShapeCount = Capacity.StaticShapeCount;
    Result.dynamicShapeCount = Capacity.DynamicShapeCount;
    Result.staticBodyCount = Capacity.StaticBodyCount;
    Result.dynamicBodyCount = Capacity.DynamicBodyCount;
    Result.contactCount = Capacity.ContactCount;
    return Result;
}
FORCEINLINE FB3Capacity ToUnreal(const b3Capacity& Capacity)
{
    FB3Capacity Result;
    Result.StaticShapeCount = Capacity.staticShapeCount;
    Result.DynamicShapeCount = Capacity.dynamicShapeCount;
    Result.StaticBodyCount = Capacity.staticBodyCount;
    Result.DynamicBodyCount = Capacity.dynamicBodyCount;
    Result.ContactCount = Capacity.contactCount;
    return Result;
}
FORCEINLINE b3SurfaceMaterial ToNative( const FB3SurfaceMaterial& SurfaceMaterial)
{
    b3SurfaceMaterial Result{};
	Result.friction = SurfaceMaterial.Friction;
	Result.restitution = SurfaceMaterial.Restitution;
	Result.rollingResistance = SurfaceMaterial.RollingResistance;
	Result.tangentVelocity = ToNativeVec(SurfaceMaterial.TangentVelocity);
	Result.userMaterialId =  (static_cast<uint64_t>(SurfaceMaterial.FrictionCombineMode) << 32) | static_cast<uint64_t>(SurfaceMaterial.RestitutionCombineMode);
    return Result;
}
FORCEINLINE FB3SurfaceMaterial ToUnreal( const b3SurfaceMaterial& SurfaceMaterial)
{
    FB3SurfaceMaterial Result{};
	Result.Friction = SurfaceMaterial.friction;
	Result.Restitution = SurfaceMaterial.restitution;
	Result.RollingResistance = SurfaceMaterial.rollingResistance;
	Result.TangentVelocity = ToUnreal(SurfaceMaterial.tangentVelocity);
    Result.FrictionCombineMode = static_cast<EB3CombineMode>(SurfaceMaterial.userMaterialId >> 32);
    Result.RestitutionCombineMode = static_cast<EB3CombineMode>(SurfaceMaterial.userMaterialId);
    return Result;
}





// ///////////////////////
// ///////////////////////
// ///---Definitions---///
// ///////////////////////
// ///////////////////////
FORCEINLINE b3ExplosionDef ToNative( const FB3ExplosionDef& ExplosionDef)
{
    b3ExplosionDef Result{};
    Result.maskBits = ~static_cast<uint64_t>(ExplosionDef.ObjectsToIgnore);
    Result.position = ToNativePos(ExplosionDef.Position);
    Result.radius = ExplosionDef.Radius;
    Result.falloff = ExplosionDef.Falloff;
    Result.impulsePerArea = ExplosionDef.ImpulsePerArea;
    return Result;
}
FORCEINLINE b3MeshDef ToNative( FB3MeshDef& MeshDef)
{
    b3MeshDef Result{};
    Result.vertices = reinterpret_cast<b3Vec3*>(MeshDef.Vertices.GetData());
	Result.stride = 0;
    Result.indices = MeshDef.TriangleIndices.GetData();
    Result.materialIndices = MeshDef.MaterialIndices.GetData();
    Result.weldTolerance = MeshDef.WeldTolerance;
    Result.vertexCount = MeshDef.VertexCount;
    Result.triangleCount = MeshDef.TriangleCount;
    Result.weldVertices = MeshDef.bWeldVertices;
    Result.useMedianSplit = MeshDef.bUseMedianSplit;
    Result.identifyEdges = MeshDef.bIdentifyEdges;
    return Result;
}
FORCEINLINE b3WorldDef ToNative(const FB3WorldDef WorldDef)
{
	b3WorldDef Result{};
	Result.gravity              = ToNativeVec(WorldDef.Gravity);
	Result.restitutionThreshold = WorldDef.RestitutionThreshold;
	Result.hitEventThreshold    = WorldDef.HitEventThreshold;
	Result.contactHertz         = WorldDef.ContactHertz;
	Result.contactDampingRatio  = WorldDef.ContactDampingRatio;
	Result.contactSpeed         = WorldDef.ContactSpeed;
	Result.maximumLinearSpeed   = WorldDef.MaximumLinearSpeed;
	Result.enableSleep          = WorldDef.bEnableSleep;
	Result.enableContinuous     = WorldDef.bEnableContinuous;
	Result.workerCount          = WorldDef.bAutoWorkers ? FPlatformMisc::NumberOfCores() : WorldDef.WorkerCount;
	Result.capacity             = ToNative(WorldDef.Capacity);
	Result.internalValue        = B3_SECRET_COOKIE;
	return Result;
}
FORCEINLINE b3BodyDef ToNative(const FB3BodyDef BodyDef)
{
    b3BodyDef Result{};
    Result.userData = BodyDef.UserData;
    Result.type = ToNative(BodyDef.Type);

    Result.position = ToNativePos(BodyDef.Position);
    Result.rotation = ToNative(BodyDef.Rotation);
    Result.linearVelocity =ToNativeVec(BodyDef.LinearVelocity);
    Result.angularVelocity = ToNativeVec(BodyDef.AngularVelocity);
    Result.linearDamping = BodyDef.LinearDamping;
    Result.angularDamping = BodyDef.AngularDamping;
    Result.gravityScale = BodyDef.GravityScale;
    Result.sleepThreshold = BodyDef.SleepThreshold;
    Result.name = nullptr; // This value is changed in B3Inside_CreateBody()
    Result.motionLocks = ToNative(BodyDef.MotionLocks);
    Result.enableSleep = BodyDef.bEnableSleep;
    Result.isAwake = BodyDef.bIsAwake;
    Result.isBullet = BodyDef.bIsBullet;
    Result.isEnabled = BodyDef.bIsEnabled;
    Result.allowFastRotation = BodyDef.bAllowFastRotation;
    Result.enableContactRecycling = BodyDef.bEnableContactRecycling;
    Result.internalValue = B3_SECRET_COOKIE;
    return Result;
}
FORCEINLINE b3ShapeDef ToNative( const FB3ShapeDef ShapeDef)
{
    b3ShapeDef Result{};
    Result.userData = ShapeDef.UserData;
    Result.baseMaterial = ToNative(ShapeDef.BaseMaterial);
    Result.density = ShapeDef.Density;
    Result.explosionScale = ShapeDef.ExplosionScale;
    Result.enableCustomFiltering = ShapeDef.bEnableCustomFiltering;
    Result.isSensor = ShapeDef.bIsSensor;
    Result.enableSensorEvents = ShapeDef.bEnableSensorEvents;
    Result.enableContactEvents = ShapeDef.bEnableContactEvents;
    Result.enableHitEvents = ShapeDef.bEnableHitEvents;
    Result.enablePreSolveEvents = ShapeDef.bEnablePreSolveEvents;
    Result.invokeContactCreation = ShapeDef.bInvokeContactCreation;
    Result.updateBodyMass = ShapeDef.bUpdateBodyMass;
    Result.enableSpeculativeContact = ShapeDef.bEnableSpeculativeContact;
    Result.filter = ToNative(ShapeDef.Filter);
    Result.name = nullptr; // This value is changed in B3Inside_CreateBody()
    Result.internalValue = B3_SECRET_COOKIE;
    return Result;
}
FORCEINLINE b3JointDef ToNative( const FB3JointDef JointDef)
{
    b3JointDef Result{};
    Result.userData = JointDef.UserData;
    Result.bodyIdA = JointDef.BodyHandleA.GetID();
    Result.bodyIdB = JointDef.BodyHandleB.GetID();
    Result.localFrameA = ToNativeTransform(FTransform3f(JointDef.RotationA,JointDef.LocationA));
    Result.localFrameB = ToNativeTransform(FTransform3f(JointDef.RotationB,JointDef.LocationB));
    Result.forceThreshold = JointDef.ForceThreshold;
    Result.torqueThreshold = JointDef.TorqueThreshold;
    Result.constraintHertz = JointDef.ConstraintHertz;
    Result.constraintDampingRatio = JointDef.ConstraintDampingRatio;
    Result.collideConnected = JointDef.bCollideConnected;
    Result.drawScale = JointDef.DrawScale;
    Result.internalValue = B3_SECRET_COOKIE;
    return Result;
}
FORCEINLINE b3DistanceJointDef ToNative( const FB3DistanceJointDef& DistanceJointDef)
{
	b3DistanceJointDef Result;
	Result.length = DistanceJointDef.Length;
	Result.enableSpring = DistanceJointDef.bEnableSpring;
	Result.lowerSpringForce = DistanceJointDef.LowerSpringForce;
	Result.upperSpringForce = DistanceJointDef.UpperSpringForce;
	Result.hertz = DistanceJointDef.Hertz;
	Result.dampingRatio = DistanceJointDef.DampingRatio;
	Result.enableLimit = DistanceJointDef.bEnableLimit;
	Result.minLength = DistanceJointDef.MinLength;
	Result.maxLength = DistanceJointDef.MaxLength;
	Result.enableMotor = DistanceJointDef.bEnableMotor;
	Result.maxMotorForce = DistanceJointDef.MaxMotorForce;
	Result.motorSpeed = DistanceJointDef.MotorSpeed;
    return Result;
}
FORCEINLINE b3SphericalJointDef ToNative( const FB3SphericalJointDef& SphericalJointDef)
{
	b3SphericalJointDef Result;
	Result.enableSpring = SphericalJointDef.bEnableSpring;
	Result.hertz = SphericalJointDef.Hertz;
	Result.dampingRatio = SphericalJointDef.DampingRatio;
	Result.targetRotation = ToNative(SphericalJointDef.TargetRotation);
	Result.enableConeLimit = SphericalJointDef.bEnableConeLimit;
	Result.coneAngle = SphericalJointDef.ConeAngle;
	Result.enableTwistLimit = SphericalJointDef.bEnableTwistLimit;
	Result.lowerTwistAngle = SphericalJointDef.LowerTwistAngle;
	Result.upperTwistAngle = SphericalJointDef.UpperTwistAngle;
	Result.enableMotor = SphericalJointDef.bEnableMotor;
	Result.maxMotorTorque = SphericalJointDef.MaxMotorTorque;
	Result.motorVelocity = ToNativeVec(SphericalJointDef.MotorVelocity);
    return Result;
}
FORCEINLINE b3MotorJointDef ToNative( const FB3MotorJointDef& MotorJointDef)
{
	b3MotorJointDef Result;
	Result.linearVelocity = ToNativeVec(MotorJointDef.LinearVelocity);
	Result.maxVelocityForce = MotorJointDef.MaxVelocityForce;
	Result.angularVelocity = ToNativeVec(MotorJointDef.AngularVelocity);
	Result.maxVelocityTorque = MotorJointDef.MaxVelocityTorque;
	Result.linearHertz = MotorJointDef.LinearHertz;
	Result.linearDampingRatio = MotorJointDef.LinearDampingRatio;
	Result.maxSpringForce = MotorJointDef.MaxSpringForce;
	Result.angularHertz = MotorJointDef.AngularHertz;
	Result.angularDampingRatio = MotorJointDef.AngularDampingRatio;
	Result.maxSpringTorque = MotorJointDef.MaxSpringTorque;
    return Result;
}
FORCEINLINE b3ParallelJointDef ToNative( const FB3ParallelJointDef& ParallelJointDef)
{
	b3ParallelJointDef Result;
    Result.hertz = ParallelJointDef.Hertz;
    Result.dampingRatio = ParallelJointDef.DampingRatio;
    Result.maxTorque = ParallelJointDef.MaxTorque;
    return Result;
}
FORCEINLINE b3RevoluteJointDef ToNative( const FB3RevoluteJointDef& RevoluteJointDef)
{
	b3RevoluteJointDef Result;
    Result.targetAngle = RevoluteJointDef.TargetAngle;
	Result.enableSpring = RevoluteJointDef.bEnableSpring;
	Result.hertz = RevoluteJointDef.Hertz;
	Result.dampingRatio = RevoluteJointDef.DampingRatio;
	Result.enableLimit = RevoluteJointDef.bEnableLimit;
	Result.lowerAngle = RevoluteJointDef.LowerAngle;
	Result.upperAngle = RevoluteJointDef.UpperAngle;
	Result.enableMotor = RevoluteJointDef.bEnableMotor;
	Result.maxMotorTorque = RevoluteJointDef.MaxMotorTorque;
	Result.motorSpeed = RevoluteJointDef.MotorSpeed;
    return Result;
}
FORCEINLINE b3WeldJointDef ToNative( const FB3WeldJointDef& WeldJointDef)
{
	b3WeldJointDef Result;
    Result.linearHertz = WeldJointDef.LinearHertz;
    Result.angularHertz = WeldJointDef.AngularHertz;
    Result.linearDampingRatio = WeldJointDef.LinearDampingRatio;
    Result.angularDampingRatio = WeldJointDef.AngularDampingRatio;
    return Result;
}
FORCEINLINE b3WheelJointDef ToNative( const FB3WheelJointDef& WheelJointDef)
{
	b3WheelJointDef Result;
	Result.enableSuspensionSpring = WheelJointDef.bEnableSuspensionSpring;
	Result.suspensionHertz = WheelJointDef.SuspensionHertz;
	Result.suspensionDampingRatio = WheelJointDef.SuspensionDampingRatio;
	Result.enableSuspensionLimit = WheelJointDef.bEnableSuspensionLimit;
	Result.lowerSuspensionLimit = WheelJointDef.LowerSuspensionLimit;
	Result.upperSuspensionLimit = WheelJointDef.UpperSuspensionLimit;
	Result.enableSpinMotor = WheelJointDef.bEnableSpinMotor;
	Result.maxSpinTorque = WheelJointDef.MaxSpinTorque;
	Result.spinSpeed = WheelJointDef.SpinSpeed;
	Result.enableSteering = WheelJointDef.bEnableSteering;
	Result.steeringHertz = WheelJointDef.SteeringHertz;
	Result.steeringDampingRatio = WheelJointDef.SteeringDampingRatio;
	Result.targetSteeringAngle = WheelJointDef.TargetSteeringAngle;
	Result.maxSteeringTorque = WheelJointDef.MaxSteeringTorque;
	Result.enableSteeringLimit = WheelJointDef.bEnableSteeringLimit;
	Result.lowerSteeringLimit = WheelJointDef.LowerSteeringLimit;
	Result.upperSteeringLimit = WheelJointDef.UpperSteeringLimit;
    return Result;
}
FORCEINLINE b3PrismaticJointDef ToNative( const FB3PrismaticJointDef& PrismaticJointDef)
{
	b3PrismaticJointDef Result;	
	Result.enableSpring = PrismaticJointDef.bEnableSpring;
	Result.hertz = PrismaticJointDef.Hertz;
	Result.dampingRatio = PrismaticJointDef.DampingRatio;
	Result.targetTranslation = PrismaticJointDef.TargetTranslation;
	Result.enableLimit = PrismaticJointDef.bEnableLimit;
	Result.lowerTranslation = PrismaticJointDef.LowerTranslation;
	Result.upperTranslation = PrismaticJointDef.UpperTranslation;
	Result.enableMotor = PrismaticJointDef.bEnableMotor;
	Result.maxMotorForce = PrismaticJointDef.MaxMotorForce;
	Result.motorSpeed = PrismaticJointDef.MotorSpeed;
    return Result;
}