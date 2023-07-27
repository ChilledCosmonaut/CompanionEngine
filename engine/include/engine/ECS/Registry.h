#pragma once

#include "../../../src/ECS/entt.hpp"
#include "Flags.h"
#include "engine/Systems/Graphics/Components/Transform.h"

namespace gl3::engine::Ecs {

    /**
     * Singleton wrapper for entt's registry.
     * Provides a **very** small wrapper for the entt registry. Wrapper is not function complete and accessing entt directly is still necessary.
     */
    class Registry {
    public:
        /**
         * Returns a reference to the current Registry.
         * @return registry reference
         */
        static entt::registry& getCurrent(){
            return registry;
        }

        /**
         * Adds a new Component with proper flags to a specified entity.
         * This function does not guarantee that a new component instance will be created.
         * If an instance of the type does already exists it simply returns a reference to the component.
         * @tparam Component The type of the added component
         * @tparam Args Constructor parameter types
         * @param entity The entity to which the component should be added
         * @param args Constructor parameters for the component
         * @return A reference to the newly to a component of requested type
         */
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

        /**
         * Adds a component without any flags, while still returning a reference.
         * Same behaviour as `AddComponent`, but without the flag logic.
         * @tparam Component The type of the added component
         * @tparam Args Constructor parameter types
         * @param entity The entity to which the component should be added
         * @param args Constructor parameters for the component
         * @return A reference to the newly to a component of requested type
         */
        template<typename Component, typename... Args>
        static Component &AddComponentWithoutFlag(entt::entity entity, Args &&...args) {
            if (!registry.any_of<Component>(entity)){
                return registry.emplace<Component>(entity, args...);
            } else {
                return registry.get<Component>(entity);
            }
        }

        /**
         * Removes the set up flag for requested component.
         * This function should be called whenever a component is done with it's initial set up logic.
         * Else the component will be indefinitely be marked as to be set up.
         * @tparam Component Type of component regarding the flag
         * @param entity Component owning entity
         */
        template<typename Component>
        static void RemoveSetupFlag(entt::entity entity) {
            if (registry.any_of<Flags::Setup<Component>>(entity))
                registry.remove<Flags::Setup<Component>>(entity);
        }

        /**
         * Adds the update flag for requested component.
         * This function should be called whenever a component should be recalculated or updated.
         * Without this flag components will not be updated.
         * @tparam Component Type of component regarding the flag
         * @param entity Component owning entity
         */
        template<typename Component>
        static void UpdateComponent(entt::entity entity) {
            if (!registry.any_of<Flags::Update<Component>>(entity))
                registry.emplace<Flags::Update<Component>>(entity);
        }

        /**
         * Removes the update flag for requested component.
         * This function should be called whenever a component is done with recalculation logic.
         * Else the component will be indefinitely be marked as to be updated.
         * @tparam Component Type of component regarding the flag
         * @param entity Component owning entity
         */
        template<typename Component>
        static void RemoveUpdateFlag(entt::entity entity) {
            if (registry.any_of<Flags::Update<Component>>(entity))
                registry.remove<Flags::Update<Component>>(entity);
        }

        /**
         * Adds the destroy flag for requested component.
         * This function should be called whenever a component should be destroyed.
         * @tparam Component Type of component regarding the flag
         * @param entity Component owning entity
         */
        template<typename Component>
        static void DestroyComponent(entt::entity entity) {
            if (!registry.any_of<Flags::Destroy<Component>>(entity))
                registry.emplace<Flags::Destroy<Component>>(entity);
        }

        /**
         * Removes the destroy flag for requested component.
         * This function should be called whenever a component is done with it's destruction logic.
         * Remember also that the component must be destroyed manually after the logic.
         * @tparam Component Type of component regarding the flag
         * @param entity Component owning entity
         */
        template<typename Component>
        static void RemoveDestroyFlag(entt::entity entity) {
            if (registry.any_of<Flags::Destroy<Component>>(entity))
                registry.remove<Flags::Destroy<Component>>(entity);
        }

        /**
         * Immediately destroys a component.
         * Call this function only when you do not require special destruction logic.
         * @tparam Component Type of component regarding the flag
         * @param entity Component owning entity
         */
        template<typename Component>
        static void DestroyComponentWithoutFlag(entt::entity entity) {
            registry.remove<Component>(entity);
        }

        /**
         * Adds a general destroy flag for all components.
         * Also deletes all child entities.
         * This function should be called whenever a entity should be destroyed.
         * @param entity To be destroyed entity
         */
        static void DestroyEntity(entt::entity entity) {
            if (!registry.any_of<Flags::DestroyEntity>(entity))
                registry.emplace<Flags::DestroyEntity>(entity);

            auto &transform = registry.get<Graphics::Transform>(entity);
            for (entt::entity child:transform.children) {
                DestroyEntity(child);
            }
        }

        /**
         * Adds a custom empty component.
         * Special function derivative to add empty components and avoid template issues.
         * @tparam Component Type of component
         * @param entity The entity to which the component should be added
         */
        template<typename Component>
        static void AddCustomFlag(entt::entity entity) {
            if (!registry.any_of<Component>(entity))
                registry.emplace<Component>(entity);
        }

        /**
         * Removes the specified custom flag.
         * @tparam Component Type of custom flag
         * @param entity Flag owning entity
         */
        template<typename Component>
        static void RemoveCustomFlag(entt::entity entity) {
            if (registry.any_of<Flags::Destroy<Component>>(entity))
                registry.remove<Flags::Destroy<Component>>(entity);
        }

        /**
         * Checks if both entity and requested component type do exists
         * @tparam Component Requested component type
         * @param entity Entity
         * @return Boolean indicator
         */
        template<typename Component>
        static bool HasComponent(entt::entity entity) {
            if (registry.valid(entity)){
                return registry.template any_of<Component>(entity);
            }
            return false;
        }

    private:
        inline static entt::registry registry {};
    };
}
