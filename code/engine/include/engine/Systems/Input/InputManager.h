#pragma once

#include <vector>
#include <functional>
#include <memory>

#include "InputGroup.h"
#include "../../../../src/ECS/CoreSystem.h"

namespace gl3::engine::inputSystem {
    /// Manager for all input groups
    class InputManager : Ecs::CoreSystem {
    public:
        /// Need to adhere to the singleton pattern
        static InputManager *GetInputManager();

        /// Need to adhere to the singleton pattern
        static void DestroyInputManager();

        void UpdateInput(GLFWwindow *window);

        /**
         * Adds a new input group to the input system
         * @param inputGroup Pointer to a user created input group
         */
        void AddInputGroup(std::shared_ptr<InputGroup> inputGroup);

    private:
        InputManager() = default;

        ~InputManager() override = default;

        std::vector<std::shared_ptr<InputGroup>> inputGroups {};
        static inline inputSystem::InputManager* inputManager;
    };
}