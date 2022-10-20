#pragma once

#include "engine/Systems/Graphics/Components/Camera.h"

namespace gl3::engine::Graphics {
    class CameraUtils{
    public:
        static glm::mat4 GetViewMatrix(Camera &camera, Components::Transform &transform){
            return camera.lookAtMatrix * transform.inverseModelMatrix;
        }
    };
}
