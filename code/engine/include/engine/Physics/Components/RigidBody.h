#pragma once

#include "PxPhysicsAPI.h"

namespace gl3::engine::Physics::Utils {
    class RigidBodyUtils;
}

namespace gl3::engine::Physics::Components {

    enum BodyShapes{
        Sphere
    };

    struct RigidBody{
        friend class Utils::RigidBodyUtils;

    private:
        BodyShapes shape = Sphere;
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxVec3 shapeDimensions;
        physx::PxRigidDynamic* rigidBody = nullptr;
    };
}