#include "ModelLoader.h"

namespace gl3::engine::filesystem {

    void ModelLoader::LoadModel(Graphics::ModelData &modelData, const std::filesystem::path &path) {
        auto model = Graphics::ModelData();

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
        // retrieve the directory path of the filepath
        modelData.directory = path.parent_path().string();

        // process ASSIMP's root node recursively
        ProcessNode(modelData, scene->mRootNode, scene);
    }

    void ModelLoader::ProcessNode(Graphics::ModelData &modelData, aiNode *node, const aiScene *scene) {
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

    Graphics::Mesh ModelLoader::ProcessMesh(Graphics::ModelData &modelData, aiMesh *mesh, const aiScene *scene) {
        std::vector<Graphics::Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Graphics::Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Graphics::Vertex vertex{};

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

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.BiTangent = vector;

            vertices.push_back(vertex);
        }
        // process indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process material Todo: Check this weird double loading
        /*if (mesh->mMaterialIndex >= 0) {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Graphics::Texture> diffuseMaps = LoadMaterialTextures(modelData, material,
                                                               aiTextureType_DIFFUSE, "diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Graphics::Texture> specularMaps = LoadMaterialTextures(modelData, material,
                                                                aiTextureType_SPECULAR, "specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }*/

        return {vertices, indices, textures};
    }

    /*std::vector<Graphics::Texture>
    ModelLoader::LoadMaterialTextures(Graphics::ModelData &modelData, aiMaterial *mat, aiTextureType type,
                                      std::string typeName) {
        std::vector<Graphics::Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString textureName;
            mat->GetTexture(type, i, &textureName);
            bool skip = false;
            for (unsigned int j = 0; j < modelData.textures_loaded.size(); j++) {
                if (std::strcmp(modelData.textures_loaded[j].path.data, textureName.C_Str()) == 0) {
                    textures.push_back(modelData.textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip) {   // if texture hasn't been loaded already, load it
                Graphics::Texture texture;
                texture.id = TextureLoader::TextureFromFile(modelData.directory.append("\\").append(textureName.C_Str()));
                texture.type = typeName;
                texture.path = textureName.C_Str();
                textures.push_back(texture);
                modelData.textures_loaded.push_back(texture); // add to loaded textures
            }
        }
        return textures;
    }*/
}