#include "ShipController.h"

class SpaceshipTranslations;
namespace gl3::game {

    using namespace engine;
    using namespace engine::Graphics;

    template<typename T>
    int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    void Fire(int fire, entt::registry* registry, Transform& playerTransform) {
        if (fire == GLFW_PRESS){
            auto projectileView = registry->view<PlayerProjectile, Transform>();

            for (auto& entity : projectileView) {
                auto& projectile = projectileView.get<PlayerProjectile>(entity);
                auto& transform = projectileView.get<Transform>(entity);

                if (projectile.lifetime <= 0){
                    transform.active = true;
                    TransformationUtils::SetTranslation(entity, transform, playerTransform.translation);
                    TransformationUtils::SetRotation(entity, transform, playerTransform.rotation);
                    projectile.lifetime = 5;
                }
            }
        }
    }

    void ShipController::OnSetUp(engine::Game &game) {
        auto inputManager = engine::inputSystem::InputManager::GetInputManager();
        inputManager->AddInputGroup(translationControls);
        inputManager->AddInputGroup(rotationControls);
    }

    void ShipController::Update(engine::Game &game) {
        auto window = game.getWindow();
        auto& registry = Ecs::Registry::getCurrent();
        auto componentView = registry.view<ShipMovementSettings, Physics::RigidBody>();
        int screenWidth = 3840, screenHeight = 2160;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);

        auto translationInput = translationControls->GetInputVector();
        auto rotationInput = rotationControls->GetInputVector();

        //std::cout<<"Translation: ("<<translationInput.x<<","<<translationInput.y<<","<<translationInput.z<<"), Rotation: ("<<rotationInput.x<<","<<rotationInput.y<<","<<rotationInput.z<<")"<<std::endl;

