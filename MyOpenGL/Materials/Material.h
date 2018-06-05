#pragma once
#include "..//main.h"
#include "..//Texture.h"
class Material
{

public:
	virtual void Bind() = 0;
	virtual void BindUniforms(Shader &shader) = 0;
};

