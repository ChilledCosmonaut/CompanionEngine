#include "ShootingMechanics.h"

namespace gl3::game {
    void ShootingMechanics::Shoot(engine::Graphics::Transform &transform) {
        entt::registry &registry = engine::Ecs::Registry::getCurrent();
        glm::vec3 relativeForwardVector = transform.globalRotation * glm::vec4(0, 0, 1, 0);
        glm::vec3 worldPosition = engine::Graphics::TransformationUtils::GetGlobalTranslation(transform);

        entt::entity victim = engine::Physics::PhysicsUtils::MakeRaycast(worldPosition, relativeForwardVector, 200);

        entt::entity laserChild = entt::tombstone;

        for (entt::entity child : transform.children) {
            if (registry.any_of<Laser>(child)){
                laserChild = child;
                break;
            }
        }

        if(laserChild == entt::tombstone)
            return;

        auto &laserStats = registry.get<Laser>(laserChild);
        if(laserStats.timeLeft > 0) return;
        laserStats.timeLeft = laserStats.showTimer;

        float laserLength = 1000;

        if (victim != entt::tombstone){
            auto &victimTransform = registry.get<engine::Graphics::Transform>(victim);
            laserLength = glm::distance(worldPosition,
                                        engine::Graphics::TransformationUtils::GetGlobalTranslation(victimTransform));
        }

        auto &laserTransform = registry.get<engine::Graphics::Transform>(laserChild);
        laserTransform.active = true;
        laserTransform.scale.z = laserLength;

        if (!registry.any_of<Health>(victim)) return;

        Health &health = registry.get<Health>(victim);
        health.currentLife -= laserStats.laserDamage;
        std::cout << health.currentLife << std::endl;
    }
}