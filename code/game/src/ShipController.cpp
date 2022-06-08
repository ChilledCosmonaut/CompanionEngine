#include "ShipController.h"

namespace gl3::game {

    template<typename T>
    int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    void ShipController::GetUpdatedShipPosition(engine::Graphics::Components::Transform *formerPosition, GLFWwindow *window,
                                                const float *screenWidth, const float *screenHeight, float deltaTime) {
        HandleKeyboard(window, deltaTime);
        CheckMousePosition(window, screenWidth, screenHeight, deltaTime);

        int inputx = glfwGetKey(window, GLFW_KEY_A);
        inputx -= glfwGetKey(window, GLFW_KEY_D);

        int inputy = glfwGetKey(window, GLFW_KEY_SPACE);
        inputy -= glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL);

        auto translation = glm::vec3(-inputx * speedX, -inputy * speedY, forwardAcceleration) * deltaTime;
        glm::vec3 rotation = glm::vec3(rotationAccelerationX, rotationAccelerationY, rotationAccelerationZ);

        formerPosition->AddRotation(rotation * deltaTime);
        formerPosition->AddRelativeTranslation(translation * deltaTime);
    }

    void ShipController::HandleKeyboard(GLFWwindow *window, float deltaTime) {
        int inputZ = glfwGetKey(window, GLFW_KEY_W);
        inputZ -= glfwGetKey(window, GLFW_KEY_S);

        forwardAcceleration -= inputZ * speedZ * deltaTime;
        float threshold = 0.1f * speedZ * deltaTime;

        if (!(inputZ < 0.1f && inputZ > -0.1f)) {
            if (forwardAcceleration > maxSpeed) forwardAcceleration = maxSpeed;

            if (forwardAcceleration < -(maxSpeed / 4)) forwardAcceleration = -(maxSpeed / 4);
        } else {
            if ((sgn(forwardAcceleration) * forwardAcceleration) < threshold) forwardAcceleration = 0;

            if (forwardAcceleration != 0)
                forwardAcceleration -= sgn(forwardAcceleration) * drag * deltaTime;
        }

        int input = glfwGetKey(window, GLFW_KEY_Q);
        input -= glfwGetKey(window, GLFW_KEY_E);

        rotationAccelerationZ -= input * deltaTime * rotationZ;

        float rotationThresholdZ = 0.1f * rotationZ * deltaTime;

        if (!(input < 0.1f && input > -0.1f)) {
            if (rotationAccelerationZ > maxRotation) {
                rotationAccelerationZ = maxRotation;
            }

            if (rotationAccelerationZ < -maxRotation) rotationAccelerationZ = -maxRotation;
        } else {
            if ((sgn(rotationAccelerationZ) * rotationAccelerationZ) < rotationThresholdZ)
                rotationAccelerationZ = 0;

            if (rotationAccelerationZ != 0)
                rotationAccelerationZ -= sgn(rotationAccelerationZ) * drag * deltaTime;
        }
    }

    void ShipController::CheckMousePosition(GLFWwindow *window, const float *screenWidth,
                                            const float *screenHeight, float deltaTime) {
        double xposition, yposition;
        glfwGetCursorPos(window, &xposition, &yposition);

        float mousePosX = xposition - *screenWidth / 2;
        float mousePosY = yposition - *screenHeight / 2;

        mousePosX /= *screenWidth / 2.0f;
        mousePosY /= *screenHeight / 2.0f;

        if (mousePosX < mouseOffset && mousePosX > -mouseOffset) mousePosX = 0;
        if (mousePosY < mouseOffset && mousePosY > -mouseOffset) mousePosY = 0;

        rotationAccelerationX += -mousePosY * deltaTime * rotationX;

        float rotationThresholdX = 0.1f * rotationX * deltaTime;

        if (mousePosY != 0) {
            if (sgn(rotationAccelerationX) * rotationAccelerationX > maxRotation)
                rotationAccelerationX =
                        sgn(rotationAccelerationX) * maxRotation;
        } else {
            if ((sgn(rotationAccelerationX) * rotationAccelerationX) < rotationThresholdX)
                rotationAccelerationX = 0;


            if (rotationAccelerationX != 0)
                rotationAccelerationX -= sgn(rotationAccelerationX) * drag * deltaTime;
        }

        rotationAccelerationY += -mousePosX * deltaTime * rotationY;

        float rotationThresholdY = 0.1f * rotationY * deltaTime;

        if (mousePosX != 0) {
            if (sgn(rotationAccelerationY) * rotationAccelerationY > (maxRotation / 2))
                rotationAccelerationY =
                        sgn(rotationAccelerationY) * maxRotation / 2;
        } else {
            if ((sgn(rotationAccelerationY) * rotationAccelerationY) < rotationThresholdY)
                rotationAccelerationY = 0;

            if (rotationAccelerationY != 0)
                rotationAccelerationY -= sgn(rotationAccelerationY) * (drag / 2) * deltaTime;
        }
    }
}