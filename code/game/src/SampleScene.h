#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"
#include "Components/EnemyBehavourSettings.h"
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

            /*auto goal1 = CreateEntity();
            auto &goal1Transform = registry.get<engine::Graphics::Transform>(goal1);
            goal1Transform.translation = glm::vec3(0,0,99);
            goal1Transform.scale = glm::vec3(10,5,1);
            auto &goal1Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(goal1);
            goal1Plane.shapeInfo = Shapes::Box{physx::PxVec3(10,5,1)};
            goal1Plane.shape = Shapes::box;
            goal1Plane.mass = 0;
            auto &goal1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(goal1);
            goal1Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(goal1Model, shader);
            engine::Ecs::Registry::AddComponent<Goal>(goal1);

            auto goal2 = CreateEntity();
            auto &goal2Transform = registry.get<engine::Graphics::Transform>(goal2);
            goal2Transform.translation = glm::vec3(0,0,-99);
            goal2Transform.scale = glm::vec3(10,5,1);
            auto &goal2Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(goal2);
            goal2Plane.shapeInfo = Shapes::Box{physx::PxVec3(10,5,1)};
            goal2Plane.shape = Shapes::box;
            goal2Plane.mass = 0;
            auto &goal2Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(goal2);
            goal2Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(goal2Model, shader);
            engine::Ecs::Registry::AddComponent<Goal>(goal2);

            auto levelBoundary1 = CreateEntity();
            auto &boundary1Transform = registry.get<engine::Graphics::Transform>(levelBoundary1);
            boundary1Transform.translation = glm::vec3(40,0,0);
            //boundary1Transform.scale = glm::vec3(1,50,100);
            auto &boundary1Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(levelBoundary1);
            boundary1Plane.shapeInfo = Shapes::Box{physx::PxVec3(1,50,100)};
            boundary1Plane.shape = Shapes::box;
            boundary1Plane.mass = 0;
            auto &boundary1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(levelBoundary1);
            boundary1Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(boundary1Model, shader);

            auto levelBoundary2 = CreateEntity();
            auto &boundary2Transform = registry.get<engine::Graphics::Transform>(levelBoundary2);
            boundary2Transform.translation = glm::vec3(-40,0,0);
            auto &boundary2Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(levelBoundary2);
            boundary2Plane.shapeInfo = Shapes::Box{physx::PxVec3(1,50,100)};
            boundary2Plane.shape = Shapes::box;
            boundary2Plane.mass = 0;
            auto &boundary2Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(levelBoundary2);
            boundary2Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(boundary2Model, shader);

            auto levelBoundary3 = CreateEntity();
            auto &boundary3Transform = registry.get<engine::Graphics::Transform>(levelBoundary3);
            boundary3Transform.translation = glm::vec3(0,51,0);
            auto &boundary3Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(levelBoundary3);
            boundary3Plane.shapeInfo = Shapes::Box{physx::PxVec3(41,1,101)};
            boundary3Plane.shape = Shapes::box;
            boundary3Plane.mass = 0;
            auto &boundary3Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(levelBoundary3);
            boundary3Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(boundary3Model, shader);

            auto levelBoundary4 = CreateEntity();
            auto &boundary4Transform = registry.get<engine::Graphics::Transform>(levelBoundary4);
            boundary4Transform.translation = glm::vec3(0,-51,0);
            auto &boundary4Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(levelBoundary4);
            boundary4Plane.shapeInfo = Shapes::Box{physx::PxVec3(41,1,101)};
            boundary4Plane.shape = Shapes::box;
            boundary4Plane.mass = 0;
            auto &boundary4Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(levelBoundary4);
            boundary4Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(boundary4Model, shader);

            auto levelBoundary5 = CreateEntity();
            auto &boundary5Transform = registry.get<engine::Graphics::Transform>(levelBoundary5);
            boundary5Transform.translation = glm::vec3(0,0,101);
            auto &boundary5Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(levelBoundary5);
            boundary5Plane.shapeInfo = Shapes::Box{physx::PxVec3(40,50,1)};
            boundary5Plane.shape = Shapes::box;
            boundary5Plane.mass = 0;
            auto &boundary5Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(levelBoundary5);
            boundary5Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(boundary5Model, shader);

            auto levelBoundary6 = CreateEntity();
            auto &boundary6Transform = registry.get<engine::Graphics::Transform>(levelBoundary6);
            boundary6Transform.translation = glm::vec3(0,0,-101);
            auto &boundary6Plane = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(levelBoundary6);
            boundary6Plane.shapeInfo = Shapes::Box{physx::PxVec3(40,50,1)};
            boundary6Plane.shape = Shapes::box;
            boundary6Plane.mass = 0;
            auto &boundary6Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(levelBoundary6);
            boundary6Model.modelName = assets::Models::Models$box$obj;
            engine::Graphics::ModelUtils::SetShader(boundary6Model, shader);*/

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
