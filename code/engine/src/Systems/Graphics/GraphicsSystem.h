#pragma once

#include <iostream>

#include "engine/System.h"
#include "engine/Systems/FileManager/FileManager.h"

#include "engine/Systems/Graphics/Components/Model.h"
#include "engine/Systems/Graphics/Components/Camera.h"
#include "engine/Systems/Graphics/Components/Transform.h"

#include "engine/Systems/Graphics/Utils/SkyboxUtils.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"
#include "engine/Systems/Graphics/Utils/CameraUtils.h"

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

        void OnShutdown(Game &engine) override {
            //engine.getCurrentScene()->ReleasePhysicsScene();
        };

    private:
        glm::mat4 currentProjection;
        glm::mat4 currentView;
    };
}