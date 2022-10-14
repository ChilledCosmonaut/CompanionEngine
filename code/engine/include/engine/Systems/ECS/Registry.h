#pragma once

#include "../../../../src/EntityComponentSystem/entt.hpp"
#include "Flags.h"

namespace gl3::engine::Ecs {

    class Registry {
    public:
        static entt::registry& getCurrent(){
            return registry;
        }

        template<typename Component>
        static void AddSetupFlag(entt::entity entity) {
            if (!registry.any_of<Flags::Setup<Component>>(entity))
                registry.emplace<Flags::Setup<Component>>(entity);
        }

        template<typename Component>
        static void RemoveSetupFlag(entt::entity entity) {
            if (registry.any_of<Flags::Setup<Component>>(entity))
                registry.remove<Flags::Setup<Component>>(entity);
        }

        template<typename Component>
        static void AddUpdateFlag(entt::entity entity) {
            if (!registry.any_of<Flags::Update<Component>>(entity))
                registry.emplace<Flags::Update<Component>>(entity);
        }

        template<typename Component>
        static void RemoveUpdateFlag(entt::entity entity) {
            if (registry.any_of<Flags::Update<Component>>(entity))
                registry.remove<Flags::Update<Component>>(entity);
        }

        template<typename Component>
        static void AddDestroyFlag(entt::entity entity) {
            if (!registry.any_of<Flags::Destroy<Component>>(entity))
                registry.emplace<Flags::Destroy<Component>>(entity);
        }

        template<typename Component>
        static void RemoveDestroyFlag(entt::entity entity) {
            if (registry.any_of<Flags::Destroy<Component>>(entity))
                registry.remove<Flags::Destroy<Component>>(entity);
        }

    private:
        inline static entt::registry registry {};
    };
}
