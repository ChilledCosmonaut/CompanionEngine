#pragma once

#include "../../../../../src/ECS/entt.hpp"

namespace gl3::engine::Physics::TriggerEvents {

    struct OnTriggerEnter {
        entt::entity entity = entt::tombstone;
    };

    struct OnTriggerExit {
        entt::entity entity = entt::tombstone;
    };
}
