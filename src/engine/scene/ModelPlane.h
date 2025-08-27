#pragma once
#include "Model.h"

class ModelPlane : public Model 
{
public:
	ModelPlane();
	
	void Render(Shader& shader) override;
};