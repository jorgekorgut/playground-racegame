#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::Initialize()
{

}

void InputManager::Destroy()
{

}

void InputManager::Update(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

    for(int i = 65; i < 90; i++)
    {
        if(glfwGetKey(window, i) == GLFW_PRESS)
        {
            Notify(Observer::Action::KEY_PRESSED, i);
        }
        else if(glfwGetKey(window, i) == GLFW_RELEASE)
        {
            Notify(Observer::Action::KEY_RELEASED, i);
        }
	}
}