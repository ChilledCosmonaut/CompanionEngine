#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"
#include "EnemyBehavourSettings.h"

namespace gl3::game {

    using namespace engine::Physics;

    class SampleScene : public engine::Scene {
    public:
        void onSetup(){
            auto& registry = engine::Ecs::Registry::getCurrent();

            auto mainCameraObject = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Components::CameraComponent>(mainCameraObject);
            engine::Ecs::Registry::AddComponent<ShipMovementSettings>(mainCameraObject);

            auto &cameraTransform = registry.get<engine::Graphics::Components::Transform>(mainCameraObject);
            engine::Graphics::Utils::TransformationUtils::AddRotation(mainCameraObject, cameraTransform, glm::vec3(0, 180, 0));
            auto &rigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::Components::RigidBody>(mainCameraObject);
            rigidBody.shapeInfo = Components::Shapes::Sphere();
            rigidBody.shape = Components::Shapes::sphere;

            auto skybox = CreateEntity();
            engine::Ecs::Registry::AddComponent<engine::Graphics::Components::SkyboxComponent>(skybox);

            auto test = CreateEntity();
            auto &model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(test);
            engine::Graphics::Utils::ModelUtils::SetPath(model, "../../assets/SpaceShip/MainFrame.obj");

            auto &testTransform = registry.get<engine::Graphics::Components::Transform>(test);

            engine::Graphics::Utils::TransformationUtils::AddChildEntity(cameraTransform, mainCameraObject, test);

            /*auto plane = CreateEntity();
            auto &planeTransform = registry.get<engine::Graphics::Components::Transform>(plane);
            engine::Graphics::Utils::TransformUtils::AddTranslation(planeTransform, glm::vec3(0., -5.0f, 0.));
            engine::Graphics::Utils::TransformUtils::AddRotation(planeTransform, glm::vec3(0., 0., 90.));
            auto &planeRigidBody = engine::Physics::Utils::RigidBodyUtils::AddRigidStatic(*this, plane);*/


            /*auto test1 = CreateEntity();
            auto &model1 = registry.emplace<engine::Graphics::Components::Model>(test1);
            engine::Graphics::Utils::ModelUtils::SetPath(model1, "../../assets/SpaceShip/Screen-Bottom-Middle.obj");
            auto test2 = CreateEntity();
            auto &model2 = registry.emplace<engine::Graphics::Components::Model>(test2);
            engine::Graphics::Utils::ModelUtils::SetPath(model2, "../../assets/SpaceShip/Screen-Middle-Left.obj");
            auto test3 = CreateEntity();
            auto &model3 = registry.emplace<engine::Graphics::Components::Model>(test3);
            engine::Graphics::Utils::ModelUtils::SetPath(model3, "../../assets/SpaceShip/Screen-Top-Right.obj");*/
            auto shader = std::make_shared<engine::Graphics::shader>("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
            auto untexturedShader = std::make_shared<engine::Graphics::shader>("shaders/vertexShader.glsl", "shaders/untexturedFragmentShader.glsl");
            auto unlitShader = std::make_shared<engine::Graphics::shader>("shaders/vertexShader.glsl", "shaders/lightFragmentShader.glsl");
            engine::Graphics::Utils::ModelUtils::SetShader(model, untexturedShader);
            /*engine::Graphics::Utils::ModelUtils::SetShader(model1, untexturedShader);
            engine::Graphics::Utils::ModelUtils::SetShader(model2, untexturedShader);
            engine::Graphics::Utils::ModelUtils::SetShader(model3, untexturedShader);*/

            /*auto &transform = registry.get<engine::Graphics::Components::Transform>(test);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test1);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test2);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(transform, test, test3);*/

            auto asteroid = CreateEntity();
            auto &asteroidModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(asteroid);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroidModel, "../../assets/asteriod1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroidModel, shader);
            auto &asteroidTransform = registry.get<engine::Graphics::Components::Transform>(asteroid);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(asteroid, asteroidTransform, glm::vec3(-5, 3, 14));
            engine::Graphics::Utils::TransformationUtils::SetScale(asteroid, asteroidTransform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid1 = CreateEntity();
            auto &asteroid1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(asteroid1);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid1Model, "../../assets/Asteroid2.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid1Model, shader);
            auto &asteroid1Transform = registry.get<engine::Graphics::Components::Transform>(asteroid1);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(asteroid1, asteroid1Transform, glm::vec3(0, 12, 5));
            engine::Graphics::Utils::TransformationUtils::SetScale(asteroid1, asteroid1Transform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid2 = CreateEntity();
            auto &asteroid2Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(asteroid2);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid2Model, "../../assets/Asteroid1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid2Model, shader);
            auto &asteroid2Transform = registry.get<engine::Graphics::Components::Transform>(asteroid2);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(asteroid2, asteroid2Transform, glm::vec3(20, -10, 0));
            engine::Graphics::Utils::TransformationUtils::SetScale(asteroid2, asteroid2Transform, glm::vec3(0.5f, 0.5f, 0.5f));
            auto &audioSource = engine::Ecs::Registry::AddComponent<engine::soundSystem::SpatialAudioSource>(asteroid2);
            audioSource.soundFilePath = "../../assets/audio/ambient-space-4.wav";

            auto asteroid3 = CreateEntity();
            auto &asteroid3Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(asteroid3);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid3Model, "../../assets/Asteroid2.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid3Model, shader);
            auto &asteroid3Transform = registry.get<engine::Graphics::Components::Transform>(asteroid3);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(asteroid3, asteroid3Transform, glm::vec3(0, 3, 24));
            engine::Graphics::Utils::TransformationUtils::SetScale(asteroid3, asteroid3Transform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid4 = CreateEntity();
            auto &asteroid4Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(asteroid4);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid4Model, "../../assets/asteriod1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid4Model, shader);
            auto &asteroid4Transform = registry.get<engine::Graphics::Components::Transform>(asteroid4);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(asteroid4, asteroid4Transform, glm::vec3(15, -10, 5));
            engine::Graphics::Utils::TransformationUtils::SetScale(asteroid4, asteroid4Transform, glm::vec3(1.5f, 1.5f, 1.5f));

            auto asteroid5 = CreateEntity();
            auto &asteroid5Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(asteroid5);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid5Model, "../../assets/Asteroid2.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid5Model, shader);
            auto &asteroid5Transform = registry.get<engine::Graphics::Components::Transform>(asteroid5);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(asteroid5, asteroid5Transform, glm::vec3(5, 20, 30));
            engine::Graphics::Utils::TransformationUtils::SetScale(asteroid5, asteroid5Transform, glm::vec3(0.5f, 0.5f, 0.5f));

            auto asteroid6 = CreateEntity();
            auto &asteroid6Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(asteroid6);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid6Model, "../../assets/Asteroid1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid6Model, shader);
            auto &asteroid6Transform = registry.get<engine::Graphics::Components::Transform>(asteroid6);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(asteroid6, asteroid6Transform, glm::vec3(-20, 10, 10));
            engine::Graphics::Utils::TransformationUtils::SetScale(asteroid6, asteroid6Transform, glm::vec3(2.0f, 2.0f, 2.0f));

            auto enemy = CreateEntity();
            auto &enemyModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(enemy);
            engine::Graphics::Utils::ModelUtils::SetPath(enemyModel, "../../assets/SpaceShip1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(enemyModel, shader);
            auto &enemyTransform = registry.get<engine::Graphics::Components::Transform>(enemy);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(enemy, enemyTransform, glm::vec3(0, 3, 24));
            engine::Graphics::Utils::TransformationUtils::SetScale(enemy, enemyTransform, glm::vec3(0.5f, 0.5f, 0.5f));
            registry.emplace<EnemyBehaviour>(enemy);

            auto enemy1 = CreateEntity();
            auto &enemy1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(enemy1);
            engine::Graphics::Utils::ModelUtils::SetPath(enemy1Model, "../../assets/SpaceShip2.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(enemy1Model, shader);
            auto &enemy1Transform = registry.get<engine::Graphics::Components::Transform>(enemy1);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(enemy1, enemy1Transform, glm::vec3(20, -10, 0));
            engine::Graphics::Utils::TransformationUtils::SetScale(enemy1, enemy1Transform, glm::vec3(0.5f, 0.5f, 0.5f));
            registry.emplace<EnemyBehaviour>(enemy1);

            auto enemy2 = CreateEntity();
            auto &enemy2Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(enemy2);
            engine::Graphics::Utils::ModelUtils::SetPath(enemy2Model, "../../assets/SpaceShip3.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(enemy2Model, shader);
            auto &enemy2Transform = registry.get<engine::Graphics::Components::Transform>(enemy2);
            engine::Graphics::Utils::TransformationUtils::SetTranslation(enemy2, enemy2Transform, glm::vec3(0, 12, 5));
            engine::Graphics::Utils::TransformationUtils::SetScale(enemy2, enemy2Transform, glm::vec3(0.5f, 0.5f, 0.5f));
            registry.emplace<EnemyBehaviour>(enemy2);

            auto laserPlayer = CreateEntity();
            auto &laserPlayerModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(laserPlayer);
            engine::Graphics::Utils::ModelUtils::SetPath(laserPlayerModel, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserPlayerModel, unlitShader);
            auto &laserPlayerTransform = registry.get<engine::Graphics::Components::Transform>(laserPlayer);
            laserPlayerTransform.active = false;
            registry.emplace<PlayerProjectile>(laserPlayer);

            auto laserEnemy = CreateEntity();
            auto &laserEnemyModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(laserEnemy);
            engine::Graphics::Utils::ModelUtils::SetPath(laserEnemyModel, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserEnemyModel, unlitShader);
            auto &laserEnemyTransform = registry.get<engine::Graphics::Components::Transform>(laserEnemy);
            laserEnemyTransform.active = false;
            registry.emplace<EnemyProjectile>(laserEnemy);

            auto laserEnemy1 = CreateEntity();
            auto &laserEnemyModel1 = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(laserEnemy1);
            engine::Graphics::Utils::ModelUtils::SetPath(laserEnemyModel1, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserEnemyModel1, unlitShader);
            auto &laserEnemyTransform1 = registry.get<engine::Graphics::Components::Transform>(laserEnemy1);
            laserEnemyTransform1.active = false;
            registry.emplace<EnemyProjectile>(laserEnemy1);

            auto laserEnemy2 = CreateEntity();
            auto &laserEnemyModel2 = engine::Ecs::Registry::AddComponent<engine::Graphics::Components::Model>(laserEnemy2);
            engine::Graphics::Utils::ModelUtils::SetPath(laserEnemyModel2, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserEnemyModel2, unlitShader);
            auto &laserEnemyTransform2 = registry.get<engine::Graphics::Components::Transform>(laserEnemy2);
            laserEnemyTransform2.active = false;
            registry.emplace<EnemyProjectile>(laserEnemy2);
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
