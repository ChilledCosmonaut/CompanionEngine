#pragma once

#include "engine/Systems/Graphics/shader.h"
#include "engine/Systems/Graphics/mesh.h"

namespace gl3::engine::Graphics {

    struct Model {

    public:
        // model data
        vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection = false;
        std::string path;
        std::shared_ptr<Graphics::shader> shader = nullptr;

        // constructor, expects a filepath to a 3D model.
        //explicit Model(std::string const path, bool gamma = false) : path(path), gammaCorrection(gamma) {}
    };
}
