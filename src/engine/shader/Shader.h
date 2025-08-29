#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class Shader
{
public:
    // the program ID
    int ID;
    Shader(int ID = -1);

    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec4f(const std::string& name, float x, float y, float z, float w);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec3(const std::string& name, glm::vec3 pos);
    void setMat3(const std::string& name, glm::mat3& mat);
    void setMat4(const std::string& name, glm::mat4& mat);

private :
	GLint getUniformLocation(const std::string& name) const;
    mutable std::unordered_map<std::string, GLint> uniformLocationCache;
};
