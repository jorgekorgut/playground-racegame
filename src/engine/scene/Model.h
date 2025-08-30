#pragma once
#include "shader/Shader.h"
#include <vector>
#include "Mesh.h"

class Model
{
public:
    Model() {}

    Model(const Model& other)
    {
        meshes.reserve(other.meshes.size());
        for (unsigned int i = 0; i < other.meshes.size(); i++)
        {
            meshes.push_back(std::make_unique<Mesh>(*other.meshes[i]));
		}
    }

    ~Model()
    {

    }

    virtual void Render(Shader& shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i]->Render(shader);
        }
    }

    std::vector<std::unique_ptr<Mesh>> meshes;
};