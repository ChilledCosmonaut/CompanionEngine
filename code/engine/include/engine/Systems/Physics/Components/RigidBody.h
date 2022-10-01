#pragma once

#include <variant>
#include "Shapes.h"

namespace gl3::engine::Physics::Utils {
    class RigidBodyUtils;
}

namespace gl3::engine::Physics::Components {

    struct RigidBody{
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxPhysics *physicsContext = nullptr;
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidDynamic* rigidBody = nullptr;
        physx::PxShape* physXShape = nullptr;
        float mass = 1.f;
        Shapes::Shapes shape;
        std::variant<struct Shapes::sphere, struct Shapes::Box, struct Shapes::Capsule, struct Shapes::Plane> shapeInfo;
    };
}