#include "Box.h"


Box::Box()
{
	texture = new Texture(RESOURCES_PATH + "Textures\\container2.png",false);
	specularTexture = new Texture(RESOURCES_PATH + "Textures\\container2_specular.png", false);
}

void Box::Bind()
{
	texture->Bind(0);
	specularTexture->Bind(1);
}

void Box::BindUniforms(Shader & shader)
{
	shader.SetUniform1i("material.diffuse", 0);
	shader.SetUniform1i("material.specular", 1);
}


float Box::GetShininess()
{
	return shininess;
}
void Box::SetShininess(float shininess)
{
	this->shininess = shininess;
}

Box::~Box()
{
	delete texture;
	delete specularTexture;
}
