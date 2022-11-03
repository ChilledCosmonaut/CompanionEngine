#include "ModelLoader.h"

namespace gl3::engine::filesystem {

    void ModelLoader::LoadModel(const std::filesystem::path &path) {
        auto model = Graphics::Model();

        // read file via ASSIMP
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                                       aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }

        // process ASSIMP's root node recursively
        ProcessNode(model, scene->mRootNode, scene);
    }

    void ModelLoader::ProcessNode(Graphics::Model &modelData, aiNode *node, const aiScene *scene) {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            modelData.meshes.push_back(ProcessMesh(modelData, mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(modelData ,node->mChildren[i], scene);
        }
    }

    Graphics::Mesh ModelLoader::ProcessMesh(Graphics::Model &modelData, aiMesh *mesh, const aiScene *scene) {
        std::vector<Graphics::Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Graphics::Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Graphics::Vertex vertex;
            // process vertex positions, normals and texture coordinates
            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            } else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            vertices.push_back(vertex);
        }
        // process indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process material
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Graphics::Texture> diffuseMaps = loadMaterialTextures(modelData, material,
                                                               aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Graphics::Texture> specularMaps = loadMaterialTextures(modelData, material,
                                                                aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Graphics::Mesh(vertices, indices, textures);
    }
}