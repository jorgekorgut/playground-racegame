#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include "observer/Subject.h"

class InputManager : public Subject {
public:
	
	InputManager();
	void Initialize();
	void Destroy();
	void Update(GLFWwindow* window);

};