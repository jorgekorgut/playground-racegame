#pragma once
#include <glm/vec4.hpp>
#include "scene/SceneManager.h"
#include "window/WindowManager.h"

class RenderManager {
public:
	RenderManager();
	void Initialize();
	void Destroy();
	void Clear();
	void ToggleWireframeMode();
	void Render(WindowManager& windowManager, SceneManager & sceneManager);
	Shader shader;
	Shader debugShader;
private:
	glm::vec4 clearColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
	bool wireframeMode = false;
};