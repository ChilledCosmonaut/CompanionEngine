#pragma once

#include "iostream"

#include "engine/Systems/Graphics/Utils/TransformationUtils.h"
#include "engine/ECS/System.h"
#include "engine/Time.h"
#include "engine/Systems/Physics/Components/RigidBody.h"

#include "../Components/ShipMovementSettings.h"
#include "../Components/Dead.h"
#include "../Components/InfoFlags.h"
#include "../Components/Station.h"

#include "../ControlGroups/Spaceship/SpaceShipControls.h"

#include "../Utils/ShootingMechanics.h"

namespace gl3::game {

    using namespace engine;
    using namespace engine::Graphics;
    using namespace ::game::controls;

    class ShipController : public engine::entityComponentSystem::System {
    public:
        ShipController() = default;

        void OnSetUp(engine::Game &game) override;

        void Update(engine::Game &game) override;

        void OnShutdown(engine::Game &engine) override {};

    private:
        static void HandleTranslation(Physics::RigidBody &rigidBody, ShipMovementSettings &movementSettings, glm::vec3 translationInput);

        static void HandleRotation(Physics::RigidBody &rigidBody, ShipMovementSettings &movementSettings, glm::vec3 rotationInput);

        static void HandleFire(Graphics::Transform &transform, float input);

        std::shared_ptr<SpaceshipTranslationControls> translationControls = std::make_shared<SpaceshipTranslationControls>();
        std::shared_ptr<SpaceshipRotationControls> rotationControls = std::make_shared<SpaceshipRotationControls>();
        std::shared_ptr<SpaceshipFireControls> fireControls = std::make_shared<SpaceshipFireControls>();
    };
}