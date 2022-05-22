#pragma once
#include <GLFW/glfw3.h>
#include "iostream"
#include "engine/GraphicsEngine/Transform.h"


class ShipController {
public:
    void GetUpdatedShipPosition(Graphics::Transform* formerPosition, GLFWwindow* window, const float* screenWidth, const float* screenHeight, float deltaTime);
private:
    void HandleKeyboard(GLFWwindow* window, float deltaTime);

    void CheckMousePosition(GLFWwindow *window, const float *screenWidth,
                            const float *screenHeight, float deltaTime);

    float maxSpeed = 1200.0f;
    float maxRotation = 200.0f;

    float mouseOffset = 0.15f;

    float forwardAcceleration = 0.0f;

    float rotationAccelerationZ = 0.0f;
    float rotationAccelerationX = 0.0f;
    float rotationAccelerationY = 0.0f;

    float rotationX = 17.06f;
    float rotationY = 44.62f;

    float speedX = 200, speedY = 200, speedZ = 200, rotationZ = 200;

    float drag = 400.0f;
};
