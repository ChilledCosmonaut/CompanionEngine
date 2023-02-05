#pragma once

#include "../../../../../src/ECS/entt.hpp"

namespace gl3::engine::Physics::TriggerEvents {

    /// Used for identifying entities with a trigger enter last frame (Added to both trigger and triggered)
    struct OnTriggerEnter {
        /// Is the other entity in this physics interaction
        entt::entity entity = entt::null;
    };

    /// Used for identifying entities with a trigger exit last frame (Added to both trigger and triggered)
    struct OnTriggerExit {
        /// Is the other entity in this physics interaction
        entt::entity entity = entt::null;
    };
}
