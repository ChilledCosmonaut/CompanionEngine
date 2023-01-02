#pragma once

#include "PxPhysicsAPI.h"

namespace gl3::engine::Physics::Shapes {

     enum Shapes{
         sphere, box, capsule, plane
     };

    struct Sphere {
        float radius = 1;
    };

    struct Box {
        physx::PxVec3 dimensions = physx::PxVec3(1,1,1);
    };

    struct Capsule {
        float radius = 1;
        float halfHeight = 0.5f;
    };

    struct Plane {
        physx::PxVec2 dimensions = physx::PxVec2(100,100);
    };

    union Shape{

    public:
        Sphere sphere;
        Box box;
        Capsule capsule;
        Plane plane;
    };
}
