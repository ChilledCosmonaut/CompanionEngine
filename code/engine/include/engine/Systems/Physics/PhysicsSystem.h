#pragma once

#include "PxPhysicsAPI.h"
#include <stdexcept>

#include "engine/Time.h"
#include "engine/Systems/Physics/Components/Rigidbody.h"
#include "engine/Scene.h"
#include "../../../../src/ECS/CoreSystem.h"

namespace gl3::engine::Physics {

    class PhysicsSystem : Ecs::CoreSystem {
    public:
        static PhysicsSystem *GetPhysicsSystem(){
            if (physicsSystem == nullptr)
                physicsSystem = new PhysicsSystem();
            return physicsSystem;
        }

        void SetUp();

        void Update();

        void Shutdown();

    private:

        PhysicsSystem();

        ~PhysicsSystem()  override;

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
