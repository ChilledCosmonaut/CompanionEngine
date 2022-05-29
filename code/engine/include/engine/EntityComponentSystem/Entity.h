#pragma once
#include <vector>
#include "EntityComponentSystem.h"
#include "engine/EntityComponentSystem/ComponentManager.h"
#include "entt.hpp"

namespace gl3::engine::entityComponentSystem {
    class Entity final {
        friend class EntityManager;

    public:
        [[nodiscard]] guid_t guid() const { /*return id;*/ }
        [[nodiscard]] bool isDeleted() const { return deleted; }

        template<typename C, typename ...Args>
        [[nodiscard]] C &addComponent(Args ...args) {
            if(!registry.all_of<C>(entity)) {
                return registry.emplace<C>(entity, args...);
            }
            return nullptr;
        }

        template<typename C>
        C &getComponent() {
            return registry.all_of<C>(entity);
        }

        template<typename C>
        void removeComponent(Component &component) {
            component.deleted = true;
            registry.remove<C>(entity);
        }

        template<typename C>
        void removeComponent() {
            auto &component = registry.all_of<C>(entity);
            removeComponent<C>(component);
        }

    private:
        explicit Entity(entt::registry currentRegistry, ComponentManager &componentManager) : componentManager(componentManager) {
            entity = currentRegistry.create();
        }
        void deleteAllComponents() {}

        entt::entity entity;
        entt::registry registry;
        bool deleted = false;
        ComponentManager &componentManager;
    };
}
