#include "ShipController.h"

class SpaceshipTranslations;
namespace gl3::game {

    void ShipController::OnSetUp(engine::Game &game) {
        auto inputManager = engine::inputSystem::InputManager::GetInputManager();
        inputManager->AddInputGroup(translationControls);
        inputManager->AddInputGroup(rotationControls);
        inputManager->AddInputGroup(fireControls);

        auto &registry = Ecs::Registry::getCurrent();
        auto componentView = registry.view<ShipMovementSettings, Physics::RigidBody>();

        for (auto &entity: componentView) {
            auto &movementSettings = componentView.get<ShipMovementSettings>(entity);
            auto &rigidBody = componentView.get<Physics::RigidBody>(entity);

            rigidBody.rigidBody->setAngularDamping(2.0f);
            rigidBody.rigidBody->setLinearDamping(0.7f);
            rigidBody.rigidBody->setMaxLinearVelocity(movementSettings.maxSpeed);
        }
    }

    void ShipController::Update(engine::Game &game) {
        auto &registry = Ecs::Registry::getCurrent();
        auto componentView = registry.view<ShipMovementSettings, Physics::RigidBody, Graphics::Transform, Health>();
        auto deadView = registry.view<Dead>();
        auto stationView = registry.view<Health, Station>();

        auto translationInput = translationControls->GetInputVector();
        auto rotationInput = rotationControls->GetInputVector();
        float fireInput = fireControls->GetInput();

        for(auto station: stationView) {
            auto &stationHealth = stationView.get<Health>(station);
            if(stationHealth.currentLife <= 0){
                registry.emplace_or_replace<Dead>(station);
            }
        }

        for (auto &entity: componentView) {
            auto &movementSettings = componentView.get<ShipMovementSettings>(entity);
            auto &rigidBody = componentView.get<Physics::RigidBody>(entity);
            auto &transform = componentView.get<Graphics::Transform>(entity);
            auto &playerHealth = componentView.get<Health>(entity);

            if(playerHealth.currentLife <= 0){
                registry.emplace_or_replace<Dead>(entity);
            }

            for (auto &deadEntity: deadView) {
                auto infoView = registry.view<Info, Graphics::Text, Graphics::Transform>();
                for (auto info:infoView) {
                    auto &infoText = registry.get<Graphics::Text>(info);
                    auto &infoTransform = registry.get<Graphics::Transform>(info);
                    infoTransform.active = true;
                    infoText.content = "Mission failed!";
                }
                registry.remove<ShipMovementSettings>(entity);
                return;
            }

            HandleTranslation(rigidBody, movementSettings, transform.rotation * translationInput);
            HandleRotation(rigidBody, movementSettings, transform.rotation * rotationInput);
            HandleFire(transform, fireInput);
        }
    }

    void ShipController::HandleTranslation(Physics::RigidBody &rigidBody,
                                           ShipMovementSettings &movementSettings,
                                           glm::vec3 translationInput) {
        rigidBody.rigidBody->addForce(
                physx::PxVec3(translationInput.x, translationInput.y, translationInput.z)
                * movementSettings.speedZ * rigidBody.mass * 10 * engine::Time::GetDeltaTime());
    }

    void ShipController::HandleRotation(Physics::RigidBody &rigidBody,
                                        ShipMovementSettings &movementSettings,
                                        glm::vec3 rotationInput) {
        if (glm::length(rotationInput) != 0){
            auto velocity = physx::PxVec3(-rotationInput.x, -rotationInput.y, -rotationInput.z) * movementSettings.rotationSpeed;
            rigidBody.rigidBody->setAngularVelocity(velocity);
        }
    }

    void ShipController::HandleFire(Graphics::Transform &transform, float input) {
        if (input > 0){
            ShootingMechanics::Shoot(transform);
        }
    }
}