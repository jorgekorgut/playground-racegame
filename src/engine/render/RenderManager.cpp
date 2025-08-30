#include "RenderManager.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "resource/ResourceManager.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

RenderManager::RenderManager()
{
}

void RenderManager::Initialize()
{
    shader = ResourceManager::LoadShader();
	debugShader = ResourceManager::LoadShader("shaders/DebugShader.vert", "shaders/DebugShader.frag");
}

void RenderManager::Destroy()
{

}

void RenderManager::ToggleWireframeMode()
{
    wireframeMode = !wireframeMode;
    if (wireframeMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void RenderManager::Clear()
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::Render(WindowManager& windowManager, SceneManager & sceneManager)
{
    glm::mat4 projection = glm::perspective(glm::radians(sceneManager.camera.Zoom), (float)windowManager.windowWidth / (float)windowManager.windowHeight, 0.1f, 100.0f);
    glm::mat4 view = sceneManager.camera.GetViewMatrix();

    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setVec3("viewPos", sceneManager.camera.Position);
    for (GameObject & currentObject : sceneManager.objects)
    {
		glm::mat4 model = currentObject.transform.GetModelMatrix();
        shader.setMat4("model", model); 

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(model)); // Update normal matrix only in case of non-uniform scaling
        shader.setMat3("normalMatrix", normalMatrix);

		shader.setVec3("color", currentObject.color);
        currentObject.model->Render(shader);
    }

	debugShader.use();
    debugShader.setMat4("projection", projection);
    debugShader.setMat4("view", view);
    debugShader.setVec3("viewPos", sceneManager.camera.Position);
    for (GameObject& currentObject : sceneManager.debugObjects)
    {
        glm::mat4 model = currentObject.transform.GetModelMatrix();
        debugShader.setMat4("model", model);

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(model)); // Update normal matrix only in case of non-uniform scaling
        debugShader.setMat3("normalMatrix", normalMatrix);

        debugShader.setVec3("color", currentObject.color);
        currentObject.model->Render(debugShader);
    }

}