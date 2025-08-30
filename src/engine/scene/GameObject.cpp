#include "GameObject.h"



GameObject::GameObject(GameObject& other)
{
	this->transform = other.transform;
	this->color = other.color;
	if (other.model == nullptr)
	{
		this->model = std::make_unique<ModelPlane>(1, 1);
	}
	else
	{
		this->model = std::move(other.model);
	}
}

GameObject::GameObject(const Transform& transform, glm::vec3 color, std::unique_ptr<Model> model)
{
	this->transform = transform;
	this->color = color;

	if (model == nullptr)
	{
		this->model = std::make_unique<ModelPlane>(1, 1);
	}
	else
	{
		this->model = std::move(model);
	}
}

GameObject::~GameObject()
{

}

void GameObject::Initialize()
{

}

void GameObject::Destroy()
{

}

void GameObject::Update()
{

}