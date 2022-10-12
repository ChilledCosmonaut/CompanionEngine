#pragma once

#include "PxConfig.h" //Needs to stay here else PhysX won't find some HeaderFiles
#include "../../../../src/EntityComponentSystem/entt.hpp"
#include "engine/Systems/ECS/Registry.h"
#include "engine/Systems/Graphics/Utils/TransformUtils.h"

namespace gl3::engine::Graphics{

    class Scene {

    public:
        virtual void onSetup() = 0;

        void Destroy(){
            // Flag all entities in the list for destruction
        }

    protected:

        entt::entity CreateEntity(){
            auto& registry = Ecs::Registry::getCurrent();

            entt::entity entity = registry.create();
            entityList.emplace_back(entity);

            auto &transform = registry.emplace<Components::Transform>(entity);
            engine::Graphics::Utils::TransformUtils::SetCurrentRegistry(transform, registry);

            return entity;
        }

    private:
        std::vector<entt::entity> entityList {};
    };
}