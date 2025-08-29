#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 & color)
{
    this->vertices = vertices;
    this->indices = indices;
    this->color = color;

    setupMesh();
}

void Mesh::setupMesh()
{
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glBindVertexArray(0);
}

void Mesh::UpdateVertexPosition(std::vector<glm::vec3> & positions)
{
    if (positions.size() != vertices.size())
    {
        std::cout << "Error: positions size does not match vertices size in Mesh::UpdateVertexPosition" << std::endl;
        return;
    }

	for (size_t i = 0; i < vertices.size(); i++)
    {
        vertices[i].Position = positions[i];
        vertices[i].Normal = glm::vec3(0);
    }

	for (int currentTriangle = 0; currentTriangle < indices.size()/3; currentTriangle++)
    {
        for (int currentVertex = 0; currentVertex < 3; currentVertex++)
        {
            int i0 = 3 * currentTriangle + (currentVertex );
            int i1 = 3 * currentTriangle + (currentVertex + 1) % 3;
            int i2 = 3 * currentTriangle + (currentVertex + 2) % 3;

            glm::vec3 v0 = vertices[indices[i0]].Position;
            glm::vec3 v1 = vertices[indices[(i1) % indices.size()]].Position;
            glm::vec3 v2 = vertices[indices[(i2) % indices.size()]].Position;
            glm::vec3 normal = glm::normalize(glm::cross(v2 - v0, v1 - v0));

            vertices[indices[3 * currentTriangle + currentVertex]].Normal += normal;
			vertices[indices[3 * currentTriangle + currentVertex]].Normal = glm::normalize(vertices[indices[3 * currentTriangle + currentVertex]].Normal);
        }
	}

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::Render(Shader& shader)
{
    shader.setVec3("color", color);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}