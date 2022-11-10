#include "GraphicsSystem.h"

namespace gl3::engine::Graphics {

    GraphicsSystem *GraphicsSystem::GetGraphicsSystem() {
        if (graphicsSystem == nullptr)
            graphicsSystem = new GraphicsSystem();
        return graphicsSystem;
    }

    void GraphicsSystem::DestroyGraphicsSystem() {
        graphicsSystem->~GraphicsSystem();
        graphicsSystem = nullptr;
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
        auto skyboxView = registry.view<Skybox, Ecs::Flags::Setup<Skybox>>();

        for(auto& entity : skyboxView){
            auto& skybox = skyboxView.get<Skybox>(entity);
            glGenVertexArrays(1, &skybox.VAO);
            glGenBuffers(1, &skybox.VBO);
            glBindVertexArray(skybox.VAO);
            glBindBuffer(GL_ARRAY_BUFFER, skybox.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(skybox.vertices), &skybox.vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);

            skybox.texture = loadCubemap(skybox.faces);
            Ecs::Registry::RemoveSetupFlag<Skybox>(entity);
        }

        auto modelView = registry.view<Model, Ecs::Flags::Setup<Model>>();

        for(auto& entity : modelView){
            auto& model = modelView.get<Model>(entity);
            model.modelData = *fileManager->getAsset(model.modelName);
            Ecs::Registry::RemoveSetupFlag<Model>(entity);
        }
    }

    void GraphicsSystem::Update() {
        auto projectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

        auto& registry = Ecs::Registry::getCurrent();

        glm::mat4 viewMatrix;
        glm::vec3 cameraTranslation;

        auto cameraView = registry.view<Graphics::Camera, Graphics::Transform>();

        for (auto &&[entity, camera, transform] : cameraView.each()) {
            viewMatrix = TransformationUtils::GetViewMatrix(camera,transform);
            cameraTranslation = transform.translation;
            break;
        }

        auto skyboxView = registry.view<Skybox>();

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

        auto modelView = registry.view<Model, Transform>();

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

    void GraphicsSystem::Draw(Model &model) {
        for (auto &mesh: model.modelData.meshes)
            mesh.Draw(*model.shader);

    }

    void GraphicsSystem::Shutdown() {

    }

    GraphicsSystem::GraphicsSystem() {
        fileManager = filesystem::FileManager::GetFileManager();
    }

    GraphicsSystem::~GraphicsSystem() {

    }
}

