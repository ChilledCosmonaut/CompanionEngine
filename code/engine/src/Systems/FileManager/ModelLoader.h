#pragma once

#include <filesystem>
#include <iostream>

#include "engine/Systems/Graphics/Components/Model.h"

namespace gl3::engine::filesystem {

    class ModelLoader {
    public:
        static void LoadModel(const std::filesystem::path &path);

    private:
        static void ProcessNode(Graphics::Model &modelData, aiNode *node, const aiScene *scene);

        static Graphics::Mesh ProcessMesh(Graphics::Model &modelData, aiMesh *mesh, const aiScene *scene);
    };
}