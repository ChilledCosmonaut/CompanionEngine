#pragma once
#include <vector>
#include "entt.hpp"
#include "Component.h"

namespace gl3::engine::entityComponentSystem {
    class Entity final {
        friend class Graphics::Scene;

    public:
        [[nodiscard]] entt::entity entityId() const { return entity; }
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
        void removeComponent() {
            registry.remove<C>(entity);
        }

        explicit Entity(entt::registry &currentRegistry) : registry(currentRegistry) {
            entity = currentRegistry.create();
        }

    private:

        entt::entity entity;
        entt::registry &registry;
        bool deleted = false;
    };
}
