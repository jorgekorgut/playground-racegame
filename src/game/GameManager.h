#pragma once
#include "Engine.h"
#include "observer/Observer.h"
#include <memory>
#include "Terrain.h"

class GameManager {

    Terrain terrain;

    public:
    GameManager() {
        Engine& engine = Engine::GetInstance();

        engine.sceneManager.camera.Position = glm::vec3(0, 1.5, 5);
        std::shared_ptr<CameraMovement> cameraMovement =
        std::make_shared<CameraMovement>(engine.sceneManager.camera);
        engine.inputManager.Attach(cameraMovement);
        engine.AttachUpdatable(cameraMovement);
    }
};
