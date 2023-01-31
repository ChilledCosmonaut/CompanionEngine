#include "EnemyController.h"

namespace gl3::game {

    void EnemyController::Update(engine::Game &game) {
        auto &registry = engine::Ecs::Registry::getCurrent();
        auto enemyView = registry.view<EnemyBehaviour, engine::Graphics::Transform/*, engine::Physics::RigidBody*/>(/*entt::exclude<Ecs::Flags::Setup<gl3::game::Physics::RigidBody>>*/);
        for (auto &enemy: enemyView) {
            auto &enemyStats = enemyView.get<EnemyBehaviour>(enemy);
            auto &transform = enemyView.get<engine::Graphics::Transform>(enemy);
            //auto &rigidBody = enemyView.get<engine::Physics::RigidBody>(enemy);
            auto componentView = registry.view<ShipMovementSettings, engine::Graphics::Transform>();

            for (auto &entity: componentView) {
                auto &targetTransform = componentView.get<engine::Graphics::Transform>(entity);

                glm::quat targetRotation = FindRotation(transform, targetTransform);
                glm::vec3 nextRotationStep = DetermineNextRotationStep(transform, targetRotation);
                float speed = FindSpeedAmplitude(transform, targetTransform, targetRotation);
                Attack(transform, targetTransform);

                engine::Graphics::TransformationUtils::SetRotation(enemy, transform, targetRotation);
                //rigidBody.rigidBody->setAngularVelocity(physx::PxVec3(nextRotationStep.x, nextRotationStep.y, nextRotationStep.z));
                //engine::Graphics::TransformationUtils::AddRelativeTranslation(enemy, transform, glm::vec3(0, 0, -3) * speed);
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

        return targetRotation;
    }

    glm::vec3 EnemyController::DetermineNextRotationStep(const Transform &transform, glm::quat newRotation) {
        glm::vec3 newRotationInEuler = glm::eulerAngles(newRotation);
        glm::vec3 oldRotationInEuler = glm::eulerAngles(transform.rotation);

        glm::vec3 rotationDifference = newRotationInEuler - oldRotationInEuler;

        return {min(max(rotationDifference.x, -1),1), min(max(rotationDifference.y, -1),1), min(max(rotationDifference.z, -1),1)};
    }

    float EnemyController::FindSpeedAmplitude(const engine::Graphics::Transform &transform,
                                              const engine::Graphics::Transform &targetTransform, glm::quat newRotation) {
        auto currentForwardVector = glm::degrees(glm::vec3(transform.rotation * glm::vec4(0, 0, 1, 0)));
        auto targetedForwardVector = glm::degrees(glm::vec3(newRotation * glm::vec4(0, 0, 1, 0)));

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


