#include "ShootingMechanics.h"

namespace gl3::game {
    void ShootingMechanics::Shoot(engine::Graphics::Transform &transform) {
        entt::registry &registry = engine::Ecs::Registry::getCurrent();

        entt::entity laserChild = entt::tombstone;

        for (entt::entity child: transform.children) {
            if (registry.any_of<Laser>(child)) {
                laserChild = child;
                break;
            }
        }

        if (laserChild == entt::tombstone)
            return;

        auto &laserStats = registry.get<Laser>(laserChild);
        if (laserStats.timeLeft > 0) return;
        laserStats.timeLeft = laserStats.showTimer;

        auto &laserTransform = registry.get<engine::Graphics::Transform>(laserChild);
        glm::vec3 shootPosition = engine::Graphics::TransformationUtils::GetGlobalTranslation(laserTransform);
        glm::vec3 relativeForwardVector = laserTransform.globalRotation * glm::vec4(0, 0, 1, 0);

        entt::entity victim = engine::Physics::PhysicsUtils::MakeRaycast(shootPosition, relativeForwardVector, 200);

        float laserLength = 1000;

        if (victim != entt::tombstone) {

            auto &victimTransform = registry.get<engine::Graphics::Transform>(victim);
            laserLength = glm::distance(shootPosition,
                                        engine::Graphics::TransformationUtils::GetGlobalTranslation(victimTransform));

            if (!registry.any_of<Health>(victim)) return;

            Health &health = registry.get<Health>(victim);
            health.currentLife -= laserStats.laserDamage;
            std::cout <<"Hit enemy:"<< std::to_string(static_cast<double>(victim))<<" with length:"<< std::to_string(laserLength) << std::endl;
        }

        laserTransform.active = true;
        laserTransform.scale.z = laserLength;
    }
}