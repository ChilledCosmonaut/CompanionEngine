#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "engine/Systems/Graphics/shader.h"
#include "engine/Systems/FileManager/Test.h"
#include "../../../../../src/Systems/Graphics/ModelData.h"

namespace gl3::engine::Graphics {

    struct Model {

    public:
        assets::Models modelName;
        // model data
        ModelData modelData;
        std::shared_ptr <Graphics::shader> shader = nullptr;


        // constructor, expects a filepath to a 3D model.
        //explicit Model(std::string const path, bool gamma = false) : path(path), gammaCorrection(gamma) {}
    };
}
