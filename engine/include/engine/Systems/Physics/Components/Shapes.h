#pragma once

#include "PxPhysicsAPI.h"

namespace gl3::engine::Physics::Shapes {

    enum Shapes {
        sphere, box, capsule, plane
    };

    /// Info for sphere rigid body
    struct Sphere {
        /// Radius parameter of sphere
        float radius = 1;
    };

    /// Info for box rigid body
    struct Box {
        /// Dimensions of the box in a format of a vector 3
        physx::PxVec3 dimensions = physx::PxVec3(1, 1, 1);
    };

    /// Info for capsule rigid body
    struct Capsule {
        /// Determines the radius of the half circle on the endings
        float radius = 1;
        /// Determines the height of the capsule
        float halfHeight = 0.5f;
    };

    struct Plane {
        physx::PxVec2 dimensions = physx::PxVec2(100, 100);
    };

    union Shape {

    public:
        Sphere sphere;
        Box box;
        Capsule capsule;
        Plane plane;
    };
}
