#pragma once

#include "engine/Systems/Graphics/mesh.h"
#include "generated/Assets.h"


namespace gl3::engine::Graphics {

    struct ModelData {

    public:
        vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        basic_string<char, char_traits<char>, allocator<char>> directory;
        bool gammaCorrection = false;
    };
}