#pragma once

#include "engine/ECS/System.h"
#include "engine/Systems/Graphics/Components/Transform.h"

#include "../Components/WaveInfo.h"
#include "../Components/Dead.h"

#include "../Utils/ModelCreationTemplates.h"

namespace gl3::game{
    class SpawnSystem : public engine::entityComponentSystem::System {
    public:
        SpawnSystem() = default;

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override;

        void OnShutdown(engine::Game &engine) override {};
    };
}