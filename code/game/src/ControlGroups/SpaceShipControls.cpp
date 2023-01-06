#include "SpaceShipControls.h"

namespace game::controls {

    void SpaceShipControls::UpdateKeys(GLFWwindow *window) {
        inputVector = glm::vec3(0.0f, 0.0f, 0.0f);

        inputVector.x = GetXInput(window);
        inputVector.y = GetYInput(window);
        inputVector.z = GetZInput(window);
    }

    glm::vec3 SpaceShipControls::GetInputVector() {
        return inputVector;
    }

    float SpaceShipControls::GetXInput(GLFWwindow *window) {
        int input = glfwGetKey(window, GLFW_KEY_A);
        input -= glfwGetKey(window, GLFW_KEY_D);

        return input;
    }

    float SpaceShipControls::GetYInput(GLFWwindow *window) {
        int input = glfwGetKey(window, GLFW_KEY_SPACE);
        input -= glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL);

        return input;
    }

    float SpaceShipControls::GetZInput(GLFWwindow *window) {
        int input = glfwGetKey(window, GLFW_KEY_W);
        input -= glfwGetKey(window, GLFW_KEY_S);

        return input;
    }
}
