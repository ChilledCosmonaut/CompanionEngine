#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "soloud_wav.h"

#include "engine/Scene.h"
#include "generated/Assets.h"

#include "../../../../src/Systems/FileManager/stb_image.h"
#include "../../../../src/Systems/FileManager/Cache.h"
#include "../../../../src/Systems/FileManager/ModelLoader.h"
#include "../../../../src/Systems/FileManager/FontLoader.h"

typedef typename std::pair<assets::Shaders, assets::Shaders> shaderId;
typedef typename std::pair<assets::Fonts, int> fontId;

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

namespace std{
    template<>
    struct std::hash<fontId>
    {
        size_t operator()(const fontId& fonts) const
        {
            return hash<std::string>()(assets::AssetTranslator::TranslateFonts(fonts.first).string() + to_string(fonts.second));
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

    /**
     * Simple file manager for caching assets.
     * File Manager caches all assets via specialized LRU caches. This also the user to dynamically create assets
     * from anywhere inside the game without retaining references or pointers to minimize file loading impact. As
     * long as a file is still used the asset can be used. Even if the asset git already pushed outside the cache.
     * Also nearly all request to the file system are already taken care of  by the engine.
     */
    class FileManager {
    public:

        static FileManager *GetFileManager();

        static void DestroyFileManager();

        /**
         * Retrieves a new shader pointer by requesting it from the cache.
         * @param vertexShader Vertex Shader asset id
         * @param fragmentShader Fragment Shader asset id
         * @return Pointer to created shader program
         */
        std::shared_ptr<Graphics::shader> getAsset(assets::Shaders vertexShader, assets::Shaders fragmentShader);

        /**
         * Retrieves a new model pointer by requesting it from the cache.
         * @param model Model asset id
         * @return Pointer to created model
         */
        std::shared_ptr<Graphics::ModelData> getAsset(assets::Models model);

        /**
         * Retrieves a new model pointer by requesting it from the cache.
         * @param model Model asset id
         * @return Pointer to created model
         */
        std::shared_ptr<SoLoud::Wav> getAsset(assets::Sounds sound);

        /**
         * **Deprecated!!** Retrieves a new material pointer by requesting it from the cache.
         * @param model Material asset id
         * @return Pointer to created material
         */
        std::string getAsset(assets::Materials material);

        /**
         * Retrieves a new image pointer by requesting it from the cache.
         * @param model Image asset id
         * @return Pointer to created image
         */
        std::shared_ptr<Graphics::Texture> getAsset(assets::Images image);

        /**
         * Retrieves a new font pointer by requesting it from the cache.
         * @param model Font asset id
         * @return Pointer to created font map
         */
        std::shared_ptr<std::map<GLchar, Character>> getFont(assets::Fonts font, int fontSize);

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
        std::unique_ptr<Cache<assets::Sounds, SoLoud::Wav>> soundCache;
        std::unique_ptr<Cache<assets::Materials, int>> materialCache;
        std::unique_ptr<Cache<assets::Images, Graphics::Texture>> imageCache;
        std::unique_ptr<Cache<fontId, std::map<GLchar, Character>>> fontCache;
    };
}
