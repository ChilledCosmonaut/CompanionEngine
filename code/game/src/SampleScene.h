#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"
#include "Components/EnemyBehavourSettings.h"
#include "generated/Assets.h"
#include "Utils/ModelCreationTemplates.h"

namespace gl3::game {

    using namespace engine::Physics;

    class SampleScene : public engine::Scene {
    public:
        void onSetup() override{
            auto& registry = engine::Ecs::Registry::getCurrent();

            auto directionLightObject = CreateEntity();
            auto& directionLight = engine::Ecs::Registry::AddComponent<engine::Graphics::DirectionLight>(directionLightObject);

            auto mainCameraObject = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Camera>(mainCameraObject);

            auto &transform = registry.get<engine::Graphics::Transform>(mainCameraObject);
            engine::Graphics::TransformationUtils::AddRotation(mainCameraObject, transform, glm::vec3(0, 0, 20));
            transform.translation = glm::vec3(-90, 30, -300);

            auto &backgroundMusic = engine::Ecs::Registry::AddComponent<engine::soundSystem::BackgroundAudioSource>(mainCameraObject);
            backgroundMusic.fileName = assets::audio$ambientSpace3$wav;
            backgroundMusic.play = true;

            auto skybox = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Skybox>(skybox);

            auto cockpit = CreateEntity();


            Utils::ModelCreationTemplates::CreatePlayer(this, mainCameraObject);

            auto levelRoot = CreateEntity();
            auto spaceStation = Utils::ModelCreationTemplates::CreateSpaceStation(this);
            TransformationUtils::AddChildEntity(levelRoot, spaceStation);
            auto asteroidBelt = Utils::ModelCreationTemplates::CreateAsteroidBelt(this, 140, 220, 10);
            TransformationUtils::AddChildEntity(levelRoot, asteroidBelt);
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
