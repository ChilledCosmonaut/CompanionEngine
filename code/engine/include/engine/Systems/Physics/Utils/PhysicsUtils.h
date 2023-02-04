#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "PxPhysicsAPI.h"

#include "engine/ECS/Registry.h"
#include "../../../../../src/Systems/Physics/PhysicsSystem.h"

namespace gl3::engine::Physics{
    /// Provides a simple collection of some physics related utility functions
    class PhysicsUtils {
    public:
        /**
         * Makes an raycast from the specified origin and returns a tombstone if no intersection takes place.
         * @param origin Origin transform in world space
         * @param direction Direction to point raycast at in world space
         * @param maxDistance Maximum range of raycasz
         * @return Returns the first entity hit. If no other rigid bodies are hit a tombstone entity is returned
         */
        static entt::entity MakeRaycast(glm::vec3 origin, glm::vec3 direction, float maxDistance);
    };
}
