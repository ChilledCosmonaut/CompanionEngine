#include "EnemyController.h"

namespace gl3::game {

    void EnemyController::Update(engine::Game &game) {
        auto &registry = engine::Ecs::Registry::getCurrent();
        auto fighterView = registry.view<FighterBehaviour, engine::Graphics::Transform, engine::Physics::RigidBody>(
                entt::exclude<Ecs::Flags::Setup<gl3::game::Physics::RigidBody>>);
        for (auto &enemy: fighterView) {
            auto &enemyStats = fighterView.get<FighterBehaviour>(enemy);
            auto &transform = fighterView.get<engine::Graphics::Transform>(enemy);
            auto &rigidBody = fighterView.get<engine::Physics::RigidBody>(enemy);
            auto componentView = registry.view<ShipMovementSettings, engine::Graphics::Transform>();

            for (auto &entity: componentView) {
                auto &targetTransform = componentView.get<engine::Graphics::Transform>(entity);

                glm::quat targetRotation = FindRotation(transform, targetTransform);
                float speed = FindSpeedAmplitude(transform, targetTransform, targetRotation);
                Attack(transform, targetTransform);

                engine::Graphics::TransformationUtils::SetRotation(enemy, transform, targetRotation);
                //rigidBody.rigidBody->setAngularVelocity(FindAngularVelocity(transform, targetRotation));
                rigidBody.rigidBody->setLinearVelocity(FindLinearVelocity(transform, targetTransform, speed, enemyStats.maxSpeed));
                break;
            }
        }

        auto carrierView = registry.view<CarrierBehaviour, engine::Graphics::Transform, engine::Physics::RigidBody>(
                entt::exclude<Ecs::Flags::Setup<gl3::game::Physics::RigidBody>>);
        for (auto &enemy: carrierView) {
            auto &enemyStats = carrierView.get<CarrierBehaviour>(enemy);
            auto &transform = carrierView.get<engine::Graphics::Transform>(enemy);
            auto &rigidBody = carrierView.get<engine::Physics::RigidBody>(enemy);
            auto componentView = registry.view<Station, engine::Graphics::Transform>();

            for (auto &entity: componentView) {
                auto &targetTransform = componentView.get<engine::Graphics::Transform>(entity);

                glm::quat targetRotation = FindRotation(transform, targetTransform);
                float speed = FindCarrierSpeedAmplitude(transform, targetTransform);
                Attack(transform, targetTransform);

                engine::Graphics::TransformationUtils::SetRotation(enemy, transform, targetRotation);
                //rigidBody.rigidBody->setAngularVelocity(FindAngularVelocity(transform, targetRotation));
                rigidBody.rigidBody->setLinearVelocity(FindLinearVelocity(transform, targetTransform, speed, enemyStats.maxSpeed));
                break;
            }
        }
    }

    glm::quat EnemyController::FindRotation(const engine::Graphics::Transform &transform,
                                            const engine::Graphics::Transform &targetTransform) {
        glm::vec3 viewDirection =
                normalize(targetTransform.modelMatrix * glm::vec4(0, 0, 0, 1) - transform.modelMatrix * glm::vec4(0, 0, 0, 1));
        auto targetRotation = glm::quatLookAtLH(
                viewDirection,
                glm::vec3(/*transform.modelMatrix * glm::vec4(*/0, 1, 0/*, 0)*/));

        return targetRotation;
    }

    physx::PxVec3 EnemyController::FindAngularVelocity(const Transform &transform, glm::quat newRotation) {
        glm::vec3 newRotationInEuler = glm::eulerAngles(newRotation);
        glm::vec3 oldRotationInEuler = glm::eulerAngles(transform.rotation);

        glm::vec3 rotationDifference = newRotationInEuler - oldRotationInEuler;

        return {min(max(rotationDifference.x, -1), 1), min(max(rotationDifference.y, -1), 1),
                min(max(rotationDifference.z, -1), 1)};
    }

    float EnemyController::FindSpeedAmplitude(const engine::Graphics::Transform &transform,
                                              const engine::Graphics::Transform &targetTransform,
                                              glm::quat newRotation) {
        auto currentForwardVector = glm::vec3(transform.rotation * glm::vec4(0, 0, 1, 0));
        auto targetedForwardVector = glm::vec3(newRotation * glm::vec4(0, 0, 1, 0));

        float angle = glm::acos(clamp(glm::dot(currentForwardVector, targetedForwardVector)/(glm::length(currentForwardVector) * glm::length(targetedForwardVector)), -1.f, 1.f));

        return 1 - (angle/ 180);
    }

    float EnemyController::FindCarrierSpeedAmplitude(const Transform &transform, const Transform &targetTransform) {
        float baseDistance = glm::distance(transform.modelMatrix * glm::vec4(0, 0, 0, 1), targetTransform.modelMatrix * glm::vec4(0, 0, 0, 1));

        if(baseDistance <= 80)
            return 0;

        return 1;
    }

    physx::PxVec3 EnemyController::FindLinearVelocity(const Transform &transform, const Transform &targetTransform,
                                                      float speedAmplitude, float shipSpeed) {
        auto relativeForwardVector = transform.globalRotation * glm::vec4(0, 0, 1, 0);
        float distanceAmplitude = glm::distance(transform.modelMatrix * glm::vec4(0, 0, 0, 1), targetTransform.modelMatrix * glm::vec4(0, 0, 0, 1)) / 20;

        relativeForwardVector *= min(max(distanceAmplitude, 0), 5) * speedAmplitude * shipSpeed;

        return {relativeForwardVector.x, relativeForwardVector.y, relativeForwardVector.z};
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


