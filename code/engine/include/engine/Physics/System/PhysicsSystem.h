#pragma once

#include "PxPhysicsAPI.h"

#include "engine/System.h"
#include "engine/Physics/Components/RigidBody.h"
#include "engine/GraphicsEngine/Components/Transform.h"
#include "engine/GraphicsEngine/Scene.h"
#include "engine/Time.h"

namespace gl3::engine::Physics {

    class PhysicsSystem : public entityComponentSystem::System {
    public:
        PhysicsSystem() = default;

        void OnSwitchingScenes(engine::Graphics::Scene &scene) override {}

        void OnDrawCall(engine::Graphics::Scene &scene) override {};

        void Start(engine::Game &game) override {};

        void Update(engine::Game &game) override{
            game.getCurrentScene()->GetPhysicsScene()->simulate(1.0f/60.0f);
            game.getCurrentScene()->GetPhysicsScene()->fetchResults(true);
        };

        void OnShutdown(engine::Game &engine) override {};
    };
}
