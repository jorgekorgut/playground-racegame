#include "Engine.h"
#include "input/InputManager.h"
#include "window/WindowManager.h"


Engine& Engine::GetInstance()
{
    static Engine instance;
    return instance;
}

void Engine::Initialize()
{
	windowManager.Initialize();
	inputManager.Initialize();

    sceneManager.Initialize();
    renderManager.Initialize();
}

void Engine::Destroy()
{

}

void Engine::StartLoop()
{
    while (!glfwWindowShouldClose(windowManager.window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        inputManager.ProcessKeyboardInput(windowManager.window);

        renderManager.Render(windowManager, sceneManager);

        glfwSwapBuffers(windowManager.window);
        glfwPollEvents();
    }
}
