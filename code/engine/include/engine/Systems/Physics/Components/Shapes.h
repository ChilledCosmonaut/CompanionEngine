#pragma once

#include "PxPhysicsAPI.h"

namespace gl3::engine::Physics::Utils {
    class RigidBodyUtils;
}

namespace gl3::engine::Physics::Components::Shapes {

    struct Shape{
        friend class Utils::RigidBodyUtils;

    public:
        virtual ~Shape() = default;
    };

    struct Sphere : Shape {

    private:
        float radius = 1;
    };

    struct Box : Shape {

    private:
        physx::PxVec3 dimensions = physx::PxVec3(1,1,1);
    };

    struct Capsule : Shape {

    private:
        float radius = 1;
        float halfHeight = 0.5f;
    };

    struct Plane : Shape {

    private:
        physx::PxVec2 dimensions = physx::PxVec2(1,1);
    };
}
