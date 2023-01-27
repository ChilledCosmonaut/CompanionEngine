#pragma once

#include <memory>
#include <random>

#include "engine/Systems/Graphics/shader.h"
#include "engine/ECS/Registry.h"
#include "engine/Systems/Graphics/Components/Material.h"
#include "engine/Systems/FileManager/FileManager.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"
#include "../Components/EnemyBehavourSettings.h"
#include "generated/Assets.h"
#include "../Components/AsteroidField.h"
#include "engine/Systems/Physics/Components/Shapes.h"

namespace gl3::game::Utils{
    class ModelCreationTemplates{
    public:

        static entt::entity CreateAsteroidBelt(engine::Scene *scene, int lowerBound, int upperBound, int asteroidRadius){
            auto &registry = Ecs::Registry::getCurrent();

            auto asteroidBelt = scene->CreateEntity();

            //Initial distribution calculations
            float beltSize = (glm::pi<float>() * pow(upperBound, 2)) - (glm::pi<float>() * pow(lowerBound, 2));
            float asteroidArea = glm::pi<float>() * pow(asteroidRadius, 2);
            auto asteroidCount = beltSize/ asteroidArea;

            std::random_device randDevPos;
            std::mt19937 posGenerator(randDevPos());
            std::uniform_int_distribution<int> posDistribution(lowerBound, upperBound);

            std::random_device randDevRot;
            std::mt19937 rotGenerator(randDevRot());
            std::uniform_int_distribution<int> rotDistribution(0, 360);

            std::random_device randDevScale;
            std::mt19937 scaleGenerator(randDevScale());
            std::uniform_int_distribution<int> scaleDistribution(1, 4);

            std::random_device randDevLateralOffset;
            std::mt19937 lateralOffsetGenerator(randDevLateralOffset());
            std::normal_distribution<> lateralOffsetDistribution(-7, 7);

            for (int asteroidIndex = 0; (float)asteroidIndex < asteroidCount; ++asteroidIndex) {
                entt::entity asteroid;
                int scaleFactor = scaleDistribution(scaleGenerator);

                switch (asteroidIndex%3) {
                    case 0:
                        asteroid = CreateAsteroidVariant1(scene);
                        break;
                    case 1:
                        asteroid = CreateAsteroidVariant2(scene);
                        break;
                    case 2:
                        asteroid = CreateAsteroidVariant3(scene);
                        break;
                }
                registry.emplace<AsteroidField>(asteroid);

                auto &transform = registry.get<Graphics::Transform>(asteroid);
                transform.translation = glm::quat(glm::radians(glm::vec3(0, rotDistribution(rotGenerator), 0))) * glm::vec3(posDistribution(posGenerator), lateralOffsetDistribution(lateralOffsetGenerator), 0);
                transform.scale = glm::vec3(1, 1, 1) * (float)scaleFactor;
                TransformationUtils::AddChildEntity(asteroidBelt, asteroid);

                auto &rigidBody = registry.get<engine::Physics::RigidBody>(asteroid);
                auto sphereInfo = engine::Physics::Shapes::Sphere{};
                sphereInfo.radius = (float)scaleFactor;
                rigidBody.shapeInfo = sphereInfo;
            }

            return asteroidBelt;
        }

