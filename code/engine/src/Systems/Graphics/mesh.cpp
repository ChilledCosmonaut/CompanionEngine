#include <iostream>
#include "engine/Systems/Graphics/mesh.h"

namespace gl3::engine::Graphics {

    Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        /*this->textures = textures;*/

        setupMesh();
    }

    void Mesh::Draw(Graphics::shader &shader, Graphics::Material &material) const {
        // activate proper texture unit before binding
        if (material.ambient != nullptr) {
            glActiveTexture(GL_TEXTURE0);
            shader.setFloat("material.ambient", GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, material.ambient->id);
        }

        if (material.diffuse != nullptr) {
            glActiveTexture(GL_TEXTURE1);
            shader.setFloat("material.diffuse", GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, material.diffuse->id);
        }

        if (material.specular != nullptr) {
            glActiveTexture(GL_TEXTURE2);
            shader.setFloat("material.specular", GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, material.specular->id);
        }

        if (material.normal != nullptr) {
            glActiveTexture(GL_TEXTURE3);
            shader.setFloat("material.normal", GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, material.normal->id);
        }

        shader.setFloat("material.shininess", material.shininess);

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                     &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Tangent));
        // vertex biTangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, BiTangent));

        glBindVertexArray(0);
    }
}