#pragma once

#include "PxConfig.h" //Needs to stay here else PhysX won't find some HeaderFiles
#include "PxPhysicsAPI.h"
#include <stdexcept>

#include "engine/Time.h"
#include "engine/Systems/Physics/Components/RigidBody.h"
#include "engine/Scene.h"
#include "engine/Systems/Physics/Components/TriggerEvents.h"

#include "../../ECS/CoreSystem.h"

namespace gl3::engine::Physics {

    class PhysicsSystem : Ecs::CoreSystem, public physx::PxSimulationEventCallback {
        friend class PhysicsUtils;
    public:
        /// Need to adhere to the singleton pattern
        static PhysicsSystem *GetPhysicsSystem();

        /// Need to adhere to the singleton pattern
        static void DestroyPhysicsSystem();

        void SetUp();

        void Update();

        void Shutdown();

        void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override {};
        void onWake(physx::PxActor** actors, physx::PxU32 count) override {};
        void onSleep(physx::PxActor** actors, physx::PxU32 count) override {};
        void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override {};
        void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
        void onAdvance(const physx::PxRigidBody*const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override {};

    private:

        PhysicsSystem();

        ~PhysicsSystem()  override;

        physx::PxShape* CreateShape(Shapes::Sphere& sphere, physx::PxMaterial* material);
        physx::PxShape* CreateShape(Shapes::Box& box, physx::PxMaterial* material);
        physx::PxShape* CreateShape(Shapes::Capsule& capsule, physx::PxMaterial* material);

        inline static PhysicsSystem*   physicsSystem = nullptr;

        physx::PxDefaultAllocator      mDefaultAllocatorCallback;
        physx::PxDefaultErrorCallback  mDefaultErrorCallback;
        physx::PxDefaultCpuDispatcher* mDispatcher = nullptr;
        physx::PxTolerancesScale       mToleranceScale;

        physx::PxFoundation*           mFoundation = nullptr;
        physx::PxPhysics*              mPhysics = nullptr;

        physx::PxScene*                mScene = nullptr;

        physx::PxPvd*                  mPvd = nullptr;
        physx::PxPvdTransport*         mPvdTransporter = nullptr;

        std::unordered_map<physx::PxRigidActor*, entt::entity> actorMap {};
    };
}
