#pragma once

#include <GLFW/glfw3.h>

namespace gl3::engine::inputSystem {

    class InputGroup {
    public:
        virtual void UpdateKeys(GLFWwindow *window) {};
    };
}