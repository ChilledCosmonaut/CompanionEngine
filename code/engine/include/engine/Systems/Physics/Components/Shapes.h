#pragma once

#include "PxPhysicsAPI.h"

namespace gl3::engine::Physics::Utils {
    class RigidBodyUtils;
}

namespace gl3::engine::Physics::Components::Shapes {

     enum Shapes{
         Sphere, Box, Capsule, Plane
     };

    struct Sphere {
        friend class Utils::RigidBodyUtils;

    private:
        float radius = 1;
    };

    struct Box {
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxVec3 dimensions = physx::PxVec3(1,1,1);
    };

    struct Capsule {
        friend class Utils::RigidBodyUtils;

    private:
        float radius = 1;
        float halfHeight = 0.5f;
    };

    struct Plane {
        friend class Utils::RigidBodyUtils;

    private:
        physx::PxVec2 dimensions = physx::PxVec2(1,1);
    };

    union Shape{

    public:
        struct Sphere sphere;
        struct Box box;
        struct Capsule capsule;
        struct Plane plane;
    };
}
