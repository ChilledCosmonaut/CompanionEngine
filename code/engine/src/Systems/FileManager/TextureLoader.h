#pragma once

#include <iostream>
#include <filesystem>

#include <stb_image.h>
#include <glad/glad.h>

namespace gl3::engine::filesystem {
    class TextureLoader {
    public:
        static unsigned int TextureFromFile(std::filesystem::path filepath, bool gamma = false);
    };
}