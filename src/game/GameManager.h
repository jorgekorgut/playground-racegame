#pragma once
#include "Engine.h";
#include "observer/Observer.h"

class GameManager {

public :
	GameManager() {

		Engine & engine = Engine::GetInstance();

		engine.sceneManager.camera.Position = glm::vec3(0, 1.5, 5);

		std::shared_ptr<CameraMovement> cameraMovement = std::make_shared<CameraMovement>(engine.sceneManager.camera);
		engine.inputManager.Attach(cameraMovement);
		engine.AttachUpdatable(cameraMovement);


		std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>();

		engine.imguiManager.AttachWidgetData(terrain);

	}
};