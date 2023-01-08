#include <glm/geometric.hpp>
#include "SpaceShipControls.h"

namespace game::controls {

    void SpaceshipTranslationControls::UpdateKeys(GLFWwindow *window) {
        inputVector = glm::vec3(0.0f, 0.0f, 0.0f);

        /*inputVector.x = GetXInput(window);
        inputVector.y = GetYInput(window);*/
        inputVector.z = GetZInput(window);
    }

    glm::vec3 SpaceshipTranslationControls::GetInputVector() {
        return inputVector;
    }/*

    float SpaceshipTranslationControls::GetXInput(GLFWwindow *window) {
        int input = glfwGetKey(window, GLFW_KEY_A);
        input -= glfwGetKey(window, GLFW_KEY_D);

        return input;
    }

    float SpaceshipTranslationControls::GetYInput(GLFWwindow *window) {
        int input = glfwGetKey(window, GLFW_KEY_SPACE);
        input -= glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);

        return input;
    }*/

    float SpaceshipTranslationControls::GetZInput(GLFWwindow *window) {
        int input = glfwGetKey(window, GLFW_KEY_S);
        input -= glfwGetKey(window, GLFW_KEY_W);

        return input;
    }

    void SpaceshipRotationControls::UpdateKeys(GLFWwindow *window) {
        inputVector = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::vec2 mousePosition = HandleMouseInput(window);

        inputVector.x = mousePosition.x;
        inputVector.y = mousePosition.y;
        inputVector.z = GetZInput(window);

        inputVector = glm::normalize(inputVector);
    }

    glm::vec3 SpaceshipRotationControls::GetInputVector() {
        return inputVector;
    }

    glm::vec2 SpaceshipRotationControls::HandleMouseInput(GLFWwindow *window) {
        glm::dvec2 mousePosition;
        glfwGetCursorPos(window, &mousePosition.y, &mousePosition.x);

        glm::ivec2 screenSize;
        glfwGetWindowSize(window, &screenSize.y, &screenSize.x);

        mousePosition -= screenSize/2; //Orient mouse position to middle of the screen
        mousePosition /= screenSize/2; //Scale position to range between -1 and 1

        bool outsideDeadZone = glm::length(mousePosition) > 0.3f; //Calculates if mouse is outside dead zone

        return mousePosition * (double) outsideDeadZone;
    }

    float SpaceshipRotationControls::GetZInput(GLFWwindow *window) {
        int input = glfwGetKey(window, GLFW_KEY_D);
        input -= glfwGetKey(window, GLFW_KEY_A);

        return input;
    }
}
