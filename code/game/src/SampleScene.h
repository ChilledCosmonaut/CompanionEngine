#pragma once

#include "engine/GraphicsEngine/Scene.h"
#include "engine/SoundSystem/AudioSourceUtils.h"
#include "engine/GraphicsEngine/Utils/TransformUtils.h"
#include "engine/GraphicsEngine/Utils/ModelUtils.h"

namespace gl3::game {

    class SampleScene : public engine::Graphics::Scene {
    public:
        void onSetup(){
            AddMainCamera();
            registry.emplace<ShipMovementSettings>(mainCameraObject);

            AddSkybox();

            auto test = CreateEntity();
            auto &model = registry.emplace<engine::Graphics::Components::Model>(test);
            engine::Graphics::Utils::ModelUtils::SetPath(model, "../../assets/backpack.obj");
            auto shader = std::make_shared<engine::Graphics::shader>("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
            engine::Graphics::Utils::ModelUtils::SetShader(model, shader);

            auto &transform = registry.get<engine::Graphics::Components::Transform>(test);
            engine::Graphics::Utils::TransformUtils::SetTranslation(transform, glm::vec3(0,0,-14));
            engine::Graphics::Utils::TransformUtils::SetScale(transform, glm::vec3(1,1,1));

            auto &cameraTransform = registry.get<engine::Graphics::Components::Transform>(mainCameraObject);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(cameraTransform, mainCameraObject, test);

            auto &audioSource = registry.emplace<engine::soundSystem::AudioSource>(test);
            engine::soundSystem::AudioSourceUtils::SetupAudioSource(audioSource, "../../assets/audio/electronic-wave.mp3");
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
