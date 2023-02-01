#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "PxPhysicsAPI.h"

#include "engine/ECS/Registry.h"
#include "../../../../../src/Systems/Physics/PhysicsSystem.h"

namespace gl3::engine::Physics{
    class PhysicsUtils {
    public:
        entt::entity MakeRaycast(glm::vec3 origin, glm::vec3 direction, float maxDistance);
    };
}
