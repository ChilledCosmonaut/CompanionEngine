#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"
#include "EnemyBehavourSettings.h"
#include "generated/Assets.h"

namespace gl3::game {

    using namespace engine::Physics;

    class SampleScene : public engine::Scene {
    public:
        void onSetup() override{
            auto& registry = engine::Ecs::Registry::getCurrent();
            auto fileManager = engine::filesystem::FileManager::GetFileManager();

            auto directionLightObject = CreateEntity();
            auto& directionLight = engine::Ecs::Registry::AddComponent<engine::Graphics::DirectionLight>(directionLightObject);

            engine::Graphics::Material spaceShipMaterial{};

            spaceShipMaterial.ambient  = fileManager->getAsset(assets::Images::StarSparrow_Red$png);
            spaceShipMaterial.diffuse  = fileManager->getAsset(assets::Images::StarSparrow_Red$png);
            spaceShipMaterial.specular = fileManager->getAsset(assets::Images::StarSparrow_Red$png);
            spaceShipMaterial.normal   = fileManager->getAsset(assets::Images::StarSparrow$Textures$StarSparrow_Normal$png);

            auto shader = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$fragmentShader$glsl)/*std::make_shared<engine::Graphics::shader>(assets::shaders$vertexShader$glsl, assets::shaders$fragmentShader$glsl)*/;
            auto untexturedShader = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$untexturedFragmentShader$glsl);
            auto unlitShader = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$lightFragmentShader$glsl);

            auto mainCameraObject = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Camera>(mainCameraObject);
            engine::Ecs::Registry::AddComponent<ShipMovementSettings>(mainCameraObject);

            auto &cameraTransform = registry.get<engine::Graphics::Transform>(mainCameraObject);
            engine::Graphics::TransformationUtils::AddRotation(mainCameraObject, cameraTransform, glm::vec3(0, 180, 0));
            auto &rigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(mainCameraObject);
            rigidBody.shapeInfo = Shapes::Sphere{2};
            rigidBody.shape = Shapes::sphere;

            auto skybox = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Skybox>(skybox);

            auto playerShip = CreateEntity();
            auto &playerModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(playerShip);
            playerModel.modelName = assets::Models::SpaceShip$MainFrame$obj;
            engine::Graphics::ModelUtils::SetShader(playerModel, untexturedShader);

            engine::Graphics::TransformationUtils::AddChildEntity(mainCameraObject, playerShip);

            auto ball = CreateEntity();
            auto &ballTransform = registry.get<engine::Graphics::Transform>(ball);
            ballTransform.translation = glm::vec3(2,2,2);
            auto &ballModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(ball);
            ballModel.modelName = assets::Models::Models$Ball$fbx;
            auto &ballRigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(ball);
            ballRigidBody.shapeInfo = Shapes::Sphere{};
            ballRigidBody.shape = Shapes::sphere;
            engine::Graphics::ModelUtils::SetShader(ballModel, untexturedShader);

            auto ballPickUp = CreateEntity();
            auto &ballPickUpRigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(ballPickUp);
            ballPickUpRigidBody.shapeInfo = Shapes::Sphere{};
            ballPickUpRigidBody.shape = Shapes::sphere;
            ballPickUpRigidBody.isTrigger = true;
            engine::Graphics::TransformationUtils::AddChildEntity(ball, ballPickUp);

            //auto testText = CreateEntity();
            //auto &text = engine::Ecs::Registry::AddComponent<engine::Graphics::Text>(testText);
            //text.fontName = assets::Fonts::fonts$RobotoRegular$ttf;
            //text.content = "Test";
            //auto &textTransform = engine::Ecs::Registry::AddComponent<engine::Graphics::Transform>(testText);
            //textTransform.scale = glm::vec3(10,10, 10);

            /*auto plane = CreateEntity();
            auto &planeTransform = registry.get<engine::Graphics::Components::Transform>(plane);
            engine::Graphics::Utils::TransformUtils::AddTranslation(planeTransform, glm::vec3(0., -5.0f, 0.));
            engine::Graphics::Utils::TransformUtils::AddRotation(planeTransform, glm::vec3(0., 0., 90.));
            auto &planeRigidBody = engine::Physics::Utils::RigidBodyUtils::AddRigidStatic(*this, plane);*/


            /*auto test1 = CreateEntity();
            auto &model1 = registry.emplace<engine::Graphics::Components::Model>(test1);
            engine::Graphics::Utils::ModelUtils::SetPath(model1, "../../assets/SpaceShip/ScreenBottomMiddle.obj");
            auto test2 = CreateEntity();
            auto &model2 = registry.emplace<engine::Graphics::Components::Model>(test2);
            engine::Graphics::Utils::ModelUtils::SetPath(model2, "../../assets/SpaceShip/ScreenMiddleLeft.obj");
            auto test3 = CreateEntity();
            auto &model3 = registry.emplace<engine::Graphics::Components::Model>(test3);
            engine::Graphics::Utils::ModelUtils::SetPath(model3, "../../assets/SpaceShip/ScreenTopRight.obj");*/

            /*engine::Graphics::Utils::ModelUtils::SetShader(model1, untexturedShader);
            engine::Graphics::Utils::ModelUtils::SetShader(model2, untexturedShader);
            engine::Graphics::Utils::ModelUtils::SetShader(model3, untexturedShader);*/

            /*auto &transform = registry.get<engine::Graphics::Components::Transform>(test);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test1);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test2);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test3);*/


            auto enemy = CreateEntity();
            auto &enemyModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(enemy);
            enemyModel.modelName = assets::Models::SpaceShip1$obj;
            engine::Graphics::ModelUtils::SetShader(enemyModel, shader);
            auto &enemyTransform = registry.get<engine::Graphics::Transform>(enemy);
            engine::Graphics::TransformationUtils::SetTranslation(enemy, enemyTransform, glm::vec3(0, 3, 24));
            engine::Graphics::TransformationUtils::SetScale(enemy, enemyTransform, glm::vec3(0.5f, 0.5f, 0.5f));
            registry.emplace<EnemyBehaviour>(enemy);
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
