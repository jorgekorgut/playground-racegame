#pragma once
#include "Transform.h"
#include "Model.h"
#include "ModelPlane.h"

class GameObject {
public:
	GameObject();

	virtual void Initialize();
	virtual void Destroy();
	virtual void Update();

	Model * model = nullptr; 
	Transform transform;
};