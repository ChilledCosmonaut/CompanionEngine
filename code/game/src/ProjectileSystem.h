#pragma once

#include "EnemyBehavourSettings.h"
#include "ShipMovementSettings.h"
#include "engine/ECS/System.h"
#include "ProjectileInfo.h"
#include "engine/Time.h"

namespace gl3::game {
    class ProjectileSystem : public engine::entityComponentSystem::System {
    public:
        ProjectileSystem() = default;

        void OnSwitchingScenes(engine::Graphics::Scene &scene) override {}

        void OnDrawCall(engine::Graphics::Scene &scene) override {};

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override{
            auto registry = game.getCurrentScene()->getRegistry();
            auto enemyProjectileView = registry->view<EnemyProjectile, engine::Graphics::Components::Transform>();
            for (auto &enemy: enemyProjectileView) {
                auto &enemyStats = enemyProjectileView.get<EnemyProjectile>(enemy);
                auto &transform = enemyProjectileView.get<engine::Graphics::Components::Transform>(enemy);
                auto componentView = registry->view<ShipMovementSettings, engine::Graphics::Components::Transform>();
                for (auto &player: componentView) {
                    auto& shipSettings = componentView.get<ShipMovementSettings>(player);
                    auto& playerTransform = componentView.get<engine::Graphics::Components::Transform>(player);

                    if (glm::length(engine::Graphics::Utils::TransformUtils::GetTranslation(playerTransform) -
                                    engine::Graphics::Utils::TransformUtils::GetTranslation(transform)) <= 2 &&
                                    engine::Graphics::Utils::TransformUtils::IsActive(transform)){
                        shipSettings.life -= enemyStats.damage;
                        enemyStats.lifetime = 0;
                        engine::Graphics::Utils::TransformUtils::SetActive(transform, false);
                    } else {
                        enemyStats.lifetime -= engine::Time::GetDeltaTime();
                        engine::Graphics::Utils::TransformUtils::AddRelativeTranslation(transform, glm::vec3(0,0,-40) * engine::Time::GetDeltaTime());
                    }

                    if (enemyStats.lifetime <= 0){
                        enemyStats.lifetime = 0;
                        engine::Graphics::Utils::TransformUtils::SetActive(transform, false);
                    }
                }
            }

            auto playerProjectileView = registry->view<PlayerProjectile, engine::Graphics::Components::Transform>();
            for (auto &player: playerProjectileView) {
                auto &projectileStats = playerProjectileView.get<PlayerProjectile>(player);
                auto &playerTransform = playerProjectileView.get<engine::Graphics::Components::Transform>(player);
                auto componentView = registry->view<EnemyBehaviour, engine::Graphics::Components::Transform>();
                for (auto &enemy: componentView) {
                    auto& shipSettings = componentView.get<EnemyBehaviour>(enemy);
                    auto& enemyTransform = componentView.get<engine::Graphics::Components::Transform>(enemy);

                    if (glm::length(engine::Graphics::Utils::TransformUtils::GetTranslation(enemyTransform) -
                                    engine::Graphics::Utils::TransformUtils::GetTranslation(playerTransform)) <= 2 &&
                                    engine::Graphics::Utils::TransformUtils::IsActive(playerTransform)){
                        shipSettings.lifePoints -= projectileStats.damage;
                        std::cout<<shipSettings.lifePoints<<std::endl;
                        projectileStats.lifetime = 0;
                        engine::Graphics::Utils::TransformUtils::SetActive(playerTransform, false);
                    } else {
                        projectileStats.lifetime -= engine::Time::GetDeltaTime();
                        engine::Graphics::Utils::TransformUtils::AddRelativeTranslation(playerTransform, glm::vec3(0,0,-50) * engine::Time::GetDeltaTime());
                    }

                    if (projectileStats.lifetime <= 0){
                        projectileStats.lifetime = 0;
                        engine::Graphics::Utils::TransformUtils::SetActive(playerTransform, false);
                    }
                }
            }
        };

        void OnShutdown(engine::Game &engine) override {};
    };
}