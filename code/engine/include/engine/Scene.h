#pragma once

#include "../../src/ECS/entt.hpp"
#include "engine/ECS/Registry.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/ECS/Flags.h"

namespace gl3::engine{

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

        entt::entity CreateEntity(){
            auto& registry = Ecs::Registry::getCurrent();

            if(rootEntity == entt::tombstone){
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

        entt::entity rootEntity = entt::tombstone;

    private:
        std::vector<entt::entity> entityList {};
    };
}