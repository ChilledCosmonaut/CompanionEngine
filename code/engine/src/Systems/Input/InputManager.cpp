#include "engine/Systems/Input/InputManager.h"

namespace gl3::engine::inputSystem {

    InputManager *InputManager::GetInputManager() {
        if (inputManager == nullptr)
            inputManager = new InputManager();
        return inputManager;
    }

    void InputManager::DestroyInputManager() {
        inputManager->~InputManager();
        inputManager = nullptr;
    }

    void InputManager::UpdateInput(GLFWwindow *window) {
        for (auto group:inputGroups) {
            group->UpdateKeys(window);
        }
    }

    void InputManager::AddInputGroup(std::shared_ptr<InputGroup> inputGroup) {
        inputGroups.push_back(inputGroup);
    }
}