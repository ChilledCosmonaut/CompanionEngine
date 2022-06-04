#pragma once

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

    protected:
        virtual void onSetup() = 0;

        std::unique_ptr<entityComponentSystem::Entity> CreateEntity(){
            auto newEntity = entityComponentSystem::Entity(registry);
            return std::make_unique<entityComponentSystem::Entity>(newEntity);
        }

    private:
        entt::registry registry;
    };
}

