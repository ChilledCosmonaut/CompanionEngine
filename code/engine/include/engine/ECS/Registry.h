#pragma once

#include "../../../src/ECS/entt.hpp"
#include "Flags.h"

namespace gl3::engine::Ecs {

    class Registry {
    public:
        static entt::registry& getCurrent(){
            return registry;
        }

        template<typename Component, typename... Args>
        static Component &AddComponent(entt::entity entity, Args &&...args) {
            if (!registry.any_of<Component>(entity)){

                if (!registry.any_of<Flags::Setup<Component>>(entity))
                    registry.emplace<Flags::Setup<Component>>(entity);

                return registry.emplace<Component>(entity, args...);
            } else {
                return registry.get<Component>(entity);
            }
        }

        template<typename Component, typename... Args>
        static Component &AddComponentWithoutFlag(entt::entity entity, Args &&...args) {
            if (!registry.any_of<Component>(entity)){
                return registry.emplace<Component>(entity, args...);
            } else {
                return registry.get<Component>(entity);
            }
        }

        template<typename Component>
        static void RemoveSetupFlag(entt::entity entity) {
            if (registry.any_of<Flags::Setup<Component>>(entity))
                registry.remove<Flags::Setup<Component>>(entity);
        }

        template<typename Component>
        static void UpdateComponent(entt::entity entity) {
            if (!registry.any_of<Flags::Update<Component>>(entity))
                registry.emplace<Flags::Update<Component>>(entity);
        }

        template<typename Component>
        static void RemoveUpdateFlag(entt::entity entity) {
            if (registry.any_of<Flags::Update<Component>>(entity))
                registry.remove<Flags::Update<Component>>(entity);
        }

        template<typename Component>
        static void DestroyComponent(entt::entity entity) {
            if (!registry.any_of<Flags::Destroy<Component>>(entity))
                registry.emplace<Flags::Destroy<Component>>(entity);
        }

        template<typename Component>
        static void RemoveDestroyFlag(entt::entity entity) {
            if (registry.any_of<Flags::Destroy<Component>>(entity))
                registry.remove<Flags::Destroy<Component>>(entity);
        }

        template<typename Component, typename... Args>
        static void DestroyComponentWithoutFlag(entt::entity entity, Args &&...args) {
            registry.remove<Component>(entity);
        }

    private:
        inline static entt::registry registry {};
    };
}
