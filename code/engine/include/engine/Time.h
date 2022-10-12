#pragma once

#include <GLFW/glfw3.h>

namespace gl3::engine {
    class Time {
        friend class Game;

    public:
        static float GetDeltaTime(){
            return deltaTime;
        }

        static void updateDeltaTime() {
            float frameTime = glfwGetTime();
            deltaTime = frameTime - lastFrameTime;
            lastFrameTime = frameTime;
        }

    private:

        static inline float deltaTime = 1.0f / 60;
        static inline float lastFrameTime = 1.0f / 60;
    };
}