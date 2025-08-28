#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include "observer/Subject.h"

class InputManager : public Subject {
public:
	struct MouseMovementEvent {
		float x;
		float y;
	};

	struct KeyEvent {
		int key;
	};

	InputManager();
	static void ProcessMouseInput(GLFWwindow* window, double xpos, double ypos);
	void Initialize();
	void Destroy();
	void ProcessKeyboardInput(GLFWwindow* window);

private:
	static float lastX;
	static float lastY;
	static bool firstMouse;
};