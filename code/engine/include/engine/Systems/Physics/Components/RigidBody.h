#pragma once

#include <variant>
#include "Shapes.h"

namespace gl3::engine::Physics {

    struct RigidBody{
    public:
        physx::PxPhysics *physicsContext = nullptr;
        /// Determines the properties of surface interaction
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, 1.f);
        /// Pointer to the rigidbody of physX
        physx::PxRigidDynamic* rigidBody = nullptr;
        physx::PxShape* physXShape = nullptr;
        /// Mass for physics simulation **Setting the mass to zero results in an immovable object**
        float mass = 1.f;
        /// Determines if a rigid body is only a trigger. **Omits collision**
        bool isTrigger = false;
        Shapes::Shapes shape;
        /// Sets the specified shape info
        std::variant<Shapes::Sphere, Shapes::Box, Shapes::Capsule> shapeInfo;
    };

    struct RigidStatic{
    public:
        physx::PxPhysics *physicsContext = nullptr;
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidStatic* rigidStatic = nullptr;
    };
}