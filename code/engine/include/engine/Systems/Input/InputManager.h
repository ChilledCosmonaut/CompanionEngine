#pragma once

#include <vector>
#include <functional>

#include "InputGroup.h"
#include "../../../../src/ECS/CoreSystem.h"

namespace gl3::engine::inputSystem {
    class InputManager : Ecs::CoreSystem {
    public:
        /// Need to adhere to the singleton pattern
        static InputManager *GetInputManager();

        /// Need to adhere to the singleton pattern
        static void DestroyInputManager();

        void UpdateInput(GLFWwindow *window);

    private:
        InputManager() = default;

        ~InputManager() override = default;

        std::vector<InputGroup> inputGroups {};
        static inline inputSystem::InputManager* inputManager;
    };
}