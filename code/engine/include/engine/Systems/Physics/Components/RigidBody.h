#pragma once

#include <variant>
#include "Shapes.h"

namespace gl3::engine::Physics::Utils {
    class RigidBodyUtils;
}

namespace gl3::engine::Physics::Components {

    struct RigidBody{
        friend class Utils::RigidBodyUtils;

    public:
        void SetMaterialProperties(glm::vec3 matProperties){
            materialProperties = physx::PxVec3(matProperties.x, matProperties.y, matProperties.z);
        }

        void Set

    private:
        physx::PxVec3 materialProperties = physx::PxVec3(.5f, .5f, .5f);
        physx::PxRigidDynamic* rigidBody = nullptr;
        Shapes::Shapes shape;
        std::variant<struct Shapes::Sphere, struct Shapes::Box, struct Shapes::Capsule, struct Shapes::Plane> shapeInfo;
    };
}