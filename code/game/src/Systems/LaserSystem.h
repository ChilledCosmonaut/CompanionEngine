#pragma once

#include "../Components/EnemyBehavourSettings.h"
#include "../Components/ShipMovementSettings.h"
#include "engine/ECS/System.h"
#include "engine/Time.h"
#include "engine/ECS/Registry.h"

namespace gl3::game {
    class LaserSystem : public engine::entityComponentSystem::System {
    public:
        LaserSystem() = default;

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override{
            auto& registry = engine::Ecs::Registry::getCurrent();
            auto laserView = registry.view<Laser, engine::Graphics::Transform>();
            for (auto &laser: laserView) {
                auto &laserStats = laserView.get<Laser>(laser);
                auto &transform = laserView.get<engine::Graphics::Transform>(laser);

                laserStats.timeLeft -= Time::GetDeltaTime();
                if (laserStats.timeLeft <= 0.f){
                    laserStats.timeLeft = 0;
                    transform.active = false;
                }
            }
        };

        void OnShutdown(engine::Game &engine) override {};
    };
}