        for(auto& entity : componentView){
            auto& movementSettings = componentView.get<ShipMovementSettings>(entity);
            auto& rigidBody = componentView.get<Physics::RigidBody>(entity);

            HandleKeyboard(window, movementSettings, Time::GetDeltaTime());
            CheckMousePosition(window, &screenWidth, &screenHeight, movementSettings, Time::GetDeltaTime());

            /*int inputx = glfwGetKey(window, GLFW_KEY_A);
            inputx -= glfwGetKey(window, GLFW_KEY_D);

            int inputy = glfwGetKey(window, GLFW_KEY_SPACE);
            inputy -= glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL);
*/
            /*int fire = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
            Fire(fire, registry, currentTransform);*/

             /*rigidBody.rigidBody->addForce(physx::PxVec3(-inputx * movementSettings.speedX, -inputy * movementSettings.speedY, movementSettings.forwardAcceleration)
                                           * engine::Time::GetDeltaTime());*/

            /*auto translation = glm::vec3(-inputx * movementSettings.speedX, -inputy * movementSettings.speedY, movementSettings.forwardAcceleration) * engine::Time::GetDeltaTime();
            glm::vec3 rotation = glm::vec3(movementSettings.rotationAccelerationX, movementSettings.rotationAccelerationY, movementSettings.rotationAccelerationZ);*/

            /*TransformUtils::AddRotation(currentTransform, rotation * Time::GetDeltaTime());
            TransformUtils::AddRelativeTranslation(currentTransform, translation * Time::GetDeltaTime());*/
        }
    }

    void ShipController::HandleKeyboard(GLFWwindow *window, ShipMovementSettings &movementSettings, float deltaTime) {
        /*int inputZ = glfwGetKey(window, GLFW_KEY_W);
        inputZ -= glfwGetKey(window, GLFW_KEY_S);*/

        /*movementSettings.forwardAcceleration -= inputZ * movementSettings.speedZ * deltaTime;
        float threshold = 0.1f * movementSettings.speedZ * deltaTime;

        if (!(inputZ < 0.1f && inputZ > -0.1f)) {
            if (movementSettings.forwardAcceleration > movementSettings.maxSpeed) movementSettings.forwardAcceleration = movementSettings.maxSpeed;

            if (movementSettings.forwardAcceleration < -(movementSettings.maxSpeed / 4)) movementSettings.forwardAcceleration = -(movementSettings.maxSpeed / 4);
        } else {
            if ((sgn(movementSettings.forwardAcceleration) * movementSettings.forwardAcceleration) < threshold) movementSettings.forwardAcceleration = 0;

            if (movementSettings.forwardAcceleration != 0)
                movementSettings.forwardAcceleration -= sgn(movementSettings.forwardAcceleration) * movementSettings.drag * deltaTime;
        }

        *//*int input = glfwGetKey(window, GLFW_KEY_Q);
        input -= glfwGetKey(window, GLFW_KEY_E);*//*

        movementSettings.rotationAccelerationZ -= input * deltaTime * movementSettings.rotationZ;

        float rotationThresholdZ = 0.1f * movementSettings.rotationZ * deltaTime;

        if (!(input < 0.1f && input > -0.1f)) {
            if (movementSettings.rotationAccelerationZ > movementSettings.maxRotation) {
                movementSettings.rotationAccelerationZ = movementSettings.maxRotation;
            }

            if (movementSettings.rotationAccelerationZ < -movementSettings.maxRotation) movementSettings.rotationAccelerationZ = -movementSettings.maxRotation;
        } else {
            if ((sgn(movementSettings.rotationAccelerationZ) * movementSettings.rotationAccelerationZ) < rotationThresholdZ)
                movementSettings.rotationAccelerationZ = 0;

            if (movementSettings.rotationAccelerationZ != 0)
                movementSettings.rotationAccelerationZ -= sgn(movementSettings.rotationAccelerationZ) * movementSettings.drag * deltaTime;
        }*/
    }

    void ShipController::CheckMousePosition(GLFWwindow *window, int *screenWidth,
                                            int *screenHeight, ShipMovementSettings &movementSettings, float deltaTime) {
        double xposition, yposition;
        glfwGetCursorPos(window, &xposition, &yposition);

        float mousePosX = xposition - *screenWidth / 2;
        float mousePosY = yposition - *screenHeight / 2;

        mousePosX /= *screenWidth / 2.0f;
        mousePosY /= *screenHeight / 2.0f;

        if (mousePosX < movementSettings.mouseOffset && mousePosX > -movementSettings.mouseOffset) mousePosX = 0;
        if (mousePosY < movementSettings.mouseOffset && mousePosY > -movementSettings.mouseOffset) mousePosY = 0;

        movementSettings.rotationAccelerationX += -mousePosY * deltaTime * movementSettings.rotationX;

        float rotationThresholdX = 0.1f * movementSettings.rotationX * deltaTime;

        if (mousePosY != 0) {
            if (sgn(movementSettings.rotationAccelerationX) * movementSettings.rotationAccelerationX > movementSettings.maxRotation)
                movementSettings.rotationAccelerationX =
                        sgn(movementSettings.rotationAccelerationX) * movementSettings.maxRotation;
        } else {
            if ((sgn(movementSettings.rotationAccelerationX) * movementSettings.rotationAccelerationX) < rotationThresholdX)
                movementSettings.rotationAccelerationX = 0;


            if (movementSettings.rotationAccelerationX != 0)
                movementSettings.rotationAccelerationX -= sgn(movementSettings.rotationAccelerationX) * movementSettings.drag * deltaTime;
        }

        movementSettings.rotationAccelerationY += -mousePosX * deltaTime * movementSettings.rotationY;

        float rotationThresholdY = 0.1f * movementSettings.rotationY * deltaTime;

        if (mousePosX != 0) {
            if (sgn(movementSettings.rotationAccelerationY) * movementSettings.rotationAccelerationY > (movementSettings.maxRotation / 2))
                movementSettings.rotationAccelerationY =
                        sgn(movementSettings.rotationAccelerationY) * movementSettings.maxRotation / 2;
        } else {
            if ((sgn(movementSettings.rotationAccelerationY) * movementSettings.rotationAccelerationY) < rotationThresholdY)
                movementSettings.rotationAccelerationY = 0;

            if (movementSettings.rotationAccelerationY != 0)
                movementSettings.rotationAccelerationY -= sgn(movementSettings.rotationAccelerationY) * (movementSettings.drag / 2) * deltaTime;
        }
    }
}