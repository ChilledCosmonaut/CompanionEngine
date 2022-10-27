#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../../../../src/Systems/FileManager/stb_image.h"
#include "engine/Systems/FileManager/Test.h"

namespace gl3::engine::filesystem {
    namespace fs = std::filesystem;

    struct texture{
        int width,
                height,
                colChannel;
        unsigned char *content;
    };

    class FileManager {
    public:
        static std::string getAsset(assets::Shaders shader);
        static std::string getAsset(assets::Models model);
        static std::string getAsset(assets::Sounds sound);
        static std::string getAsset(assets::Materials material);
        static std::string getAsset(assets::Images image);
        static void writeFileToTemp(const char* stringToSave, const fs::path &fileName);
        static void saveFileAt(const char* stringToSave, const fs::path &relativeFilePath);
        static const aiScene* loadModelFromFile(const fs::path &relativeFilePath);
        static texture loadTextureFromFile(const fs::path &relativeFilePath);

    private:

       [[nodiscard]] fs::path static resolveForSubdirectory(const fs::path &relativeAssetPath, const fs::path &subdirectory) {
           return fs::weakly_canonical((subdirectory / relativeAssetPath).make_preferred());
       }
       static std::string readText(const std::filesystem::path &fileName);
       static void saveTextAt(const char* stringToSave, const std::filesystem::path &fileName);
    };
}
