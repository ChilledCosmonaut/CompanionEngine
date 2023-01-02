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

            skybox.texture = filesystem::TextureLoader::LoadCubemap(skybox.faces);
            Ecs::Registry::RemoveSetupFlag<Skybox>(entity);
        }

        auto modelView = registry.view<Model, Ecs::Flags::Setup<Model>>();

        for(auto& entity : modelView){
            auto& model = modelView.get<Model>(entity);
            model.modelData = *fileManager->getAsset(model.modelName);
            Ecs::Registry::RemoveSetupFlag<Model>(entity);
        }

        auto textView = registry.view<Text, Ecs::Flags::Setup<Text>>();

        for(auto& entity : textView){
            auto& text = textView.get<Text>(entity);

            glGenVertexArrays(1, &text.VAO);
            glGenBuffers(1, &text.VBO);
            glBindVertexArray(text.VAO);
            glBindBuffer(GL_ARRAY_BUFFER, text.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            text.font = fileManager->getFont(text.fontName, text.fontSize);

            Ecs::Registry::RemoveSetupFlag<Text>(entity);
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

        auto textView = registry.view<Text, Transform>();

        for(auto &&[entity, text, transform] : textView.each()){
            if(!transform.active) continue;
            text.shader->use();

            glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1920), 0.0f, static_cast<float>(1080));
            text.shader->setMatrix("projection", projection);

            // activate corresponding render state
            text.shader->setVector3("textColor", text.color);
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(text.VAO);

            // iterate through all characters
            std::string::const_iterator c;
            float x = transform.translation.x;
            for (c = text.content.begin(); c != text.content.end(); c++)
            {
                filesystem::Character ch = (*text.font)[*c];

                float xpos = x + ch.Bearing.x * transform.scale.x;
                float ypos = transform.translation.y - (ch.Size.y - ch.Bearing.y) * transform.scale.y;

                float w = ch.Size.x * transform.scale.x;
                float h = ch.Size.y * transform.scale.y;
                // update VBO for each character
                float vertices[6][4] = {
                        { xpos,     ypos + h,   0.0f, 0.0f },
                        { xpos,     ypos,       0.0f, 1.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },

                        { xpos,     ypos + h,   0.0f, 0.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },
                        { xpos + w, ypos + h,   1.0f, 0.0f }
                };
                // render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                // update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, text.VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                x += (ch.Advance >> 6) * transform.scale.x; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
            }
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
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
        filesystem::FileManager::DestroyFileManager();
    }
}

