#pragma once
#include "main.h"
#include "Texture.h"
class Material
{
private:
	Texture *diffuseTexture;
	Texture *specularTexture;
	float shininess;
public:
	Material(const std::string &diffuseTexturePath, bool diffuseTextureAlpha, const std::string &specularTexturePath, bool specularTextureAlpha, float shininess);

	void Bind();
	void BindUniforms(Shader &shader);
	void Unbind();

	float GetShininess();
	void SetShininess(float shininess);

	~Material();
};

