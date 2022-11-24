#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace gl3::engine::filesystem {

    /// Holds all state information relevant to a character as loaded using FreeType
    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };

    class FontLoader {
    public:
        static void LoadFont(std::shared_ptr<std::map<GLchar, Character>> fontMap, const std::filesystem::path &path, int fontSize);
    };
}