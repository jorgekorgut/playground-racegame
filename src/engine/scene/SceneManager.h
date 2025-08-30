#pragma once
#include "GameObject.h"
#include "Camera.h"

class SceneManager {
public :
	SceneManager();
	void Initialize();
	void Destroy();
	void Update();
	std::vector<GameObject> objects;
	std::vector<GameObject> debugObjects;
	Camera camera;
};