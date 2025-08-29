#pragma once
#include "Model.h"

class ModelPlane : public Model 
{
public:
	ModelPlane* Clone() const override;
	ModelPlane(int numCol = 1 , int numRow= 1);
	void Render(Shader& shader) override;
	int numCol;
	int numRow;
};