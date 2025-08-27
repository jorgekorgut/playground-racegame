#pragma once
#include <shader/Shader.h>

class ResourceManager {
public:
	void Initialize();
	void Destroy();
	static Shader LoadShader(const char* vertexPath = "shaders/DefaultShader.vert", const char* fragmentPath = "shaders/DefaultShader.frag");
};