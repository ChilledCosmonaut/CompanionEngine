#pragma once

#include <filesystem>
#include <iostream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "TextureLoader.h"
#include "../Graphics/ModelData.h"

namespace gl3::engine::filesystem {

    class ModelLoader {
    public:
        static void LoadModel(Graphics::ModelData &modelData, const std::filesystem::path &path);

    private:
        static void ProcessNode(Graphics::ModelData &modelData, aiNode *node, const aiScene *scene);

        static Graphics::Mesh ProcessMesh(Graphics::ModelData &modelData, aiMesh *mesh, const aiScene *scene);

        static std::vector<Graphics::Texture> LoadMaterialTextures
        (Graphics::ModelData &modelData, aiMaterial *mat, aiTextureType type, std::string typeName);
    };
}