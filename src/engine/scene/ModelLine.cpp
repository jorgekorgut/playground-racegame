#include "ModelLine.h"
#include <vector>
#include "MeshLine.h"

ModelLine::ModelLine()
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh::Vertex vertexStart = {glm::vec3(-0.5,0,0), glm::vec3(0)};
    Mesh::Vertex vertexEnd = {glm::vec3(0.5,0,0), glm::vec3(0)};

	vertices.push_back(vertexStart);
	vertices.push_back(vertexEnd);
	indices.push_back(0);
    indices.push_back(1);

    meshes.emplace_back(std::make_unique<MeshLine>(vertices, indices));
}

ModelLine::~ModelLine()
{

}

