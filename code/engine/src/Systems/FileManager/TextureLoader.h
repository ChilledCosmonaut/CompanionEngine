#pragma once

#include <iostream>
#include <filesystem>

#include <stb_image.h>
#include <glad/glad.h>

#include "engine/Systems/FileManager/Test.h"

namespace gl3::engine::filesystem {
    class TextureLoader {
    public:
        static unsigned int TextureFromFile(std::filesystem::path filepath, bool gamma = false);

        static unsigned int LoadCubemap(std::vector<assets::Images> faces);
    };
}