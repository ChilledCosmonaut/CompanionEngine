#include "SpaceShipControls.h"

namespace game::controls {

    void SpaceShipControls::UpdateKeys(GLFWwindow *window) {
        inputVector = glm::vec3(0.0f, 0.0f, 0.0f);

        inputVector.x = GetXInput();
        inputVector.y = GetYInput();
        inputVector.z = GetZInput();
    }

    glm::vec3 SpaceShipControls::GetInputVector() {
        return inputVector;
    }
}
