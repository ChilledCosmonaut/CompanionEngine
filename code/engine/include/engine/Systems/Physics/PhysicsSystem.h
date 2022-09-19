#pragma once

#include "PxPhysicsAPI.h"

#include "engine/Time.h"

namespace gl3::engine::Physics {

    class PhysicsSystem {
    public:
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
            sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
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
        };

        void AddPhysicsObjects() {

        }

        void RemovePhysicsObjects() {

        }

        void SimulatePhysics() {
            mScene->simulate(Time::GetDeltaTime());
            mScene->fetchResults(true);
        };

        void ShutdownPhysics(){
            mPhysics->release();
#if DEBUG

            mPvd->release();
            mPvdTransporter->release();
#endif
            mFoundation->release();
        }

    private:
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
