#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "engine/Systems/Input/InputGroup.h"

namespace game::controls {
    using namespace gl3::engine::inputSystem;

    class SpaceshipTranslationControls : public InputGroup {
    public:
        void UpdateKeys(GLFWwindow *window) override;
        glm::vec3 GetInputVector();

    private:
        static float GetXInput(GLFWwindow *window) {};
        static float GetYInput(GLFWwindow *window) {};
        static float GetZInput(GLFWwindow *window);

        glm::vec3 inputVector {0.0f, 0.0f, 0.0f};
    };

    class SpaceshipRotationControls : public InputGroup {
    public:
        void UpdateKeys(GLFWwindow *window) override;
        glm::vec3 GetInputVector();

    private:
        static glm::vec2 HandleMouseInput(GLFWwindow *window);
        static float GetZInput(GLFWwindow *window);

        glm::vec3 inputVector {0.0f, 0.0f, 0.0f};
    };
}