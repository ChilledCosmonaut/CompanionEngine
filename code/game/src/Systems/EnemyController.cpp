#include "EnemyController.h"

namespace gl3::game {

    void EnemyController::Update(engine::Game &game) {
        auto &registry = engine::Ecs::Registry::getCurrent();
        auto enemyView = registry.view<EnemyBehaviour, engine::Graphics::Transform>();
        for (auto &enemy: enemyView) {
            auto &enemyStats = enemyView.get<EnemyBehaviour>(enemy);
            auto &transform = enemyView.get<engine::Graphics::Transform>(enemy);
            auto componentView = registry.view<ShipMovementSettings, engine::Graphics::Transform>();

            /*if (enemyStats.lifePoints <= 0) {
                transform.active = false;
                return;
            }*/

            for (auto &entity: componentView) {
                auto &targetTransform = componentView.get<engine::Graphics::Transform>(entity);
                //if (glm::length(transform.translation - targetTransform.translation) <= 100) {

                    /*bool shoot = rand() % 300;

                    if (shoot < 1) {
                        auto projectileView = registry.view<EnemyProjectile, engine::Graphics::Transform>();

                        for (auto &projectileEntity: projectileView) {
                            auto &projectile = projectileView.get<EnemyProjectile>(projectileEntity);
                            auto &projectileTransform = projectileView.get<engine::Graphics::Transform>(
                                    projectileEntity);

                            if (projectile.lifetime <= 0) {
                                projectileTransform.active = true;
                                engine::Graphics::TransformationUtils::SetTranslation(entity, projectileTransform,
                                                                                      transform.translation);
                                engine::Graphics::TransformationUtils::SetRotation(entity, projectileTransform,
                                                                                   transform.rotation);
                                projectile.lifetime = 3;
                            }
                        }
                    }*/
                //glm::normalize(glm::vec3((testVector) - glm::vec4(transform.translation, 1)))

                auto targetRotation = glm::toQuat(
                        glm::lookAt(
                                glm::vec3(targetTransform.modelMatrix * glm::vec4(0, 0, 0, 1)),
                                glm::vec3(transform.modelMatrix * glm::vec4(0, 0, 0, 1)),
                                glm::vec3(0, 1, 0)));
                    glm::quat newRotation = glm::mix(transform.rotation, targetRotation,
                                                     0.5f * gl3::engine::Time::GetDeltaTime());
                auto testVector = transform.modelMatrix * glm::vec4(0, 0, 0, 1);
                    std::cout<<"x: "<<testVector.x<<" ,y: "<<testVector.y<<" ,z: "<<testVector.z<<std::endl;
                    testVector.z = 0;
                    engine::Graphics::TransformationUtils::SetRotation(enemy, transform, targetRotation);
                    engine::Graphics::TransformationUtils::AddRelativeTranslation(enemy, transform, glm::vec3(0,0,1) * gl3::engine::Time::GetDeltaTime());
                    break;
                //}
            }
        }
    }
}


