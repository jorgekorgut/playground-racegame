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

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(Mesh& other);
    ~Mesh();
    void UpdateMesh();
    virtual void Render(Shader& shader);

    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;

protected:
    //  render data
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};