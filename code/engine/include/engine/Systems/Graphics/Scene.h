#pragma once

#include "PxConfig.h" //Needs to stay here else PhysX won't find some HeaderFiles
#include <memory>
#include <utility>
#include "../../../../src/EntityComponentSystem/entt.hpp"
#include "engine/Systems/Graphics/Components/Skybox.h"
#include "engine/Systems/Graphics/Components/Model.h"
#include "engine/Systems/Graphics/Components/Camera.h"
#include "engine/Systems/Graphics/Utils/TransformUtils.h"

namespace gl3::engine::Graphics{

    class Scene {

    public:

        virtual void onSetup() = 0;

    protected:

        entt::entity CreateEntity(){
            /*entt::entity entity = registry.create();
            auto &transform = registry.emplace<Components::Transform>(entity);
            engine::Graphics::Utils::TransformUtils::SetCurrentRegistry(transform, registry);
            return entity;*/
        }
    };
}