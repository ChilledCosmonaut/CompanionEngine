#pragma once

#include "shader.h"

#include "glm/vec2.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <vector>
#include <utility>

namespace gl3::engine::Graphics {
    using namespace std;

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture {
        unsigned int id;
        string type;
        aiString path;
    };

    class Mesh {
    public:
        // mesh data
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

        void Draw(Graphics::shader &shader);

    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
    };
}
