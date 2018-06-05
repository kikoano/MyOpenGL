#include "Terrian.h"


Terrain::Terrain()
{
	texture1 = new Texture(RESOURCES_PATH + "Textures\\grass.png",false);
	texture2 = new Texture(RESOURCES_PATH + "Textures\\dirt.png", false);
	blendMap = new Texture(RESOURCES_PATH + "Textures\\Maps\\terrainBlendMap.bmp", false,true);
	specularTexture = new Texture(RESOURCES_PATH + "Textures\\grass.png", false);
}

void Terrain::Bind()
{
	texture1->Bind(0);
	texture2->Bind(1);
	blendMap->Bind(2);
	specularTexture->Bind(3);
}

void Terrain::BindUniforms(Shader & shader)
{
	shader.SetUniform1i("material.diffuse", 0);
	shader.SetUniform1i("material.diffuse2", 1);
	shader.SetUniform1i("material.blendMap", 2);
	shader.SetUniform1i("material.specular", 3);
}


float Terrain::GetShininess()
{
	return shininess;
}
void Terrain::SetShininess(float shininess)
{
	this->shininess = shininess;
}

void Terrain::UpdateBlendMap()
{
	delete blendMap;
	blendMap = new Texture(RESOURCES_PATH + "Textures\\Maps\\terrainBlendMap.bmp", false);
	blendMap->Bind(2);
}

Terrain::~Terrain()
{
	delete texture1;
	delete texture2;
	delete blendMap;
	delete specularTexture;
}
