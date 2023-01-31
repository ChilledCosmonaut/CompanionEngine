#pragma once

#include <random>

#include "engine/ECS/System.h"

#include "ShipController.h"
#include "../Components/EnemyBehavourSettings.h"
#include "engine/Systems/Physics/Components/RigidBody.h"

namespace gl3::game {
    class EnemyController : public engine::entityComponentSystem::System {
    public:
        EnemyController() = default;

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override;

        void OnShutdown(engine::Game &engine) override {};

    private:
        static glm::quat FindRotation(const engine::Graphics::Transform& transform, const engine::Graphics::Transform& targetTransform);

        static physx::PxVec3 FindAngularVelocity(const engine::Graphics::Transform& transform, glm::quat newRotation);

        static float FindSpeedAmplitude(const engine::Graphics::Transform& transform, const engine::Graphics::Transform& targetTransform, glm::quat newRotation);

        static physx::PxVec3 FindLinearVelocity(const engine::Graphics::Transform& transform, const engine::Graphics::Transform& targetTransform, float speedAmplitude, float shipSpeed);

        static void Attack(const engine::Graphics::Transform& transform, const engine::Graphics::Transform& targetTransform);
    };
}
