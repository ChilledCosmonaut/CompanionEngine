#pragma once

#include "engine/GraphicsEngine/Scene.h"
#include "engine/GraphicsEngine/Components/Skybox.h"

namespace gl3::engine::Graphics::Systems {
    class SkyboxRenderer {
    public:
        SkyboxRenderer() = default;
        ~SkyboxRenderer() = default;

        void SetupSkybox(Graphics::Scene& scene){
            auto registry = scene.getRegistry();
            auto components = registry->view<Components::SkyboxComponent>();

            for(auto& component : components){
                glGenVertexArrays(1, &component.VAO);
                glGenBuffers(1, &component.VBO);
                glBindVertexArray(component.VAO);
                glBindBuffer(GL_ARRAY_BUFFER, component.VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(component.vertices), &component.vertices, GL_STATIC_DRAW);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);

                component.texture = loadCubemap(component.faces);
            }
        }

        void render(const glm::mat4 &view, const glm::mat4 &projection);

    private:
        unsigned int m_skyboxVAO;
        unsigned int m_skyboxVBO;
        unsigned int m_skyboxTexture;
    };
}