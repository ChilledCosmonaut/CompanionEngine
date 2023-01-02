#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Components/Model.h"
#include "TransformationUtils.h"

namespace gl3::engine::Graphics {

    using namespace std;

    class ModelUtils {
    public:

        static void SetShader(Model &model, std::shared_ptr<engine::Graphics::shader> shader){
            model.shader = shader;
        }

    private:
        static inline glm::vec3 lightPos = glm::vec3(0.0f, -0.5f, 1.0f);
    };
}