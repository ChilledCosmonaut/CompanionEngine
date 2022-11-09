#pragma once

#include "engine/Systems/Graphics/shader.h"
#include "engine/Systems/Graphics/mesh.h"
#include "engine/Systems/FileManager/Test.h"

namespace gl3::engine::Graphics {

    struct ModelData {

    public:
        vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        basic_string<char, char_traits<char>, allocator<char>> directory;
        bool gammaCorrection = false;
        std::filesystem::path path;
        std::shared_ptr<Graphics::shader> shader = nullptr;

    };

    struct Model {

    public:
        assets::Models modelName;
        // model data
        ModelData modelData;
        std::shared_ptr<Graphics::shader> shader = nullptr;


        // constructor, expects a filepath to a 3D model.
        //explicit Model(std::string const path, bool gamma = false) : path(path), gammaCorrection(gamma) {}
    };
}
