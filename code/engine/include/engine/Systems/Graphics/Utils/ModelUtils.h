#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Components/Model.h"
#include "TransformUtils.h"

namespace gl3::engine::Graphics::Utils {

    using namespace std;

    class ModelUtils {
    public:

        static void SetPath(Components::Model &model, std::string path){
            model.path = path;
        }

        static void SetShader(Components::Model &model, std::shared_ptr<engine::Graphics::shader> shader){
            model.shader = shader;
        }

    private:
        static inline glm::vec3 lightPos = glm::vec3(0.0f, -0.5f, 1.0f);
    };
}