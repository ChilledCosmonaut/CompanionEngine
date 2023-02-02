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
        auto componentView = registry.view<ShipMovementSettings, Physics::RigidBody, Graphics::Transform>();

        auto translationInput = translationControls->GetInputVector();
        auto rotationInput = rotationControls->GetInputVector();
        float fireInput = fireControls->GetInput();

        for (auto &entity: componentView) {
            auto &movementSettings = componentView.get<ShipMovementSettings>(entity);
            auto &rigidBody = componentView.get<Physics::RigidBody>(entity);
            auto &transform = componentView.get<Graphics::Transform>(entity);

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