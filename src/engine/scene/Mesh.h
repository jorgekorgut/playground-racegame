#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "shader/Shader.h"

class Mesh 
{
public:
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    glm::vec3 color = glm::vec3(0);

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 & color);
    void UpdateVertexPosition(std::vector<glm::vec3>& positions);
    void Render(Shader& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};