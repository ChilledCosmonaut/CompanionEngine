#pragma once

#include "engine/ECS/System.h"

#include "../Components/AsteroidField.h"

namespace gl3::game {
    class AsteroidVectorField : public engine::entityComponentSystem::System {
    public:
        AsteroidVectorField() = default;

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override;

        void OnShutdown(engine::Game &engine) override {};
    };
}