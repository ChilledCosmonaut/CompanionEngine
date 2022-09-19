#pragma once

#include "engine/Systems/Graphics/Components/Camera.h"

namespace gl3::engine::Graphics::Utils {
    class CameraUtils{
    public:
        static glm::mat4 GetViewMatrix(Components::CameraComponent &camera, Components::Transform &transform){
            return camera.lookAtMatrix * TransformUtils::GetInverseModelMatrix(transform);
        }
    };
}
