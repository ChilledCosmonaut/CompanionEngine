#include "GraphicsSystem.h"

namespace gl3::engine::Graphics::Systems{

    GraphicsSystem *GraphicsSystem::GetGraphicsSystem() {
        if (graphicsSystem == nullptr)
            graphicsSystem = new GraphicsSystem();
        return graphicsSystem;
    }

    void GraphicsSystem::DestroyGraphicsSystem() {
        graphicsSystem->~GraphicsSystem();
        graphicsSystem = nullptr;
    }

    static unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false) {
        string filename = string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        //stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        } else {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }

    static vector<Texture> loadMaterialTextures(Components::Model &modelData, aiMaterial *mat, aiTextureType type, string typeName) {
        vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;
            for (unsigned int j = 0; j < modelData.textures_loaded.size(); j++) {
                if (std::strcmp(modelData.textures_loaded[j].path.data, str.C_Str()) == 0) {
                    textures.push_back(modelData.textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip) {   // if texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), modelData.directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                modelData.textures_loaded.push_back(texture); // add to loaded textures
            }
        }
        return textures;
    }

    static Mesh processMesh(Components::Model &modelData, aiMesh *mesh, const aiScene *scene) {
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
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
            vector<Texture> diffuseMaps = loadMaterialTextures(modelData, material,
                                                               aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            vector<Texture> specularMaps = loadMaterialTextures(modelData, material,
                                                                aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    static void processNode(Components::Model &modelData, aiNode *node, const aiScene *scene) {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            modelData.meshes.push_back(processMesh(modelData, mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(modelData ,node->mChildren[i], scene);
        }
    }

    static void loadModel(Components::Model &modelData, const string &path) {
        /*const aiScene *scene = files::FileManager::loadModelFromFile(path);
        directory = path.substr(0, path.find_last_of('/'));*/
        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                                       aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return;
        }
        // retrieve the directory path of the filepath
        modelData.directory = path.substr(0, path.find_last_of('/'));

        // process ASSIMP's root node recursively
        processNode(modelData, scene->mRootNode, scene);
    }

    static unsigned int loadCubemap(std::vector<std::string> faces)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char *data = stbi_load((std::string("../../assets/textures/SpaceSkybox/").append(faces[i])).c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
    }

    void GraphicsSystem::SetUp() {
        auto& registry = Ecs::Registry::getCurrent();
        auto skyboxView = registry.view<Components::SkyboxComponent, Ecs::Flags::Setup<Components::SkyboxComponent>>();

        for(auto& entity : skyboxView){
            auto& skybox = skyboxView.get<Components::SkyboxComponent>(entity);
            glGenVertexArrays(1, &skybox.VAO);
            glGenBuffers(1, &skybox.VBO);
            glBindVertexArray(skybox.VAO);
            glBindBuffer(GL_ARRAY_BUFFER, skybox.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(skybox.vertices), &skybox.vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);

            skybox.texture = loadCubemap(skybox.faces);
            Ecs::Registry::RemoveSetupFlag<Components::SkyboxComponent>(entity);
        }

        auto modelView = registry.view<Components::Model, Ecs::Flags::Setup<Components::Model>>();

        for(auto& entity : modelView){
            auto& model = modelView.get<Components::Model>(entity);
            loadModel(model,model.path);
            Ecs::Registry::RemoveSetupFlag<Components::Model>(entity);
        }
    }

    void GraphicsSystem::Update() {
        auto projectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

        auto& registry = Ecs::Registry::getCurrent();

        glm::mat4 viewMatrix;
        glm::vec3 cameraTranslation;

        auto cameraView = registry.view<Graphics::Camera, Graphics::Components::Transform>();

        for (auto &&[entity, camera, transform] : cameraView.each()) {
            viewMatrix = CameraUtils::GetViewMatrix(camera,transform);
            cameraTranslation = transform.translation;
            break;
        }

        auto skyboxView = registry.view<Components::SkyboxComponent>();

        for (auto &&[entity, skybox]: skyboxView.each()) {

            glDepthMask(GL_FALSE);
            skybox.shader->use();
            skybox.shader->setMatrix("projection", projectionMatrix);
            skybox.shader->setMatrix("view", viewMatrix);
            glBindVertexArray(skybox.VAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.texture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthMask(GL_TRUE);
        }

        //DisplayLights();

        auto modelView = registry.view<Components::Model, Components::Transform>();

        for(auto &&[entity, model, transform] : modelView.each()){
            if(!transform.active) continue;
            model.shader->use();

            model.shader->setMatrix("projection", projectionMatrix);
            model.shader->setMatrix("view", viewMatrix);

            model.shader->setMatrix("model", transform.modelMatrix);

            model.shader->setVector("viewPos",glm::vec4(cameraTranslation, 1.0f));

            model.shader->setVector3("dirLight.direction", -lightPos);

            model.shader->setVector3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
            model.shader->setVector3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
            model.shader->setVector3("dirLight.specular", glm::vec3(0.7f, 0.7f, 0.7f));

            Draw(model);
        }
    }

    void GraphicsSystem::Draw(Components::Model &modelData) {
        for (auto &mesh: modelData.meshes)
            mesh.Draw(*modelData.shader);

    }

    void GraphicsSystem::Shutdown() {

    }

    GraphicsSystem::GraphicsSystem() {

    }

    GraphicsSystem::~GraphicsSystem() {

    }
}

