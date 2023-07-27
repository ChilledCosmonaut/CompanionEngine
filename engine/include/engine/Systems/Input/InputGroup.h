#pragma once

#include <GLFW/glfw3.h>

namespace gl3::engine::inputSystem {

    /**
     * Parent class of all input groups.
     * Each inheritor should implement a special storage and function to retrieve the polled input.
     */
    class InputGroup {
    public:
        /**
         * Should be implemented by the user to poll correct input.
         * @param window Window reference to poll input from
         */
        virtual void UpdateKeys(GLFWwindow *window) {};
    };
}