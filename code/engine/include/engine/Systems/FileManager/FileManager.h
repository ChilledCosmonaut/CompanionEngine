#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../../../../src/Systems/FileManager/stb_image.h"
#include "generated/Assets.h"
#include "../../../../src/Systems/FileManager/Cache.h"
#include "../../../../src/Systems/FileManager/ModelLoader.h"
#include "engine/Scene.h"

typedef typename std::pair<assets::Shaders, assets::Shaders> shaderId;

namespace std{
    template<>
    struct std::hash<shaderId>
    {
        size_t operator()(const shaderId& shaders) const
        {
            return static_cast<std::size_t>(shaders.first)
                   * static_cast<std::size_t>(assets::Shaders::LAST)
                   + static_cast<std::size_t>(shaders.second);
        };
    };
}

namespace gl3::engine::filesystem {
    namespace fs = std::filesystem;

    struct texture {
        int width,
                height,
                colChannel;
        unsigned char *content;
    };

    class FileManager {
    public:

        /// Need to adhere to the singleton pattern
        static FileManager *GetFileManager();

        /// Need to adhere to the singleton pattern
        static void DestroyFileManager();

        std::shared_ptr<Graphics::shader> getAsset(assets::Shaders vertexShader, assets::Shaders fragmentShader);

        std::shared_ptr<Graphics::ModelData> getAsset(assets::Models model);

        std::string getAsset(assets::Sounds sound);

        std::string getAsset(assets::Materials material);

        std::string getAsset(assets::Images image);

        void writeFileToTemp(const char *stringToSave, const fs::path &fileName);

        void saveFileAt(const char *stringToSave, const fs::path &relativeFilePath);

        static texture loadTextureFromFile(const fs::path &relativeFilePath);

    private:

        FileManager();

        ~FileManager();

        [[nodiscard]] fs::path static
        resolveForSubdirectory(const fs::path &relativeAssetPath, const fs::path &subdirectory) {
            return fs::weakly_canonical((subdirectory / relativeAssetPath).make_preferred());
        }

        static std::string readText(const std::filesystem::path &fileName);

        static void saveTextAt(const char *stringToSave, const std::filesystem::path &fileName);

        static inline FileManager *fileManager = nullptr;

        std::unique_ptr<Cache<shaderId, Graphics::shader>> shaderCache;
        std::unique_ptr<Cache<assets::Models, Graphics::ModelData>> modelCache;
        std::unique_ptr<Cache<assets::Sounds, int>> soundCache;
        std::unique_ptr<Cache<assets::Materials, int>> materialCache;
        std::unique_ptr<Cache<assets::Images, int>> imageCache;
    };
}
