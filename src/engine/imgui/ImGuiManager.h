#pragma once
#include <glfw/glfw3.h>
#include "Widget.h"
#include <vector>
#include <memory>

class ImGuiManager{
	public:
	void Initialize(GLFWwindow* window);
	void Destroy();

	void NewFrame();
	void UpdateWidgetsData();
	void Render();
	void AttachWidgetData(std::shared_ptr<WidgetData> widgetData);
	void DetachWidgetData(std::shared_ptr<WidgetData> widgetData);

	void End();

	std::vector<std::shared_ptr<WidgetData>> widgetList;
};