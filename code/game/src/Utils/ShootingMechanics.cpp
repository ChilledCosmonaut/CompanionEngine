#include "ShootingMechanics.h"

namespace gl3::game {
    void ShootingMechanics::Shoot(const engine::Graphics::Transform &transform) {
        entt::registry &registry = engine::Ecs::Registry::getCurrent();
        glm::vec3 relativeForwardVector = transform.globalRotation * glm::vec4(0, 0, 1, 0);
        glm::vec3 worldPosition = engine::Graphics::TransformationUtils::GetGlobalTranslation(
                const_cast<engine::Graphics::Transform &>(transform));

        entt::entity victim = engine::Physics::PhysicsUtils::MakeRaycast(worldPosition, relativeForwardVector, 200);

        if (!registry.any_of<Health>(victim)) return;

        Health &health = registry.get<Health>(victim);
        health.currentLife -= 10;
        std::cout << health.currentLife << std::endl;
    }
}