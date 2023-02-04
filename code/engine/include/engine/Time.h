#pragma once

#include <GLFW/glfw3.h>

namespace gl3::engine {

    /// Tracks the used time up by the game cycle
    class Time {
        friend class Game;

    public:
        /**
         * Returns the time which past since last frame
         * @return Delta time as float
         */
        static float GetDeltaTime(){
            return deltaTime;
        }

    private:
        static void updateDeltaTime() {
            float frameTime = glfwGetTime();
            deltaTime = frameTime - lastFrameTime;
            lastFrameTime = frameTime;
        }

        static inline float deltaTime = 1.0f / 60;
        static inline float lastFrameTime = 1.0f / 60;
    };
}