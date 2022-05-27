#pragma once
#include <vector>
#include "EntityComponentSystem.h"
#include "engine/EntityComponentSystem/ComponentManager.h"

namespace gl3::engine::entityComponentSystem {
    class Entity final {
        friend class EntityManager;

    public:
        [[nodiscard]] guid_t guid() const { return id; }
        [[nodiscard]] bool isDeleted() const { return deleted; }

        template<typename C>
        [[nodiscard]] C &addComponent() {
            return componentManager.addComponent<C>(id);
        }

        template<typename C>
        C &getComponent() {
            return componentManager.getComponent<C>(id);
        }

        template<typename C>
        void removeComponent(Component &component) {
            component.deleted = true;
            componentManager.removeComponent<C>(id);
        }

        template<typename C>
        void removeComponent() {
            auto &component = getComponent<C>();
            removeComponent<C>(component);
        }

    private:
        explicit Entity(guid_t id, ComponentManager &componentManager) : id(id), componentManager(componentManager) {}
        void deleteAllComponents() {
            componentManager.removeComponents(id);
        }

        guid_t id = invalidID;
        bool deleted = false;
        ComponentManager &componentManager;
    };
}
