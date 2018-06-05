#pragma once
#include "Material.h"
class Box :
	public Material
{
private:
	Texture *texture;
	Texture *specularTexture;
	float shininess = 64.0f;
public:
	Box();
	void Bind();
	void BindUniforms(Shader &shader);
	float GetShininess();
	void SetShininess(float shininess);
	~Box();
};

