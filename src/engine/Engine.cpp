#include "Engine.h"
#include "input/InputManager.h"
#include "window/WindowManager.h"
#include <imgui/ImGuiManager.h>
#include <imgui.h>


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
        
        for (Updatable* currentUpdatable : updatableList)
        {
            currentUpdatable->Update();
        }

        renderManager.Clear();

        ImGuiManager::NewFrame();

        renderManager.Render(windowManager, sceneManager);

        ImGui::Begin("Properties");
        std::string fps("FPS: ");
        fps += std::to_string((int)ImGui::GetIO().Framerate);
        ImGui::Text(fps.c_str());
        ImGui::End();

        ImGuiManager::Render();

        glfwSwapBuffers(windowManager.window);
        glfwPollEvents();
    }
}

void Engine::AttachUpdatable(Updatable* object)
{
    updatableList.push_back(object);
}

void Engine::DetachUpdatable(Updatable* object)
{
    updatableList.erase(std::remove(updatableList.begin(), updatableList.end(), object), updatableList.end());
}
