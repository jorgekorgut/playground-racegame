#pragma once
// #include "input/InputManager.h"
#include "scripts/ScriptableObject.h"
#include "Engine.h"
#include <vector>

class CameraMovement : public ScriptableObject {
    public:
    CameraMovement() {
    }

    void Start() override {
        Engine::GetInstance().inputManager.AddMouseMovementCallback(
        [this](
        InputManager::MouseMovementEvent value) { this->MouseMoved(value); });
    }

    void Update() override {
        Camera& camera = Engine::GetInstance().sceneManager.camera;

        std::vector<bool>& keysState = Engine::GetInstance().inputManager.keysState;

        if(keysState[ENGINE_KEY_SPACE]) {
            camera.ProcessKeyboard(UP, Engine::GetInstance().deltaTime);
        }
        if(keysState[ENGINE_KEY_LEFT_SHIFT]) {
            camera.ProcessKeyboard(DOWN, Engine::GetInstance().deltaTime);
        }
        if(keysState[ENGINE_KEY_W]) {
            camera.ProcessKeyboard(FORWARD, Engine::GetInstance().deltaTime);
        }
        if(keysState[ENGINE_KEY_S]) {
            camera.ProcessKeyboard(BACKWARD, Engine::GetInstance().deltaTime);
        }
        if(keysState[ENGINE_KEY_A]) {
            camera.ProcessKeyboard(LEFT, Engine::GetInstance().deltaTime);
        }
        if(keysState[ENGINE_KEY_D]) {
            camera.ProcessKeyboard(RIGHT, Engine::GetInstance().deltaTime);
        }
    }

    void MouseMoved(InputManager::MouseMovementEvent value) {
        Camera& camera = Engine::GetInstance().sceneManager.camera;
        camera.ProcessMouseMovement(value.x, value.y);
    }
};
