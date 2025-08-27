#pragma once
#include "shader/Shader.h"
#include <vector>
#include "Mesh.h"

class Model
{
public:
    virtual void Render(Shader& shader) = 0;
protected:
    std::vector<Mesh> meshes;
};