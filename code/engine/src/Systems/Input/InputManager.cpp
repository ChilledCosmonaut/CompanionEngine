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

    void InputManager::UpdateInput() {
        for (auto group:inputGroups) {
            group.UpdateKeys();
        }
    }
}