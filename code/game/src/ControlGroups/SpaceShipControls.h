#pragma once

#include "glm/vec3.hpp"

#include "engine/Systems/Input/InputGroup.h"

namespace game::controls {
    using namespace gl3::engine::inputSystem;

    class SpaceShipControls : InputGroup {
    public:
        void UpdateKeys(GLFWwindow *window) override;
        glm::vec3 GetInputVector();

    private:
        float GetXInput();
        float GetYInput();
        float GetZInput();

        glm::vec3 inputVector {0.0f, 0.0f, 0.0f};
    };
}