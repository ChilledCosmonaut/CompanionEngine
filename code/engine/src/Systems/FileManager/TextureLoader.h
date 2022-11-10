#pragma once

#include <iostream>

#include <stb_image.h>

namespace gl3::engine::filesystem {
    class TextureLoader {
    public:
        static unsigned int TextureFromFile(std::filesystem::path filepath, bool gamma = false);
    };
}