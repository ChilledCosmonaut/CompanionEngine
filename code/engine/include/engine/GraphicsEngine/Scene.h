#pragma once

#include "camera.h"
#include "entt.hpp"
#include "engine/EntityComponentSystem/Entity.h"

namespace gl3::engine::Graphics{

    class Scene {
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

