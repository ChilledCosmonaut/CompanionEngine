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
            engine::Ecs::Registry::AddComponent<ShipMovementSettings>(mainCameraObject);

            auto &cameraTransform = registry.get<engine::Graphics::Transform>(mainCameraObject);
            engine::Graphics::TransformationUtils::AddRotation(mainCameraObject, cameraTransform, glm::vec3(0, 180, 0));

            auto &rigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(mainCameraObject);
            rigidBody.shapeInfo = Shapes::Box{};
            rigidBody.shape = Shapes::sphere;

            auto &backgroundMusic = engine::Ecs::Registry::AddComponent<engine::soundSystem::BackgroundAudioSource>(mainCameraObject);
            backgroundMusic.fileName = assets::audio$ambientSpace3$wav;
            backgroundMusic.play = true;

            auto skybox = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Skybox>(skybox);

            entt::entity playerShip = Utils::ModelCreationTemplates::CreatePlayer(this);
            engine::Graphics::TransformationUtils::AddChildEntity(mainCameraObject, playerShip);

            auto levelRoot = CreateEntity();
            auto &transform = registry.get<Graphics::Transform>(levelRoot);
            //transform.translation = glm::vec3(90, -30, 300);
            TransformationUtils::SetRotation(levelRoot, transform, glm::vec3(0, 0, 20));
            auto spaceStation = Utils::ModelCreationTemplates::CreateSpaceStation(this);
            TransformationUtils::AddChildEntity(levelRoot, spaceStation);
            auto asteroidBelt = Utils::ModelCreationTemplates::CreateAsteroidBelt(this, 140, 220, 10);
            TransformationUtils::AddChildEntity(levelRoot, asteroidBelt);
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
