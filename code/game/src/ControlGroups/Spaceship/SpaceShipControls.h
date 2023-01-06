#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "engine/Systems/Input/InputGroup.h"

namespace game::controls {
    using namespace gl3::engine::inputSystem;

    class SpaceshipTranslationControls : InputGroup {
    public:
        void UpdateKeys(GLFWwindow *window) override;
        glm::vec3 GetInputVector();

    private:
        float GetXInput(GLFWwindow *window);
        float GetYInput(GLFWwindow *window);
        float GetZInput(GLFWwindow *window);

        glm::vec3 inputVector {0.0f, 0.0f, 0.0f};
    };

    class SpaceshipRotationControls : InputGroup {
    public:
        void UpdateKeys(GLFWwindow *window) override;
        glm::vec3 GetInputVector();

    private:
        glm::vec2 HandleMouseInput(GLFWwindow *window);
        float GetZInput(GLFWwindow *window);

        glm::vec3 inputVector {0.0f, 0.0f, 0.0f};
    };
}