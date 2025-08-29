#pragma once
#include <glfw/glfw3.h>

class ImGuiManager{
	public:
	static void Initialize(GLFWwindow* window);
	static void Destroy();

	static void NewFrame();
	static void Render();
};