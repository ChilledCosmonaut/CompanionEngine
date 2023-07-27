#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "engine/Systems/Graphics/shader.h"
#include "generated/Assets.h"
#include "../../../../../src/Systems/Graphics/ModelData.h"

namespace gl3::engine::Graphics {

    /// Model component
    struct Model {
    public:
        /// Asset id of rendered model
        assets::Models modelName;
        /// Model data for the renderer
        ModelData modelData;
        /// Material reference for the model
        Material material;
        /// Shader to be used while rendering the model
        std::shared_ptr <Graphics::shader> shader = nullptr;


        // constructor, expects a filepath to a 3D model.
        //explicit Model(std::string const path, bool gamma = false) : path(path), gammaCorrection(gamma) {}
    };
}
