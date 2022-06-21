#pragma once

#include "engine/GraphicsEngine/Components/Camera.h"

namespace gl3::engine::Graphics::Utils {
    class CameraUtils{
    public:
        static glm::mat4 GetViewMatrix(Components::CameraComponent &camera, Components::Transform &transform){
            return camera.lookAtMatrix * transform.GetInverseModelMatrix();
        }
    };
}
