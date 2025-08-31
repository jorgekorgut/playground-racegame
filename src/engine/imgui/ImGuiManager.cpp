#include "ImGuiManager.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include "Widget.h"
#include <string>

void ImGuiManager::Initialize(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void ImGuiManager::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::UpdateWidgetsData()
{
    ImGui::Begin("Properties");
    std::string fps("FPS: ");
    fps += std::to_string((int)ImGui::GetIO().Framerate);
    ImGui::Text(fps.c_str());
    
    for (std::shared_ptr<WidgetData>& currentWidget : widgetList)
    {
        currentWidget->UpdateData();
    }

    ImGui::End();
}

void ImGuiManager::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::AttachWidgetData(std::shared_ptr<WidgetData> widgetData)
{
    widgetList.push_back(widgetData);
}

void ImGuiManager::DetachWidgetData(std::shared_ptr<WidgetData> widgetData)
{
    widgetList.erase(std::remove(widgetList.begin(), widgetList.end(), widgetData), widgetList.end());

}

