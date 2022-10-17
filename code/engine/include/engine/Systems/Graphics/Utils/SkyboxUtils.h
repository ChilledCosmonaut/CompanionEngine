#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Components/Skybox.h"

namespace gl3::engine::Graphics::Utils {

    class SkyboxUtils {

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

    public:

        static void SetupSkybox(Graphics::Scene& scene){
            auto registry = scene.getRegistry();
            auto componentView = registry->view<Components::SkyboxComponent>();

            for(auto& entity : componentView){
                auto& skybox = componentView.get<Components::SkyboxComponent>(entity);
                glGenVertexArrays(1, &skybox.VAO);
                glGenBuffers(1, &skybox.VBO);
                glBindVertexArray(skybox.VAO);
                glBindBuffer(GL_ARRAY_BUFFER, skybox.VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(skybox.vertices), &skybox.vertices, GL_STATIC_DRAW);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);

                skybox.texture = loadCubemap(skybox.faces);
            }
        }

        void SetVAO(Components::SkyboxComponent &skybox, GLuint vao) {
            skybox.VAO = vao;
        }

        void SetVBO(Components::SkyboxComponent &skybox, GLuint vbo) {
            skybox.VBO = vbo;
        }

        void SetTexture(Components::SkyboxComponent &skybox, GLuint newTexture) {
            skybox.texture = newTexture;
        }
    };
}