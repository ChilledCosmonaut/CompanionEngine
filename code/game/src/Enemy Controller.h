#pragma once

#include "engine/ECS/System.h"
#include "ShipController.h"
#include "EnemyBehavourSettings.h"

namespace gl3::game {
    class EnemyController : public engine::entityComponentSystem::System {
    public:
        EnemyController() = default;

        void OnSwitchingScenes(engine::Graphics::Scene &scene) override {}

        void OnDrawCall(engine::Graphics::Scene &scene) override {};

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override {
            auto registry = game.getCurrentScene()->getRegistry();
            auto enemyView = registry->view<EnemyBehaviour, engine::Graphics::Components::Transform>();
            for (auto &enemy: enemyView) {
                auto &enemyStats = enemyView.get<EnemyBehaviour>(enemy);
                auto &transform = enemyView.get<engine::Graphics::Components::Transform>(enemy);
                auto componentView = registry->view<ShipMovementSettings, engine::Graphics::Components::Transform>();

                if (enemyStats.lifePoints <= 0){
                    engine::Graphics::Utils::TransformUtils::SetActive(transform, false);
                    return;
                }

                for (auto &entity: componentView) {
                    auto &targetTransform = componentView.get<engine::Graphics::Components::Transform>(entity);
                    if (glm::length(engine::Graphics::Utils::TransformUtils::GetTranslation(transform) -
                                    engine::Graphics::Utils::TransformUtils::GetTranslation(targetTransform)) <= 100) {

                        bool shoot = rand() % 300;

                        if (shoot < 1){
                            auto projectileView = registry->view<EnemyProjectile, engine::Graphics::Components::Transform>();

                            for (auto& projectileEntity : projectileView) {
                                auto& projectile = projectileView.get<EnemyProjectile>(projectileEntity);
                                auto& projectileTransform = projectileView.get<engine::Graphics::Components::Transform>(projectileEntity);

                                if (projectile.lifetime <= 0){
                                    engine::Graphics::Utils::TransformUtils::SetActive(projectileTransform, true);
                                    engine::Graphics::Utils::TransformUtils::SetTranslation(projectileTransform, engine::Graphics::Utils::TransformUtils::GetTranslation(transform));
                                    engine::Graphics::Utils::TransformUtils::SetRotation(projectileTransform, engine::Graphics::Utils::TransformUtils::GetQuatRotation(transform));
                                    projectile.lifetime = 3;
                                }
                            }
                        }

                        auto targetRotation = glm::toQuat(
                                glm::inverse(
                                        glm::lookAt(
                                                engine::Graphics::Utils::TransformUtils::GetTranslation(targetTransform),
                                                engine::Graphics::Utils::TransformUtils::GetTranslation(transform),
                                                glm::vec3(0, 1, 0)))) * glm::quat(glm::radians(glm::vec3(0, 180, 0)));
                        glm::quat newRotation = glm::mix(
                                engine::Graphics::Utils::TransformUtils::GetQuatRotation(transform), targetRotation,
                                0.5f * gl3::engine::Time::GetDeltaTime());

                        engine::Graphics::Utils::TransformUtils::SetRotation(transform, newRotation);
                        if(std::fabs(glm::angle(newRotation)-glm::angle(engine::Graphics::Utils::TransformUtils::GetQuatRotation(transform))) <= 0.7f)
                            engine::Graphics::Utils::TransformUtils::AddRelativeTranslation(transform, glm::vec3(0,0,-2) * gl3::engine::Time::GetDeltaTime());
                        break;
                    }
                }
            }
        };

        void OnShutdown(engine::Game &engine) override {};
    };
}
