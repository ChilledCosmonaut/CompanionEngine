#pragma once

#include "PxPhysicsAPI.h"

namespace gl3::engine::Physics::Utils {
    class RigidBodyUtils;
}

namespace gl3::engine::Physics::Components {

    struct SphereCollider{
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        float radius = 1;
        physx::PxRigidDynamic* rigidBody = nullptr;
    };

    struct BoxCollider{
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxVec3 dimensions;
        physx::PxRigidDynamic* rigidBody = nullptr;
    };

    struct CapsuleCollider{
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        float radius;
        float halfHeight;
        physx::PxRigidDynamic* rigidBody = nullptr;
    };

    struct PlaneCollider{
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidDynamic* rigidBody = nullptr;
    };
}