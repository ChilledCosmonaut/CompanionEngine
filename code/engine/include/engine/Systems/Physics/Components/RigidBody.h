#pragma once

#include <variant>
#include "Shapes.h"

namespace gl3::engine::Physics::Components {

    struct RigidBody{
    public:
        physx::PxPhysics *physicsContext = nullptr;
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidDynamic* rigidBody = nullptr;
        physx::PxShape* physXShape = nullptr;
        float mass = 1.f;
        Shapes::Shapes shape;
        std::variant<struct Shapes::Sphere, struct Shapes::Box, struct Shapes::Capsule, struct Shapes::Plane> shapeInfo;
    };
}