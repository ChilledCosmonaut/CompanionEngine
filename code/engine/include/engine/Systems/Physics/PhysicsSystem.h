#pragma once

#include "PxPhysicsAPI.h"
#include <stdexcept>

#include "engine/Time.h"
#include "engine/Systems/Physics/Components/Rigidbody.h"
#include "engine/Scene.h"

namespace gl3::engine::Physics {

    class PhysicsSystem {
    public:
        static PhysicsSystem &GetPhysicsSystem(){
            if (physicsSystem != nullptr)
                return *physicsSystem;
            throw std::domain_error("PhysicsSystem is not yet created");
        }

        PhysicsSystem(){
            // init physx
            mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
            if (!mFoundation) throw("PxCreateFoundation failed!");

            mToleranceScale.length = 100;        // typical length of an object
            mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice

#if DEBUG
            mPvd = PxCreatePvd(*mFoundation);
            physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
            mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
            mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
#else
            mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale);
#endif

            physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
            sceneDesc.gravity = physx::PxVec3(0.0f, 0.0f, 0.0f);
            mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
            sceneDesc.cpuDispatcher	= mDispatcher;
            sceneDesc.filterShader	= physx::PxDefaultSimulationFilterShader;
            mScene = mPhysics->createScene(sceneDesc);

#if DEBUG
            physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
            if(pvdClient)
            {
                pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
                pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
                pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
            }
#endif
            physicsSystem = this;
        };

        ~PhysicsSystem(){
            mPhysics->release();
#if DEBUG
            mPvd->release();
            mPvdTransporter->release();
#endif
            mFoundation->release();
        }

        physx::PxPhysics* GetPhysics() {
            return mPhysics;
        }

        void AddPhysicsObjects(physx::PxRigidDynamic* rigidBody) {
            mScene->addActor(*rigidBody);
        }

        void AddPhysicsObjects(physx::PxRigidStatic* rigidStatic) {
            mScene->addActor(*rigidStatic);
        }

        void RemovePhysicsObjects() {

        }

        void SimulatePhysics(Scene &scene) {
            mScene->simulate(Time::GetDeltaTime());
            mScene->fetchResults(true);

            auto& registry = Ecs::Registry::getCurrent();
            auto componentView = registry.view<Components::RigidBody, Graphics::Components::Transform>();

            for (auto& entity : componentView) {
                auto& rigidBody = componentView.get<Components::RigidBody>(entity);
                auto& transform = componentView.get<Graphics::Components::Transform>(entity);

                auto physicsTransform = rigidBody.rigidBody->getGlobalPose();

               Graphics::Utils::TransformUtils::SetRotation(transform,glm::quat(
                       physicsTransform.q.w, physicsTransform.q.x, physicsTransform.q.y, physicsTransform.q.z));
               Graphics::Utils::TransformUtils::SetTranslation(transform, glm::vec3(
                       physicsTransform.p.x, physicsTransform.p.y, physicsTransform.p.z));
            }
        };

    private:
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
