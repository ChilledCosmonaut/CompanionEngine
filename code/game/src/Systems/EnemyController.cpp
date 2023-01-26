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

                auto normalizedDistanceVector = glm::abs(glm::normalize(glm::vec3(targetTransform.modelMatrix * glm::vec4(0, 0, 0, 1)) - glm::vec3(transform.modelMatrix * glm::vec4(0, 0, 0, 1))));

                auto targetRotation = glm::toQuat(
                        glm::lookAt(
                                glm::vec3(transform.modelMatrix * glm::vec4(0, 0, 0, 1)),
                                glm::vec3(targetTransform.modelMatrix * glm::vec4(0, 0, 0, 1)),
                                glm::vec3(transform.modelMatrix * glm::vec4(0, 1, 0, 0))));

                glm::quat newRotation = glm::mix(transform.rotation, targetRotation, 0.5f * gl3::engine::Time::GetDeltaTime());

                auto currentForwardVector = glm::vec3(transform.rotation * glm::vec4(0, 0, 1, 0));
                auto targetedForwardVector = glm::vec3(targetRotation * glm::vec4(0, 0, 1, 0));

                glm::vec3 rotationDifference = abs(targetedForwardVector - currentForwardVector); //Gets difference between target rotation and current rotation

                engine::Graphics::TransformationUtils::AddRelativeTranslation(enemy, transform, (glm::vec3(0,0,-3) * (2 - glm::length(rotationDifference))/4.f * Time::GetDeltaTime()));

                /*auto eulerAngles = glm::eulerAngles(targetRotation);
                std::cout << "x: " << rotationDifference.x << " ,y: " << rotationDifference.y << " ,z: " << rotationDifference.z << std::endl;
                std::cout<<glm::length(rotationDifference)<<std::endl;*/
                engine::Graphics::TransformationUtils::SetRotation(enemy, transform, targetRotation);
                break;
            }
        }
    }
}


