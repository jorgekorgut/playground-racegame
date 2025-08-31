#pragma once
#include "Transform.h"
#include "Model.h"
#include "ModelPlane.h"

class GameObject {
public:
    GameObject(GameObject& other);
	GameObject(const Transform& transform = Transform(), glm::vec3 color = glm::vec3(1.0f, 0, 0), const std::shared_ptr<Model> = nullptr);
	~GameObject();

	virtual void Initialize();
	virtual void Destroy();
	virtual void Update();

	std::shared_ptr<Model> model = nullptr;
	glm::vec3 color;
	Transform transform;
};