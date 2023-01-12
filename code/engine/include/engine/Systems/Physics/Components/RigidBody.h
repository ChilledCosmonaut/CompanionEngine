#pragma once

#include <variant>
#include "Shapes.h"

namespace gl3::engine::Physics {

    struct RigidBody{
    public:
        physx::PxPhysics *physicsContext = nullptr;
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidDynamic* rigidBody = nullptr;
        physx::PxShape* physXShape = nullptr;
        float mass = 1.f;
        bool isTrigger = false;
        Shapes::Shapes shape;
        std::variant<Shapes::Sphere, Shapes::Box, Shapes::Capsule> shapeInfo;
    };

    struct RigidStatic{
    public:
        physx::PxPhysics *physicsContext = nullptr;
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidStatic* rigidStatic = nullptr;
    };
}