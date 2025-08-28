#include "InputManager.h"
#include "Engine.h"

bool InputManager::firstMouse = true;
float InputManager::lastX = 0;
float InputManager::lastY = 0;

InputManager::InputManager()
{
}

void InputManager::Initialize()
{
    glfwSetInputMode(Engine::GetInstance().windowManager.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(Engine::GetInstance().windowManager.window, InputManager::ProcessMouseInput);
}

void InputManager::Destroy()
{

}

void InputManager::ProcessMouseInput(GLFWwindow* window, double xpos, double ypos)
{
    float fxpos = (float)xpos;
    float fypos = (float)ypos;

    if (firstMouse)
    {
        lastX = fxpos;
        lastY = fypos;
        firstMouse = false;
    }

    float xoffset = fxpos - lastX;
    float yoffset = lastY - fypos;

    lastX = fxpos;
    lastY = fypos;

	MouseMovementEvent mme = MouseMovementEvent{ xoffset, yoffset };
	Engine::GetInstance().inputManager.Notify(Observer::Action::MOUSE_MOVED, (void*)&mme);
}

void InputManager::ProcessKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

    for(int i = 32; i < 341; i++)
    {
        if(glfwGetKey(window, i) == GLFW_PRESS)
        {
            KeyEvent ke = KeyEvent{ i };
            Notify(Observer::Action::KEY_PRESSED, (void*)&ke);
        }
        else if(glfwGetKey(window, i) == GLFW_RELEASE)
        {
			KeyEvent ke = KeyEvent{ i };
            Notify(Observer::Action::KEY_RELEASED, (void*)&ke);
        }
	}
}