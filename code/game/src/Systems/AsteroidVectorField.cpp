#include "AsteroidVectorField.h"

namespace gl3::game{

    void AsteroidVectorField::Update(engine::Game &game) {
        auto &registry = engine::Ecs::Registry::getCurrent();

        auto enemyView = registry.view<engine::Graphics::Transform, engine::Physics::RigidBody, AsteroidField>();

        for (auto &asteroid: enemyView) {
            auto &transform = enemyView.get<engine::Graphics::Transform>(asteroid);
            auto &rigidBody = enemyView.get<engine::Physics::RigidBody>(asteroid);

            glm::vec3 globalTranslation = engine::Graphics::TransformationUtils::GetGlobalTranslation(transform);

            glm::vec2 forceField(transform.translation.z, -transform.translation.x);

            rigidBody.rigidBody->setLinearVelocity(physx::PxVec3(forceField.x, 0, forceField.y) / 5.f);
        }
    }
}