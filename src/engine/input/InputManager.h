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

	struct MouseButtonEvent {
		int button;
		int action;
	};

	InputManager();
	static void ProcessMouseMoveInput(GLFWwindow* window, double xpos, double ypos);
	static void ProcessMouseButtonInput(GLFWwindow* window, int button, int action, int mods);
	static void ProcessKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool IsCursorOverImGuiWindow();

	void Initialize();
	void Destroy();
	static void SetMenuMode(bool enabled);

private:
	static bool isMenuMode;
	static float lastX;
	static float lastY;
	static bool firstMouse;
};