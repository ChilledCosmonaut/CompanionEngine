#pragma once

#include "../../../../src/EntityComponentSystem/entt.hpp"

namespace gl3::engine::Ecs {

    class Registry {
    public:
        static entt::registry* getRegistry(){
            return &registry;
        }

    private:
        inline static entt::registry registry {};
    };
}
