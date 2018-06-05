#pragma once
#include "Material.h"
class Terrain :
	public Material
{
private:
	Texture * texture1;
	Texture *texture2;
	Texture *blendMap;
	Texture *specularTexture;
	float shininess = 256.0f;

public:
	Terrain();
	void Bind();
	void BindUniforms(Shader &shader);
	float GetShininess();
	void SetShininess(float shininess);
	void UpdateBlendMap();
	~Terrain();
};

