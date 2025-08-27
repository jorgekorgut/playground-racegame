#include "ModelPlane.h"
#include "Mesh.h"
#include <iostream>
#include <shader/Shader.h>


ModelPlane::ModelPlane()
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;
    
    Mesh::Vertex vertex;

    vertex.Position = glm::vec3(0.5f, 0, -0.5f);
    vertex.Normal = glm::vec3(0, 1, 0);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(0.5f, 0, 0.5f);
    vertex.Normal = glm::vec3(0, 1, 0);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(-0.5f, 0, 0.5f);
    vertex.Normal = glm::vec3(0, 1, 0);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(-0.5f, 0, -0.5f);
    vertex.Normal = glm::vec3(0, 1, 0);
    vertices.push_back(vertex);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    glm::vec3 color(1, 0, 0);

    meshes.push_back(Mesh(vertices, indices, color));
}

void ModelPlane::Render(Shader& shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Render(shader);
    }
}
