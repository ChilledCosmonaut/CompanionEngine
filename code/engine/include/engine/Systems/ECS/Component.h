#pragma once

#include "../../../../src/EntityComponentSystem/entt.hpp"

namespace gl3::engine::Ecs {

    struct Component{
    protected:
        entt::entity entity = entt::tombstone;
    };
}