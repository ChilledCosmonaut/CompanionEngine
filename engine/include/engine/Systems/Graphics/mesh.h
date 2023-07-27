#pragma once

#include "shader.h"
#include "engine/Systems/Graphics/Components/Material.h"

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
        glm::vec3 Tangent;
        glm::vec3 BiTangent;
    };

    class Mesh {
    public:
        // mesh data
        vector<Vertex> vertices;
        vector<unsigned int> indices;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

        void Draw(Graphics::shader &shader, Graphics::Material &material) const;

    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
    };
}
