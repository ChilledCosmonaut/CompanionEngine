#include "EnemyController.h"

namespace gl3::game {

    void EnemyController::Update(engine::Game &game) {
        auto &registry = engine::Ecs::Registry::getCurrent();
        auto enemyView = registry.view<EnemyBehaviour, engine::Graphics::Transform>();
        for (auto &enemy: enemyView) {
            auto &enemyStats = enemyView.get<EnemyBehaviour>(enemy);
            auto &transform = enemyView.get<engine::Graphics::Transform>(enemy);
            auto componentView = registry.view<ShipMovementSettings, engine::Graphics::Transform>();

            for (auto &entity: componentView) {
                auto &targetTransform = componentView.get<engine::Graphics::Transform>(entity);

                glm::quat targetRotation = FindRotation(transform, targetTransform);
                float speed = FindSpeedAmplitude(transform, targetTransform, targetRotation);
                Attack(transform, targetTransform);

                engine::Graphics::TransformationUtils::SetRotation(enemy, transform, targetRotation);
                engine::Graphics::TransformationUtils::AddRelativeTranslation(enemy, transform, glm::vec3(0, 0, -3) * speed);
                break;
            }
        }
    }

    glm::quat EnemyController::FindRotation(const engine::Graphics::Transform &transform,
                                            const engine::Graphics::Transform &targetTransform) {
        auto targetRotation = glm::toQuat(
                glm::lookAt(
                        glm::vec3(targetTransform.modelMatrix * glm::vec4(0, 0, 0, 1)),
                        glm::vec3(transform.modelMatrix * glm::vec4(0, 0, 0, 1)),
                        glm::vec3(transform.modelMatrix * glm::vec4(0, 1, 0, 0))));

        glm::quat newRotation = glm::mix(transform.rotation, targetRotation, 0.5f * gl3::engine::Time::GetDeltaTime());
    }

    float EnemyController::FindSpeedAmplitude(const engine::Graphics::Transform &transform,
                                              const engine::Graphics::Transform &targetTransform, glm::quat newRotation) {
        auto currentForwardVector = glm::vec3(transform.rotation * glm::vec4(0, 0, 1, 0));
        auto targetedForwardVector = glm::vec3(newRotation * glm::vec4(0, 0, 1, 0));

        glm::vec3 rotationDifference = abs(targetedForwardVector -
                                           currentForwardVector); //Gets difference between target rotation and current rotation

        return (2 - glm::length(rotationDifference)) / 4.f * Time::GetDeltaTime();
    }

    void EnemyController::Attack(const engine::Graphics::Transform &transform,
                                 const engine::Graphics::Transform &targetTransform) {
        std::random_device randDevShoot;
        std::mt19937 shootGenerator(randDevShoot());
        std::uniform_int_distribution<int> shootDistribution(0, 300);

        if (shootDistribution(shootGenerator) < 1) {
            entt::registry &registry = engine::Ecs::Registry::getCurrent();

        }
    }
}


