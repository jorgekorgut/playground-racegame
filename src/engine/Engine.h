#pragma once

#include "input/InputManager.h"
#include "window/WindowManager.h"
#include "render/RenderManager.h"
#include "scene/SceneManager.h"
#include "observer/Updatable.h"

class Engine {
public:
	Engine(Engine& other) = delete;
	void operator=(const Engine&) = delete;
	static Engine& GetInstance();

	void Initialize();
	void Destroy();
	void StartLoop();
	void AttachUpdatable(Updatable * object);
	void DetachUpdatable(Updatable* object);


	WindowManager windowManager;
	InputManager inputManager;
	RenderManager renderManager;
	SceneManager sceneManager;

	float deltaTime = 0.0f;	// Time between current frame and last frame

private :
	Engine() {}

	std::vector<Updatable*> updatableList;
	float lastFrame = 0.0f; // Time of last frame
	static Engine* instance;
};