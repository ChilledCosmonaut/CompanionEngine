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
        void onSetup(){
            auto& registry = engine::Ecs::Registry::getCurrent();
            auto fileManager = engine::filesystem::FileManager::GetFileManager();

            auto mainCameraObject = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Camera>(mainCameraObject);
            engine::Ecs::Registry::AddComponent<ShipMovementSettings>(mainCameraObject);

            auto &cameraTransform = registry.get<engine::Graphics::Transform>(mainCameraObject);
            engine::Graphics::TransformationUtils::AddRotation(mainCameraObject, cameraTransform, glm::vec3(0, 180, 0));
            auto &rigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(mainCameraObject);
            rigidBody.shapeInfo = Shapes::Sphere();
            rigidBody.shape = Shapes::sphere;

            auto skybox = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Skybox>(skybox);

            auto test = CreateEntity();
            auto &model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(test);
            model.modelName = assets::Models::SpaceShip$MainFrame$obj;

            auto &testTransform = registry.get<engine::Graphics::Transform>(test);

            engine::Graphics::TransformationUtils::AddChildEntity(cameraTransform, mainCameraObject, test);

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
            auto shader = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$fragmentShader$glsl)/*std::make_shared<engine::Graphics::shader>(assets::shaders$vertexShader$glsl, assets::shaders$fragmentShader$glsl)*/;
            auto untexturedShader = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$untexturedFragmentShader$glsl);
            auto unlitShader = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$lightFragmentShader$glsl);
            engine::Graphics::ModelUtils::SetShader(model, untexturedShader);
            /*engine::Graphics::Utils::ModelUtils::SetShader(model1, untexturedShader);
            engine::Graphics::Utils::ModelUtils::SetShader(model2, untexturedShader);
            engine::Graphics::Utils::ModelUtils::SetShader(model3, untexturedShader);*/

            /*auto &transform = registry.get<engine::Graphics::Components::Transform>(test);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test1);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test2);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test3);*/

            auto asteroid = CreateEntity();
            auto &asteroidModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroid);
            asteroidModel.modelName = assets::Models::asteriod1$obj;
            engine::Graphics::ModelUtils::SetShader(asteroidModel, shader);
            auto &asteroidTransform = registry.get<engine::Graphics::Transform>(asteroid);
            engine::Graphics::TransformationUtils::SetTranslation(asteroid, asteroidTransform, glm::vec3(-5, 3, 14));
            engine::Graphics::TransformationUtils::SetScale(asteroid, asteroidTransform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid1 = CreateEntity();
            auto &asteroid1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroid1);
            asteroid1Model.modelName = assets::Models::Asteroid2$obj;
            engine::Graphics::ModelUtils::SetShader(asteroid1Model, shader);
            auto &asteroid1Transform = registry.get<engine::Graphics::Transform>(asteroid1);
            engine::Graphics::TransformationUtils::SetTranslation(asteroid1, asteroid1Transform, glm::vec3(0, 12, 5));
            engine::Graphics::TransformationUtils::SetScale(asteroid1, asteroid1Transform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid2 = CreateEntity();
            auto &asteroid2Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroid2);
            asteroid2Model.modelName = assets::Models::asteriod1$obj;
            engine::Graphics::ModelUtils::SetShader(asteroid2Model, shader);
            auto &asteroid2Transform = registry.get<engine::Graphics::Transform>(asteroid2);
            engine::Graphics::TransformationUtils::SetTranslation(asteroid2, asteroid2Transform, glm::vec3(20, -10, 0));
            engine::Graphics::TransformationUtils::SetScale(asteroid2, asteroid2Transform, glm::vec3(0.5f, 0.5f, 0.5f));
            auto &audioSource = engine::Ecs::Registry::AddComponent<engine::soundSystem::SpatialAudioSource>(asteroid2);
            audioSource.fileName = "../../assets/audio/ambientSpace4.wav";

            auto asteroid3 = CreateEntity();
            auto &asteroid3Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroid3);
            asteroid3Model.modelName = assets::Models::Asteroid2$obj;
            engine::Graphics::ModelUtils::SetShader(asteroid3Model, shader);
            auto &asteroid3Transform = registry.get<engine::Graphics::Transform>(asteroid3);
            engine::Graphics::TransformationUtils::SetTranslation(asteroid3, asteroid3Transform, glm::vec3(0, 3, 24));
            engine::Graphics::TransformationUtils::SetScale(asteroid3, asteroid3Transform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid4 = CreateEntity();
            auto &asteroid4Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroid4);
            asteroid4Model.modelName = assets::Models::asteriod1$obj;
            engine::Graphics::ModelUtils::SetShader(asteroid4Model, shader);
            auto &asteroid4Transform = registry.get<engine::Graphics::Transform>(asteroid4);
            engine::Graphics::TransformationUtils::SetTranslation(asteroid4, asteroid4Transform, glm::vec3(15, -10, 5));
            engine::Graphics::TransformationUtils::SetScale(asteroid4, asteroid4Transform, glm::vec3(1.5f, 1.5f, 1.5f));

            auto asteroid5 = CreateEntity();
            auto &asteroid5Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroid5);
            asteroid5Model.modelName = assets::Models::Asteroid2$obj;
            engine::Graphics::ModelUtils::SetShader(asteroid5Model, shader);
            auto &asteroid5Transform = registry.get<engine::Graphics::Transform>(asteroid5);
            engine::Graphics::TransformationUtils::SetTranslation(asteroid5, asteroid5Transform, glm::vec3(5, 20, 30));
            engine::Graphics::TransformationUtils::SetScale(asteroid5, asteroid5Transform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid6 = CreateEntity();
            auto &asteroid6Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroid6);
            asteroid6Model.modelName = assets::Models::asteriod1$obj;
            engine::Graphics::ModelUtils::SetShader(asteroid6Model, shader);
            auto &asteroid6Transform = registry.get<engine::Graphics::Transform>(asteroid6);
            engine::Graphics::TransformationUtils::SetTranslation(asteroid6, asteroid6Transform, glm::vec3(-20, 10, 10));
            engine::Graphics::TransformationUtils::SetScale(asteroid6, asteroid6Transform, glm::vec3(2.0f, 2.0f, 2.0f));

            auto enemy = CreateEntity();
            auto &enemyModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(enemy);
            enemyModel.modelName = assets::Models::SpaceShip1$obj;
            engine::Graphics::ModelUtils::SetShader(enemyModel, shader);
            auto &enemyTransform = registry.get<engine::Graphics::Transform>(enemy);
            engine::Graphics::TransformationUtils::SetTranslation(enemy, enemyTransform, glm::vec3(0, 3, 24));
            engine::Graphics::TransformationUtils::SetScale(enemy, enemyTransform, glm::vec3(0.5f, 0.5f, 0.5f));
            registry.emplace<EnemyBehaviour>(enemy);

            auto enemy1 = CreateEntity();
            auto &enemy1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(enemy1);
            enemy1Model.modelName = assets::Models::SpaceShip2$obj;
            engine::Graphics::ModelUtils::SetShader(enemy1Model, shader);
            auto &enemy1Transform = registry.get<engine::Graphics::Transform>(enemy1);
            engine::Graphics::TransformationUtils::SetTranslation(enemy1, enemy1Transform, glm::vec3(20, -10, 0));
            engine::Graphics::TransformationUtils::SetScale(enemy1, enemy1Transform, glm::vec3(0.5f, 0.5f, 0.5f));
            registry.emplace<EnemyBehaviour>(enemy1);

            auto enemy2 = CreateEntity();
            auto &enemy2Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(enemy2);
            enemy2Model.modelName = assets::Models::SpaceShip3$obj;
            engine::Graphics::ModelUtils::SetShader(enemy2Model, shader);
            auto &enemy2Transform = registry.get<engine::Graphics::Transform>(enemy2);
            engine::Graphics::TransformationUtils::SetTranslation(enemy2, enemy2Transform, glm::vec3(0, 12, 5));
            engine::Graphics::TransformationUtils::SetScale(enemy2, enemy2Transform, glm::vec3(0.5f, 0.5f, 0.5f));
            registry.emplace<EnemyBehaviour>(enemy2);

            auto laserPlayer = CreateEntity();
            auto &laserPlayerModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(laserPlayer);
            laserPlayerModel.modelName = assets::Models::LaserPlayer$obj;
            engine::Graphics::ModelUtils::SetShader(laserPlayerModel, unlitShader);
            auto &laserPlayerTransform = registry.get<engine::Graphics::Transform>(laserPlayer);
            laserPlayerTransform.active = false;
            registry.emplace<PlayerProjectile>(laserPlayer);

            auto laserEnemy = CreateEntity();
            auto &laserEnemyModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(laserEnemy);
            laserEnemyModel.modelName = assets::Models::LaserPlayer$obj;
            engine::Graphics::ModelUtils::SetShader(laserEnemyModel, unlitShader);
            auto &laserEnemyTransform = registry.get<engine::Graphics::Transform>(laserEnemy);
            laserEnemyTransform.active = false;
            registry.emplace<EnemyProjectile>(laserEnemy);

            auto laserEnemy1 = CreateEntity();
            auto &laserEnemyModel1 = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(laserEnemy1);
            laserEnemyModel1.modelName = assets::Models::LaserPlayer$obj;
            engine::Graphics::ModelUtils::SetShader(laserEnemyModel1, unlitShader);
            auto &laserEnemyTransform1 = registry.get<engine::Graphics::Transform>(laserEnemy1);
            laserEnemyTransform1.active = false;
            registry.emplace<EnemyProjectile>(laserEnemy1);

            auto laserEnemy2 = CreateEntity();
            auto &laserEnemyModel2 = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(laserEnemy2);
            laserEnemyModel2.modelName = assets::Models::LaserPlayer$obj;
            engine::Graphics::ModelUtils::SetShader(laserEnemyModel2, unlitShader);
            auto &laserEnemyTransform2 = registry.get<engine::Graphics::Transform>(laserEnemy2);
            laserEnemyTransform2.active = false;
            registry.emplace<EnemyProjectile>(laserEnemy2);
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
