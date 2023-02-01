#pragma once

#include "../Components/EnemyBehavourSettings.h"
#include "../Components/ShipMovementSettings.h"
#include "engine/ECS/System.h"
#include "engine/Time.h"
#include "engine/ECS/Registry.h"

namespace gl3::game {
    class ProjectileSystem : public engine::entityComponentSystem::System {
    public:
        ProjectileSystem() = default;

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override{
            /*auto& registry = engine::Ecs::Registry::getCurrent();
            auto enemyProjectileView = registry.view<EnemyProjectile, engine::Graphics::Transform>();
            for (auto &enemy: enemyProjectileView) {
                auto &enemyStats = enemyProjectileView.get<EnemyProjectile>(enemy);
                auto &transform = enemyProjectileView.get<engine::Graphics::Transform>(enemy);
                auto componentView = registry.view<ShipMovementSettings, engine::Graphics::Transform>();
                for (auto &player: componentView) {
                    auto& shipSettings = componentView.get<ShipMovementSettings>(player);
                    auto& playerTransform = componentView.get<engine::Graphics::Transform>(player);

                    if (glm::length(playerTransform.translation - transform.translation) <= 2 &&
                        transform.active){
                        shipSettings.life -= enemyStats.damage;
                        enemyStats.lifetime = 0;
                        transform.active = false;
                    } else {
                        enemyStats.lifetime -= engine::Time::GetDeltaTime();
                        engine::Graphics::TransformationUtils::AddRelativeTranslation(enemy, transform, glm::vec3(0, 0, -40) * engine::Time::GetDeltaTime());
                    }

                    if (enemyStats.lifetime <= 0){
                        enemyStats.lifetime = 0;
                        transform.active = false;
                    }
                }
            }

            auto playerProjectileView = registry.view<PlayerProjectile, engine::Graphics::Transform>();
            for (auto &player: playerProjectileView) {
                auto &projectileStats = playerProjectileView.get<PlayerProjectile>(player);
                auto &playerTransform = playerProjectileView.get<engine::Graphics::Transform>(player);
                auto componentView = registry.view<FighterBehaviour, engine::Graphics::Transform>();
                for (auto &enemy: componentView) {
                    auto& shipSettings = componentView.get<FighterBehaviour>(enemy);
                    auto& enemyTransform = componentView.get<engine::Graphics::Transform>(enemy);

                    if (glm::length(enemyTransform.translation - playerTransform.translation) <= 2 && playerTransform.active){
                        shipSettings.lifePoints -= projectileStats.damage;
                        std::cout<<shipSettings.lifePoints<<std::endl;
                        projectileStats.lifetime = 0;
                        playerTransform.active = false;
                    } else {
                        projectileStats.lifetime -= engine::Time::GetDeltaTime();
                        engine::Graphics::TransformationUtils::AddRelativeTranslation(player, playerTransform, glm::vec3(0, 0, -50) * engine::Time::GetDeltaTime());
                    }

                    if (projectileStats.lifetime <= 0){
                        projectileStats.lifetime = 0;
                        playerTransform.active = false;
                    }
                }
            }*/
        };

        void OnShutdown(engine::Game &engine) override {};
    };
}