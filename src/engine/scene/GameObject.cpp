#include "GameObject.h"

GameObject::GameObject(const GameObject& other)
{
	transform = other.transform;
	model = other.model->Clone();
}

GameObject::GameObject(const Transform& transform, const Model* model)
{
	this->transform = transform;
	if (model == nullptr)
	{
		this->model = new ModelPlane(1, 1);
	}
	else
	{
		this->model = model->Clone();
	}
}

GameObject::~GameObject()
{
	delete model;
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