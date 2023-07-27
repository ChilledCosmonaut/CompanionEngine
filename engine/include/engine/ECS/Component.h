#pragma once

#include "../../../src/ECS/entt.hpp"

namespace gl3::engine::Ecs {

    struct Component{
    protected:
        entt::entity entity = entt::null;
    };
}