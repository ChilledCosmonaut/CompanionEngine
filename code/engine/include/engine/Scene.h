#pragma once

#include "../../src/ECS/entt.hpp"
#include "engine/ECS/Registry.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/ECS/Flags.h"

namespace gl3::engine{

    /// Defines a scene structure for the game to render
    class Scene {
    public:
        virtual void onSetup() = 0;

        /// Flags all entities in the entity list of the scene for destruction
        void Quit(){

            auto& registry = Ecs::Registry::getCurrent();

            for (auto entity:entityList) {
                registry.emplace<Ecs::Flags::Destroy<Graphics::Transform>>(entity);
            }
        }

        /**
         * Creates a new entity with a transform
         * @return Newly created entity
         */
        entt::entity CreateEntity(){
            auto& registry = Ecs::Registry::getCurrent();

            if(!registry.valid(rootEntity)){
                rootEntity = registry.create();
                entityList.emplace_back(rootEntity);

                auto &transform = engine::Ecs::Registry::AddComponent<Graphics::Transform>(rootEntity);
            }

            entt::entity entity = registry.create();
            entityList.emplace_back(entity);

            auto &transform = engine::Ecs::Registry::AddComponent<Graphics::Transform>(entity);

            Graphics::TransformationUtils::AddChildEntity(rootEntity, entity);

            return entity;
        }

        /// Parent entity of all other entities in the scene
        entt::entity rootEntity = entt::null;

    private:
        std::vector<entt::entity> entityList {};
    };
}