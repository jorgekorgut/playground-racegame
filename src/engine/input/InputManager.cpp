#include "InputManager.h"
#include "Engine.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>

bool InputManager::isMenuMode = true;
bool InputManager::firstMouse = true;
float InputManager::lastX = 0;
float InputManager::lastY = 0;

InputManager::InputManager()
{
}

void InputManager::Initialize()
{
    SetMenuMode(true);
    glfwSetKeyCallback(Engine::GetInstance().windowManager.window, InputManager::ProcessKeyboardInput);
    glfwSetCursorPosCallback(Engine::GetInstance().windowManager.window, InputManager::ProcessMouseMoveInput);
    glfwSetMouseButtonCallback(Engine::GetInstance().windowManager.window, InputManager::ProcessMouseButtonInput);
}

void InputManager::Destroy()
{

}

void InputManager::SetMenuMode(bool enabled)
{
    if (enabled == true && isMenuMode == false)
    {
        firstMouse = true;
    }

    isMenuMode = enabled;
    if (enabled)
    {
        glfwSetInputMode(Engine::GetInstance().windowManager.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(Engine::GetInstance().windowManager.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void InputManager::ProcessKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (!isMenuMode)
        return;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        SetMenuMode(false);
    }

    if (action == GLFW_PRESS)
    {
        KeyEvent ke = KeyEvent{ key };
        Engine::GetInstance().inputManager.Notify(Observer::Action::KEY_PRESSED, (void*)&ke);
    }

    if (action == GLFW_RELEASE)
    {
        KeyEvent ke = KeyEvent{ key };
        Engine::GetInstance().inputManager.Notify(Observer::Action::KEY_RELEASED, (void*)&ke);
    }
}

bool InputManager::IsCursorOverImGuiWindow()
{
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureMouse;
}

void InputManager::ProcessMouseButtonInput(GLFWwindow* window, int button, int action, int mods)
{
    if (IsCursorOverImGuiWindow())
    {
        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        return;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        SetMenuMode(true);
    }

    if (action == GLFW_PRESS || action == GLFW_RELEASE)
    {
        MouseButtonEvent mbe = MouseButtonEvent{ button, action };
        Engine::GetInstance().inputManager.Notify(Observer::Action::MOUSE_BUTTON, (void*)&mbe);
    }
}

void InputManager::ProcessMouseMoveInput(GLFWwindow* window, double xpos, double ypos)
{
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

    if(!isMenuMode)
		return;

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
