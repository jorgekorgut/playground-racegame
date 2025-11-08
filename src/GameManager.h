#pragma once
#include "Engine.h"
#include <memory>
#include "Terrain.h"

class GameManager {
    Terrain terrain;
    CameraMovement cameraMovement;

    public:
    GameManager() {
        Engine& engine                      = Engine::GetInstance();
        engine.sceneManager.camera.Position = glm::vec3(0, 1.5, 5);
    }
};
