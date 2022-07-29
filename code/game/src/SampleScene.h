#pragma once

#include "engine/GraphicsEngine/Scene.h"
#include "engine/SoundSystem/AudioSourceUtils.h"
#include "engine/GraphicsEngine/Utils/TransformUtils.h"
#include "engine/GraphicsEngine/Utils/ModelUtils.h"
#include "EnemyBehavourSettings.h"

namespace gl3::game {

    class SampleScene : public engine::Graphics::Scene {
    public:
        void onSetup(){
            AddMainCamera();
            registry.emplace<ShipMovementSettings>(mainCameraObject);

            AddSkybox();

            auto test = CreateEntity();
            auto &model = registry.emplace<engine::Graphics::Components::Model>(test);
            engine::Graphics::Utils::ModelUtils::SetPath(model, "../../assets/SpaceShip/MainFrame.obj");
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

            auto &cameraTransform = registry.get<engine::Graphics::Components::Transform>(mainCameraObject);
            engine::Graphics::Utils::TransformUtils::AddChildEntity(cameraTransform, mainCameraObject, test);

            auto &audioSource = registry.emplace<engine::soundSystem::AudioSource>(test);
            engine::soundSystem::AudioSourceUtils::SetupAudioSource(audioSource, "../../assets/audio/electronic-wave.mp3");

            auto asteroid = CreateEntity();
            auto &asteroidModel = registry.emplace<engine::Graphics::Components::Model>(asteroid);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroidModel, "../../assets/asteriod1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroidModel, shader);
            auto &asteroidTransform = registry.get<engine::Graphics::Components::Transform>(asteroid);
            engine::Graphics::Utils::TransformUtils::SetTranslation(asteroidTransform, glm::vec3(-5,3,14));
            engine::Graphics::Utils::TransformUtils::SetScale(asteroidTransform, glm::vec3(0.5f,0.5f,0.5f));

            auto asteroid1 = CreateEntity();
            auto &asteroid1Model = registry.emplace<engine::Graphics::Components::Model>(asteroid1);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid1Model, "../../assets/Asteroid2.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid1Model, shader);
            auto &asteroid1Transform = registry.get<engine::Graphics::Components::Transform>(asteroid1);
            engine::Graphics::Utils::TransformUtils::SetTranslation(asteroid1Transform, glm::vec3(0,12,5));
            engine::Graphics::Utils::TransformUtils::SetScale(asteroid1Transform, glm::vec3(0.5f,0.5f,0.5f));

            auto asteroid2 = CreateEntity();
            auto &asteroid2Model = registry.emplace<engine::Graphics::Components::Model>(asteroid2);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid2Model, "../../assets/Asteroid1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid2Model, shader);
            auto &asteroid2Transform = registry.get<engine::Graphics::Components::Transform>(asteroid2);
            engine::Graphics::Utils::TransformUtils::SetTranslation(asteroid2Transform, glm::vec3(20,-10,0));
            engine::Graphics::Utils::TransformUtils::SetScale(asteroid2Transform, glm::vec3(0.5f,0.5f,0.5f));


            auto asteroid3 = CreateEntity();
            auto &asteroid3Model = registry.emplace<engine::Graphics::Components::Model>(asteroid3);
            engine::Graphics::Utils::ModelUtils::SetPath(asteroid3Model, "../../assets/Asteroid2.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(asteroid3Model, shader);
            auto &asteroid3Transform = registry.get<engine::Graphics::Components::Transform>(asteroid3);
            engine::Graphics::Utils::TransformUtils::SetTranslation(asteroid3Transform, glm::vec3(0,3,24));
            engine::Graphics::Utils::TransformUtils::SetScale(asteroid3Transform, glm::vec3(0.5f,0.5f,0.5f));

            auto enemy = CreateEntity();
            auto &enemyModel = registry.emplace<engine::Graphics::Components::Model>(enemy);
            engine::Graphics::Utils::ModelUtils::SetPath(enemyModel, "../../assets/SpaceShip1.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(enemyModel, shader);
            auto &enemyTransform = registry.get<engine::Graphics::Components::Transform>(enemy);
            engine::Graphics::Utils::TransformUtils::SetTranslation(enemyTransform, glm::vec3(0,3,24));
            engine::Graphics::Utils::TransformUtils::SetScale(enemyTransform, glm::vec3(0.5f,0.5f,0.5f));
            registry.emplace<EnemyBehaviour>(enemy);

            auto enemy1 = CreateEntity();
            auto &enemy1Model = registry.emplace<engine::Graphics::Components::Model>(enemy1);
            engine::Graphics::Utils::ModelUtils::SetPath(enemy1Model, "../../assets/SpaceShip2.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(enemy1Model, shader);
            auto &enemy1Transform = registry.get<engine::Graphics::Components::Transform>(enemy1);
            engine::Graphics::Utils::TransformUtils::SetTranslation(enemy1Transform, glm::vec3(20,-10,0));
            engine::Graphics::Utils::TransformUtils::SetScale(enemy1Transform, glm::vec3(0.5f,0.5f,0.5f));
            registry.emplace<EnemyBehaviour>(enemy1);

            auto enemy2 = CreateEntity();
            auto &enemy2Model = registry.emplace<engine::Graphics::Components::Model>(enemy2);
            engine::Graphics::Utils::ModelUtils::SetPath(enemy2Model, "../../assets/SpaceShip3.obj");
            engine::Graphics::Utils::ModelUtils::SetShader(enemy2Model, shader);
            auto &enemy2Transform = registry.get<engine::Graphics::Components::Transform>(enemy2);
            engine::Graphics::Utils::TransformUtils::SetTranslation(enemy2Transform, glm::vec3(0,12,5));
            engine::Graphics::Utils::TransformUtils::SetScale(enemy2Transform, glm::vec3(0.5f,0.5f,0.5f));
            registry.emplace<EnemyBehaviour>(enemy2);

            auto laserPlayer = CreateEntity();
            auto &laserPlayerModel = registry.emplace<engine::Graphics::Components::Model>(laserPlayer);
            engine::Graphics::Utils::ModelUtils::SetPath(laserPlayerModel, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserPlayerModel, unlitShader);
            auto &laserPlayerTransform = registry.get<engine::Graphics::Components::Transform>(laserPlayer);
            engine::Graphics::Utils::TransformUtils::SetActive(laserPlayerTransform, false);
            registry.emplace<PlayerProjectile>(laserPlayer);

            auto laserEnemy = CreateEntity();
            auto &laserEnemyModel = registry.emplace<engine::Graphics::Components::Model>(laserEnemy);
            engine::Graphics::Utils::ModelUtils::SetPath(laserEnemyModel, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserEnemyModel, unlitShader);
            auto &laserEnemyTransform = registry.get<engine::Graphics::Components::Transform>(laserEnemy);
            engine::Graphics::Utils::TransformUtils::SetActive(laserEnemyTransform, false);
            registry.emplace<EnemyProjectile>(laserEnemy);

            auto laserEnemy1 = CreateEntity();
            auto &laserEnemyModel1 = registry.emplace<engine::Graphics::Components::Model>(laserEnemy1);
            engine::Graphics::Utils::ModelUtils::SetPath(laserEnemyModel1, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserEnemyModel1, unlitShader);
            auto &laserEnemyTransform1 = registry.get<engine::Graphics::Components::Transform>(laserEnemy1);
            engine::Graphics::Utils::TransformUtils::SetActive(laserEnemyTransform1, false);
            registry.emplace<EnemyProjectile>(laserEnemy1);

            auto laserEnemy2 = CreateEntity();
            auto &laserEnemyModel2 = registry.emplace<engine::Graphics::Components::Model>(laserEnemy2);
            engine::Graphics::Utils::ModelUtils::SetPath(laserEnemyModel2, "../../assets/Laser(Player).obj");
            engine::Graphics::Utils::ModelUtils::SetShader(laserEnemyModel2, unlitShader);
            auto &laserEnemyTransform2 = registry.get<engine::Graphics::Components::Transform>(laserEnemy2);
            engine::Graphics::Utils::TransformUtils::SetActive(laserEnemyTransform2, false);
            registry.emplace<EnemyProjectile>(laserEnemy2);
        }

    private:
        std::vector<entt::entity> Entities;
    };
}
