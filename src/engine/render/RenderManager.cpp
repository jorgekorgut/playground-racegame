#include "RenderManager.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "resource/ResourceManager.h"

RenderManager::RenderManager()
{
}

void RenderManager::Initialize()
{
    shader = ResourceManager::LoadShader();
}

void RenderManager::Destroy()
{

}

void RenderManager::Render(WindowManager& windowManager, SceneManager & sceneManager)
{

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(sceneManager.camera.Zoom), (float)windowManager.windowWidth / (float)windowManager.windowHeight, 0.1f, 100.0f);
    glm::mat4 view = sceneManager.camera.GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setVec3("viewPos", sceneManager.camera.Position);

    for (GameObject currentObject : sceneManager.objects)
    {
        glm::mat4 model(1.0f);
        glm::mat3 normalMatrix = glm::mat3(1.0f);
        model = glm::translate(model, currentObject.transform.position); // translate it down so it's at the center of the scene
        model = glm::scale(model, currentObject.transform.scale);

        shader.setMat4("model", model);

        normalMatrix = glm::transpose(glm::inverse(model)); // Update normal matrix only in case of non-uniform scaling
        shader.setMat3("normalMatrix", normalMatrix);

        currentObject.model->Render(shader);
    }
}