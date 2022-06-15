#pragma once

#include "engine/GraphicsEngine/Scene.h"

namespace gl3::game {

    class SampleScene : public engine::Graphics::Scene {
    public:
        void onSetup(){
            AddMainCamera();
            AddSkybox();

            auto test = CreateEntity();
            auto &model = registry.emplace<engine::Graphics::Components::Model>(test);
            model.path = "../../assets/backpack.obj";
            model.shader = std::make_shared<engine::Graphics::shader>("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

            auto &transform = registry.get<engine::Graphics::Components::Transform>(test);
            transform.AddTranslation(glm::vec3(-5,3,1-4));
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
