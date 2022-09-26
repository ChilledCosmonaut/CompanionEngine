#pragma once

#include "Shapes.h"

namespace gl3::engine::Physics::Utils {
    class RigidBodyUtils;
}

namespace gl3::engine::Physics::Components {

    struct RigidBody{
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidDynamic* rigidBody = nullptr;
        Shapes::Shape shape = Shapes::Sphere();
    };
}