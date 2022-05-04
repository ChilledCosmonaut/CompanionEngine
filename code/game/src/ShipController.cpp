#include "ShipController.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void ShipController::GetUpdatedShipPosition(Graphics::Transform *formerPosition, GLFWwindow *window,
                                            const float *screenWidth, const float *screenHeight) {

}

void ShipController::HandleKeyboard(GLFWwindow *window) {

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

    if (mousePosY != 0)
    {
        if (sgn(rotationAccelerationX) * rotationAccelerationX > maxRotation)
            rotationAccelerationX =
                    sgn(rotationAccelerationX) * maxRotation;
    }
    else
    {
        if ((sgn(rotationAccelerationX) * rotationAccelerationX) < rotationThresholdX)
            rotationAccelerationX = 0;


        if (rotationAccelerationX != 0)
            rotationAccelerationX -= sgn(rotationAccelerationX) * drag * deltaTime;
    }
}
