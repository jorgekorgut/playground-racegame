#pragma once
#include "RenderManager.h"
#include "resource/ResourceManager.h"
#include <glad/glad.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <scene/Material.h>
#include <scene/Model.h>
#include <scene/Transform.h>
#include <Engine.h>


RenderManager::RenderManager() {
}

void RenderManager::Initialize() {
    shader = ResourceManager::LoadShader();

    Signature renderSignature;
    renderSignature.set(
    Engine::GetInstance().componentManager.GetComponentType<Transform>());
    renderSignature.set(
    Engine::GetInstance().componentManager.GetComponentType<Material>());
    renderSignature.set(Engine::GetInstance().componentManager.GetComponentType<Model>());
    Engine::GetInstance().systemManager.RegisterSystem<RenderManager>(this, renderSignature);
}

void RenderManager::Destroy() {
}

void RenderManager::ToggleWireframeMode() {
    wireframeMode = !wireframeMode;
    if(wireframeMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void RenderManager::Clear() {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::Render(WindowManager& windowManager, SceneManager& sceneManager) {
    glm::mat4 projection = glm::perspective(glm::radians(sceneManager.camera.Zoom),
    (float)windowManager.windowWidth / (float)windowManager.windowHeight, 0.1f, 100.0f);
    glm::mat4 view = sceneManager.camera.GetViewMatrix();

    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setVec3("viewPos", sceneManager.camera.Position);

    for(const Entity& currentEntity : mEntities) {
        Transform& transform =
        Engine::GetInstance().componentManager.GetComponent<Transform>(currentEntity);
        Material& material =
        Engine::GetInstance().componentManager.GetComponent<Material>(currentEntity);
        Model& modelMesh =
        Engine::GetInstance().componentManager.GetComponent<Model>(currentEntity);

        glm::mat4 model = transform.GetModelMatrix();
        shader.setMat4("model", model);

        glm::mat3 normalMatrix = glm::transpose(
        glm::inverse(model)); // Update normal matrix only in case of non-uniform scaling
        shader.setMat3("normalMatrix", normalMatrix);

        shader.setVec3("color", material.color);
        modelMesh.Render(shader);
    }
}
