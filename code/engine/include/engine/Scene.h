#pragma once

#include "PxConfig.h" //Needs to stay here else PhysX won't find some HeaderFiles
#include "../../src/ECS/entt.hpp"
#include "engine/ECS/Registry.h"
#include "engine/Systems/Graphics/Utils/TransformUtils.h"
#include "engine/ECS/Flags.h"

namespace gl3::engine{

    class Scene {

    public:
        virtual void onSetup() = 0;

        /// Flags all entities in the entity list of the scene for destruction
        void Quit(){

            auto& registry = Ecs::Registry::getCurrent();

            for (auto entity:entityList) {
                registry.emplace<Ecs::Flags::Destroy<Graphics::Components::Transform>>(entity);
            }
        }

    protected:

        entt::entity CreateEntity(){
            auto& registry = Ecs::Registry::getCurrent();

            entt::entity entity = registry.create();
            entityList.emplace_back(entity);

            auto &transform = engine::Ecs::Registry::AddComponent<Graphics::Components::Transform>(entity);

            return entity;
        }

    private:
        std::vector<entt::entity> entityList {};
    };
}