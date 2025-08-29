#pragma once
#include "observer/Observer.h"
#include "input/InputManager.h"
#include "observer/Updatable.h"
#include <vector>

class CameraMovement : Observer, Updatable {
public:
	CameraMovement(Camera & camera) : camera(camera)
	{
		keysState.resize(1024, false);
	}

	void Update() override
	{
		if (keysState[GLFW_KEY_SPACE])
		{
			camera.ProcessKeyboard(UP, Engine::GetInstance().deltaTime);
		}
		if (keysState[GLFW_KEY_LEFT_SHIFT])
		{
			camera.ProcessKeyboard(DOWN, Engine::GetInstance().deltaTime);
		}
		if (keysState[GLFW_KEY_W])
		{
			camera.ProcessKeyboard(FORWARD, Engine::GetInstance().deltaTime);
		}
		if (keysState[GLFW_KEY_S])
		{
			camera.ProcessKeyboard(BACKWARD, Engine::GetInstance().deltaTime);
		}
		if (keysState[GLFW_KEY_A])
		{
			camera.ProcessKeyboard(LEFT, Engine::GetInstance().deltaTime);
		}
		if (keysState[GLFW_KEY_D])
		{
			camera.ProcessKeyboard(RIGHT, Engine::GetInstance().deltaTime);
		}
	}

	virtual void Notify(int action, void * value) override 
	{
		if (action == Observer::Action::KEY_PRESSED)
		{
			InputManager::KeyEvent* keyEvent = static_cast<InputManager::KeyEvent*>(value);

			int keyValue = keyEvent->key;

			keysState[keyValue] = true;
		}
		
		if (action == Observer::Action::KEY_RELEASED)
		{
			InputManager::KeyEvent* keyEvent = static_cast<InputManager::KeyEvent*>(value);

			int keyValue = keyEvent->key;

			keysState[keyValue] = false;
		}

		if(action == Observer::Action::MOUSE_MOVED)
		{
			InputManager::MouseMovementEvent* mouseMovementEvent = static_cast<InputManager::MouseMovementEvent*>(value);
			float x = mouseMovementEvent->x;
			float y = mouseMovementEvent->y;
			camera.ProcessMouseMovement(x, y);
		}
	}
	
private :
	Camera & camera;
	std::vector<bool> keysState;
};