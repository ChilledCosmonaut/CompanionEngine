#pragma once

#include "PxConfig.h" //Needs to stay here else PhysX won't find some HeaderFiles
#include "PxPhysicsAPI.h"
#include <stdexcept>

#include "engine/Time.h"
#include "engine/Systems/Physics/Components/RigidBody.h"
#include "engine/Scene.h"
#include "../../ECS/CoreSystem.h"

namespace gl3::engine::Physics {

    class PhysicsSystem : Ecs::CoreSystem {
    public:
        /// Need to adhere to the singleton pattern
        static PhysicsSystem *GetPhysicsSystem();

        /// Need to adhere to the singleton pattern
        static void DestroyPhysicsSystem();

        void SetUp();

        void Update();

        void Shutdown();

    private:

        PhysicsSystem();

        ~PhysicsSystem()  override;

        physx::PxShape* CreateShape(Shapes::Sphere& sphere, physx::PxMaterial* material);
        physx::PxShape* CreateShape(Shapes::Box& box, physx::PxMaterial* material);
        physx::PxShape* CreateShape(Shapes::Capsule& capsule, physx::PxMaterial* material);
        physx::PxShape* CreateShape(Shapes::Plane& plane, physx::PxMaterial* material);

        inline static PhysicsSystem *physicsSystem = nullptr;

        physx::PxDefaultAllocator      mDefaultAllocatorCallback;
        physx::PxDefaultErrorCallback  mDefaultErrorCallback;
        physx::PxDefaultCpuDispatcher* mDispatcher = nullptr;
        physx::PxTolerancesScale       mToleranceScale;

        physx::PxFoundation*           mFoundation = nullptr;
        physx::PxPhysics*              mPhysics = nullptr;

        physx::PxScene*                mScene = nullptr;

        physx::PxPvd*                  mPvd = nullptr;
        physx::PxPvdTransport*         mPvdTransporter = nullptr;
    };
}
