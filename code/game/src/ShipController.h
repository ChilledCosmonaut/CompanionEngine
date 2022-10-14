#pragma once

#include "iostream"
#include "engine/Systems/Graphics/Utils/TransformUtils.h"
#include "engine/System.h"
#include "ShipMovementSettings.h"
#include "ProjectileInfo.h"
#include "engine/Time.h"
#include "engine/Systems/Physics/Components/Rigidbody.h"
#include "engine/Systems/Physics/Utils/RigidBodyUtils.h"

namespace gl3::game {
class ShipController : public engine::entityComponentSystem::System {
    public:
    ShipController() = default;

    void OnSwitchingScenes(engine::Graphics::Scene &scene) override {}

    void OnDrawCall(engine::Graphics::Scene &scene) override {};

    void OnSetUp(engine::Game &game) override {};

    void Update(engine::Game &game) override;

    void OnShutdown(engine::Game &engine) override {};

    private:
        void HandleKeyboard(GLFWwindow *window, ShipMovementSettings &movementSettings, float deltaTime);

        void CheckMousePosition(GLFWwindow *window, int *screenWidth,
                                int *screenHeight, ShipMovementSettings &movementSettings, float deltaTime);
    };
}