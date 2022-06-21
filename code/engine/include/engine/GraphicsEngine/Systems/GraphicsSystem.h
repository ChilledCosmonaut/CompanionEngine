#pragma once

#include <iostream>

#include "engine/GraphicsEngine/Components/Model.h"
#include "engine/GraphicsEngine/Components/Camera.h"
#include "engine/GraphicsEngine/Components/Transform.h"

#include "engine/FileManager/FileManager.h"
#include "engine/GraphicsEngine/Utils/SkyboxUtils.h"
#include "engine/EntityComponentSystem/System.h"
#include "engine/GraphicsEngine/Utils/ModelUtils.h"

namespace gl3::engine::Graphics::Systems{

    class GraphicsSystem : public entityComponentSystem::System {
    public:
        GraphicsSystem() = default;

        void OnSwitchingScenes(Scene &scene) override {
            Utils::SkyboxUtils::SetupSkybox(scene);
            Utils::ModelUtils::SetUpModel(scene);
        }

        void OnDrawCall(Scene &scene) override;

        void Start(Game &game) override {};

        void Update(Game &game) override {};

        void OnShutdown(Game &engine) override {};

    private:
        glm::mat4 currentProjection;
        glm::mat4 currentView;
    };
}