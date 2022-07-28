#pragma once

#include "PxPhysicsAPI.h"

namespace gl3::engine::Physics {

    class PhysicsScene {
    public:
        PhysicsScene(){
            // init physx
            mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
            if (!mFoundation) throw("PxCreateFoundation failed!");
            /*mPvd = PxCreatePvd(*mFoundation);
            physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
            mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);*/
            //mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(),true, mPvd);
            mToleranceScale.length = 100;        // typical length of an object
            mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice
            //mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
            mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale);

            physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
            sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
            mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
            sceneDesc.cpuDispatcher	= mDispatcher;
            sceneDesc.filterShader	= physx::PxDefaultSimulationFilterShader;
            mScene = mPhysics->createScene(sceneDesc);

            /*physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
            if(pvdClient)
            {
                pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
                pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
                pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
            }*/
        }

        physx::PxScene* GetScene(){
            return mScene;
        }

        physx::PxPhysics* GetPhysicsBase(){
            return mPhysics;
        }

    private:
        // declare variables
        physx::PxDefaultAllocator      mDefaultAllocatorCallback;
        physx::PxDefaultErrorCallback  mDefaultErrorCallback;
        physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
        physx::PxTolerancesScale       mToleranceScale;

        physx::PxFoundation*           mFoundation = NULL;
        physx::PxPhysics*              mPhysics = NULL;

        physx::PxScene*                mScene = NULL;
        physx::PxMaterial*             mMaterial = NULL;

        physx::PxPvd*                  mPvd = NULL;
    };
}
