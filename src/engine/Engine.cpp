#include "Engine.h"
#include "input/InputManager.h"
#include "window/WindowManager.h"
#include <imgui.h>
#include <imgui/UIObject.h>
#include <imgui/ImGuiManager.h>
#include <scene/Material.h>
#include <scene/GameObject.h>


Engine& Engine::GetInstance() {
    static Engine instance;
    return instance;
}

void Engine::Initialize() {
    componentManager.RegisterComponent<Transform>();
    componentManager.RegisterComponent<Model>();
    componentManager.RegisterComponent<Material>();
    componentManager.RegisterComponent<UIObject>();

    windowManager.Initialize();
    imguiManager.Initialize(windowManager.window);
    inputManager.Initialize();

    sceneManager.Initialize();
    renderManager.Initialize();
}

void Engine::Destroy() {
    imguiManager.Destroy();
}

void Engine::StartLoop() {
    while(!glfwWindowShouldClose(windowManager.window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime          = currentFrame - lastFrame;
        lastFrame          = currentFrame;

        for(std::shared_ptr<Updatable>& currentUpdatable : updatableList) {
            currentUpdatable->Update();
        }

        renderManager.Clear();

        imguiManager.NewFrame();

        renderManager.Render(windowManager, sceneManager);

        imguiManager.RenderUIData();

        imguiManager.Render();

        glfwSwapBuffers(windowManager.window);
        glfwPollEvents();
    }
}


void Engine::AttachUpdatable(std::shared_ptr<Updatable> object) {
    updatableList.push_back(object);
}

void Engine::DetachUpdatable(std::shared_ptr<Updatable> object) {
    updatableList.erase(std::remove(updatableList.begin(), updatableList.end(), object),
    updatableList.end());
}
