#pragma once

#include <memory>
#include "camera.h"
#include "../../../src/EntityComponentSystem/entt.hpp"
#include "engine/EntityComponentSystem/Entity.h"
#include "engine/GraphicsEngine/Components/Skybox.h"

namespace gl3::engine::Graphics{

    class Scene {

    public:

        entt::registry* getRegistry(){
            return &registry;
        }

        void addSkybox(){
            entt::entity entity = registry.create();
            registry.emplace<Components::SkyboxComponent>(entity);
        }

        template<typename Included, typename Excluded>
        entt::basic_view<entt::entity, entt::get_t<Included>, entt::exclude_t<Excluded>> getAllComponents(){
            return registry.view<Included, Excluded>();
        }

        virtual void onSetup() = 0;

    protected:

        std::unique_ptr<entityComponentSystem::Entity> CreateEntity(){
            auto newEntity = entityComponentSystem::Entity(registry);
            return std::make_unique<entityComponentSystem::Entity>(newEntity);
        }

    private:
        entt::registry registry;
    };
}