        static entt::entity CreateSpaceStation(engine::Scene *scene){
            auto spaceStation = scene->CreateEntity();

            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module1$fbx, GetStationModule1Material(), glm::vec3(0,0,23.3432f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module3$fbx, GetStationModule3Material(), glm::vec3(0,0,21.721f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module4$fbx, GetStationModule4Material(), glm::vec3(0,0,19.5662f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module4$001$fbx, GetStationModule4Material(), glm::vec3(0,0,14.0546f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module5$fbx, GetStationModule5Material(), glm::vec3(0,0,7.14884f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module6$fbx, GetStationModule6Material(), glm::vec3(0,0,2.59261f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module7$fbx, GetStationModule7Material(), glm::vec3(0,0,0.191649f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module8$fbx, GetStationModule8Material(), glm::vec3(0,0,-6.71709f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module9$fbx, GetStationModule9Material(), glm::vec3(0,0,-7.88377f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module10$fbx, GetStationModule10Material(), glm::vec3(0,0,-13.4303f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module11$fbx, GetStationModule11Material(), glm::vec3(0,-5.52623,-13.4289f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module12$fbx, GetStationModule12Material(), glm::vec3(0,0,-19.2921f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module13$fbx, GetStationModule13Material(), glm::vec3(0,0,-19.451f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module14$fbx, GetStationModule14Material(), glm::vec3(0,0,-35.0941f));
            AddStationSubmodule(scene, spaceStation, assets::Models$SpaceStation$Module15$fbx, GetStationModule15Material(), glm::vec3(0,0,-35.7648f));

            return spaceStation;
        }

        static entt::entity CreateAsteroidVariant1(engine::Scene *scene){
            auto asteroidVariant1 = scene->CreateEntity();

            auto &asteroidVariant1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroidVariant1);
            asteroidVariant1Model.modelName = assets::Models::Models$Asteroids$asteroid1_LOD0$fbx;
            asteroidVariant1Model.material = *GetAsteroidMaterial();
            engine::Graphics::ModelUtils::SetShader(asteroidVariant1Model, GetTexturedShader());

            auto &rigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(asteroidVariant1);
            rigidBody.shapeInfo = engine::Physics::Shapes::Sphere{};
            rigidBody.shape = engine::Physics::Shapes::sphere;

            return asteroidVariant1;
        }

        static entt::entity CreateAsteroidVariant2(engine::Scene *scene){
            auto &registry = Ecs::Registry::getCurrent();

            auto asteroidVariant2 = scene->CreateEntity();

            auto &asteroidVariant2Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroidVariant2);
            asteroidVariant2Model.modelName = assets::Models::Models$Asteroids$asteroid2_LOD0$fbx;
            asteroidVariant2Model.material = *GetAsteroidMaterial();
            engine::Graphics::ModelUtils::SetShader(asteroidVariant2Model, GetTexturedShader());

            auto &rigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(asteroidVariant2);
            rigidBody.shapeInfo = engine::Physics::Shapes::Sphere{};
            rigidBody.shape = engine::Physics::Shapes::sphere;

            return asteroidVariant2;
        }

        static entt::entity CreateAsteroidVariant3(engine::Scene *scene){
            auto &registry = Ecs::Registry::getCurrent();

            auto asteroidVariant3 = scene->CreateEntity();

            auto &asteroidVariant3Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(asteroidVariant3);
            asteroidVariant3Model.modelName = assets::Models::Models$Asteroids$asteroid3_LOD0$fbx;
            asteroidVariant3Model.material = *GetAsteroidMaterial();
            engine::Graphics::ModelUtils::SetShader(asteroidVariant3Model, GetTexturedShader());

            auto &rigidBody = engine::Ecs::Registry::AddComponent<engine::Physics::RigidBody>(asteroidVariant3);
            rigidBody.shapeInfo = engine::Physics::Shapes::Sphere{};
            rigidBody.shape = engine::Physics::Shapes::sphere;

            return asteroidVariant3;
        }

        static entt::entity CreateEnemyVariant1(engine::Scene *scene){
            auto enemyVariant1 = scene->CreateEntity();

            auto &enemyVariant1Model = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(enemyVariant1);
            enemyVariant1Model.modelName = assets::Models::Models$SpaceShips$StarSparrow1$fbx;
            enemyVariant1Model.material = *GetStarSparrowMaterial();
            engine::Graphics::ModelUtils::SetShader(enemyVariant1Model, GetTexturedShader());

            //registry.emplace<EnemyBehaviour>(carrierEnemy);

            return enemyVariant1;
        }

        static entt::entity CreateCarrier(engine::Scene *scene){
            auto carrierEnemy = scene->CreateEntity();

            auto &carrierEnemyModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(carrierEnemy);
            carrierEnemyModel.modelName = assets::Models::Models$SpaceShips$CarrierCombined$fbx;
            carrierEnemyModel.material = *GetCarrierMaterial();
            engine::Graphics::ModelUtils::SetShader(carrierEnemyModel, GetTexturedShader());

            //registry.emplace<EnemyBehaviour>(carrierEnemy);

            return carrierEnemy;
        }

        static entt::entity CreatePlayer(engine::Scene *scene){
            auto playerShip = scene->CreateEntity();

            auto &playerModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(playerShip);
            playerModel.modelName = assets::Models::SpaceShip$MainFrame$obj;
            engine::Graphics::ModelUtils::SetShader(playerModel, GetUntexturedShader());

            return playerShip;
        }

    private:
        static std::shared_ptr<engine::Graphics::shader> GetTexturedShader(){
            if(texturedShader == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                texturedShader  = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$fragmentShader$glsl);
            }
            return texturedShader;
        }

        static std::shared_ptr<engine::Graphics::shader> GetUntexturedShader(){
            if(untexturedShader == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                untexturedShader = fileManager->getAsset(assets::shaders$vertexShader$glsl, assets::shaders$untexturedFragmentShader$glsl);
            }
            return untexturedShader;
        }

        static void AddStationSubmodule(engine::Scene *scene, entt::entity spaceStation, assets::Models subModuleName, const std::shared_ptr<engine::Graphics::Material>& subModelMaterial, glm::vec3 offset){
            auto subModule = scene->CreateEntity();

            auto& registry = engine::Ecs::Registry::getCurrent();

            auto &subModuleModel = engine::Ecs::Registry::AddComponent<engine::Graphics::Model>(subModule);
            subModuleModel.modelName = subModuleName;
            subModuleModel.material = *subModelMaterial;
            engine::Graphics::ModelUtils::SetShader(subModuleModel, GetTexturedShader());

            auto &transform = registry.get<Graphics::Transform>(subModule);
            transform.translation = offset;

            engine::Graphics::TransformationUtils::AddChildEntity(spaceStation, subModule);
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule1Material(){
            if(stationModule1Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule1Material = std::make_shared<engine::Graphics::Material>();

                stationModule1Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module1_AlbedoTransparency$tga);
                stationModule1Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module1_AlbedoTransparency$tga);
                stationModule1Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module1_MetallicSmoothness$tga);
                stationModule1Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module1_Normal$tga);
            }
            return stationModule1Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule3Material(){
            if(stationModule3Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule3Material = std::make_shared<engine::Graphics::Material>();

                stationModule3Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module3_AlbedoTransparency$tga);
                stationModule3Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module3_AlbedoTransparency$tga);
                stationModule3Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module3_MetallicSmoothness$tga);
                stationModule3Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module3_Normal$tga);
            }
            return stationModule3Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule4Material(){
            if(stationModule4Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule4Material = std::make_shared<engine::Graphics::Material>();

                stationModule4Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module4_AlbedoTransparency$tga);
                stationModule4Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module4_AlbedoTransparency$tga);
                stationModule4Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module4_MetallicSmoothness$tga);
                stationModule4Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module4_Normal$tga);
            }
            return stationModule4Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule5Material(){
            if(stationModule5Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule5Material = std::make_shared<engine::Graphics::Material>();

                stationModule5Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module5_AlbedoTransparency$tga);
                stationModule5Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module5_AlbedoTransparency$tga);
                stationModule5Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module5_MetallicSmoothness$tga);
                stationModule5Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module5_Normal$tga);
            }
            return stationModule5Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule6Material(){
            if(stationModule6Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule6Material = std::make_shared<engine::Graphics::Material>();

                stationModule6Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module6_AlbedoTransparency$tga);
                stationModule6Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module6_AlbedoTransparency$tga);
                stationModule6Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module6_MetallicSmoothness$tga);
                stationModule6Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module6_Normal$tga);
            }
            return stationModule6Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule7Material(){
            if(stationModule7Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule7Material = std::make_shared<engine::Graphics::Material>();

                stationModule7Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module7_AlbedoTransparency$tga);
                stationModule7Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module7_AlbedoTransparency$tga);
                stationModule7Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module7_MetallicSmoothness$tga);
                stationModule7Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module7_Normal$tga);
            }
            return stationModule7Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule8Material(){
            if(stationModule8Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule8Material = std::make_shared<engine::Graphics::Material>();

                stationModule8Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module8_AlbedoTransparency$tga);
                stationModule8Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module8_AlbedoTransparency$tga);
                stationModule8Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module8_MetallicSmoothness$tga);
                stationModule8Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module8_Normal$tga);
            }
            return stationModule8Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule9Material(){
            if(stationModule9Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule9Material = std::make_shared<engine::Graphics::Material>();

                stationModule9Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module9_AlbedoTransparency$tga);
                stationModule9Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module9_AlbedoTransparency$tga);
                stationModule9Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module9_MetallicSmoothness$tga);
                stationModule9Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module9_Normal$tga);
            }
            return stationModule9Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule10Material(){
            if(stationModule10Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule10Material = std::make_shared<engine::Graphics::Material>();

                stationModule10Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module10_AlbedoTransparency$tga);
                stationModule10Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module10_AlbedoTransparency$tga);
                stationModule10Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module10_MetallicSmoothness$tga);
                stationModule10Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module10_Normal$tga);
            }
            return stationModule10Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule11Material(){
            if(stationModule11Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule11Material = std::make_shared<engine::Graphics::Material>();

                stationModule11Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module11_AlbedoTransparency$tga);
                stationModule11Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module11_AlbedoTransparency$tga);
                stationModule11Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module11_MetallicSmoothness$tga);
                stationModule11Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module11_Normal$tga);
            }
            return stationModule11Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule12Material(){
            if(stationModule12Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule12Material = std::make_shared<engine::Graphics::Material>();

                stationModule12Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module12_AlbedoTransparency$tga);
                stationModule12Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module12_AlbedoTransparency$tga);
                stationModule12Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module12_MetallicSmoothness$tga);
                stationModule12Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module12_Normal$tga);
            }
            return stationModule12Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule13Material(){
            if(stationModule13Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule13Material = std::make_shared<engine::Graphics::Material>();

                stationModule13Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module13_AlbedoTransparency$tga);
                stationModule13Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module13_AlbedoTransparency$tga);
                stationModule13Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module13_MetallicSmoothness$tga);
                stationModule13Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module13_Normal$tga);
            }
            return stationModule13Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule14Material(){
            if(stationModule14Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule14Material = std::make_shared<engine::Graphics::Material>();

                stationModule14Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module14_AlbedoTransparency$tga);
                stationModule14Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module14_AlbedoTransparency$tga);
                stationModule14Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module14_MetallicSmoothness$tga);
                stationModule14Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module14_Normal$tga);
            }
            return stationModule14Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStationModule15Material(){
            if(stationModule15Material == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                stationModule15Material = std::make_shared<engine::Graphics::Material>();

                stationModule15Material->ambient  = fileManager->getAsset(assets::Images::textures$SpaceStation$module15_AlbedoTransparency$tga);
                stationModule15Material->diffuse  = fileManager->getAsset(assets::Images::textures$SpaceStation$module15_AlbedoTransparency$tga);
                stationModule15Material->specular = fileManager->getAsset(assets::Images::textures$SpaceStation$module15_MetallicSmoothness$tga);
                stationModule15Material->normal   = fileManager->getAsset(assets::Images::textures$SpaceStation$module15_Normal$tga);
            }
            return stationModule15Material;
        }

        static std::shared_ptr<engine::Graphics::Material> GetCarrierMaterial(){
            if(carrierMaterial == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                carrierMaterial = std::make_shared<engine::Graphics::Material>();

                carrierMaterial->ambient  = fileManager->getAsset(assets::Images::textures$Carrier$CarrierRedAlbedo$png);
                carrierMaterial->diffuse  = fileManager->getAsset(assets::Images::textures$Carrier$CarrierRedAlbedo$png);
                carrierMaterial->specular = fileManager->getAsset(assets::Images::textures$Carrier$LitzmannClassGunCarrierPBRSpecular$png);
                carrierMaterial->normal   = fileManager->getAsset(assets::Images::textures$Carrier$LitzmannClassGunCarrierNormal$png);
            }
            return carrierMaterial;
        }

        static std::shared_ptr<engine::Graphics::Material> GetStarSparrowMaterial(){
            if(starSparrowMaterial == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                starSparrowMaterial = std::make_shared<engine::Graphics::Material>();

                starSparrowMaterial->ambient  = fileManager->getAsset(assets::Images::textures$EnemyVariant$StarSparrow_Red$png);
                starSparrowMaterial->diffuse  = fileManager->getAsset(assets::Images::textures$EnemyVariant$StarSparrow_Red$png);
                starSparrowMaterial->specular = fileManager->getAsset(assets::Images::textures$EnemyVariant$StarSparrow_MetallicSmoothness$png);
                starSparrowMaterial->normal   = fileManager->getAsset(assets::Images::textures$EnemyVariant$StarSparrow_Normal$png);
            }
            return starSparrowMaterial;
        }

        static std::shared_ptr<engine::Graphics::Material> GetAsteroidMaterial(){
            if(asteroidMaterial == nullptr){
                auto fileManager = engine::filesystem::FileManager::GetFileManager();
                asteroidMaterial = std::make_shared<engine::Graphics::Material>();

                asteroidMaterial->ambient  = fileManager->getAsset(assets::Images::textures$Asteroids$seamless_rock_texture$jpg);
                asteroidMaterial->diffuse  = fileManager->getAsset(assets::Images::textures$Asteroids$seamless_rock_texture$jpg);
                asteroidMaterial->specular = fileManager->getAsset(assets::Images::textures$Asteroids$seamless_rock_texture$jpg);
                asteroidMaterial->normal   = fileManager->getAsset(assets::Images::textures$Asteroids$seamless_rock_texture_detail$jpg);
            }
            return asteroidMaterial;
        }

        inline static std::shared_ptr<engine::Graphics::shader> texturedShader = nullptr;
        inline static std::shared_ptr<engine::Graphics::shader> untexturedShader = nullptr;

        inline static std::shared_ptr<engine::Graphics::Material> carrierMaterial = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> starSparrowMaterial = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> asteroidMaterial = nullptr;

        inline static std::shared_ptr<engine::Graphics::Material> stationModule1Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule3Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule4Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule5Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule6Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule7Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule8Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule9Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule10Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule11Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule12Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule13Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule14Material = nullptr;
        inline static std::shared_ptr<engine::Graphics::Material> stationModule15Material = nullptr;
    };
}