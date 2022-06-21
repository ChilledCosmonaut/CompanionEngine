#pragma once

#include "engine/GraphicsEngine/Scene.h"

namespace gl3::game {

    class SampleScene : public engine::Graphics::Scene {
    public:
        void onSetup(){
            AddMainCamera();
            registry.emplace<ShipMovementSettings>(mainCameraObject);

            AddSkybox();

            auto test = CreateEntity();
            auto &model = registry.emplace<engine::Graphics::Components::Model>(test);
            model.path = "../../assets/backpack.obj";
            model.shader = std::make_shared<engine::Graphics::shader>("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

            auto &transform = registry.get<engine::Graphics::Components::Transform>(test);
            transform.SetTranslation(glm::vec3(0,0,-14));
            transform.SetScale(glm::vec3(50,50,50));
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
