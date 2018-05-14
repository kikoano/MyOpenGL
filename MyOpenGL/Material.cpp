#include "Material.h"


Material::Material(const std::string &diffuseTexturePath, bool diffuseTextureAlpha, const std::string &specularTexturePath, bool specularTextureAlpha, float shininess) : shininess(shininess)
{
	diffuseTexture = new Texture(RESOURCES_PATH + "Textures\\" + diffuseTexturePath, diffuseTextureAlpha);
	specularTexture = new Texture(RESOURCES_PATH + "Textures\\" + specularTexturePath, specularTextureAlpha);
}

void Material::Bind()
{
	diffuseTexture->Bind(0);
	specularTexture->Bind(1);
}
void Material::BindUniforms(Shader &shader) {
	shader.SetUniform1i("material.diffuse", 0);
	shader.SetUniform1i("material.specular", 1);
}

void Material::Unbind()
{
	diffuseTexture->Unbind();
	specularTexture->Unbind();
}


float Material::GetShininess()
{
	return shininess;
}

void Material::SetShininess(float shininess)
{
	this->shininess = shininess;
}

Material::~Material()
{
	delete diffuseTexture;
	delete specularTexture;
}
