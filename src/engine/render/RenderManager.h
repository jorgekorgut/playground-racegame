#pragma once
#include <glm/vec4.hpp>
#include "scene/SceneManager.h"
#include "window/WindowManager.h"

class RenderManager {
public:
	RenderManager();
	void Initialize();
	void Destroy();
	void Render(WindowManager& windowManager, SceneManager & sceneManager);
	Shader shader;

private:
	glm::vec4 clearColor = glm::vec4(1.0f);
};