#pragma once
#include "observer/Observer.h"

class CameraMovement : Observer {
public:
	CameraMovement(Camera & camera) : camera(camera)
	{

	}

	virtual void Notify(int action, const int value) override 
	{
		if (action == Observer::Action::KEY_PRESSED)
		{
			if (value == GLFW_KEY_W)
			{
				camera.ProcessKeyboard(FORWARD, Engine::GetInstance().deltaTime);
			}
			if (value == GLFW_KEY_S)
			{
				camera.ProcessKeyboard(BACKWARD, Engine::GetInstance().deltaTime);
			}
			if (value == GLFW_KEY_A)
			{
				camera.ProcessKeyboard(LEFT, Engine::GetInstance().deltaTime);
			}
			if (value == GLFW_KEY_D)
			{
				camera.ProcessKeyboard(RIGHT, Engine::GetInstance().deltaTime);
			}
		}
	}
	
private :
	Camera & camera;
};