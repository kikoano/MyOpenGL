#include "Light.h"


Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Entity(position), ambient(ambient), diffuse(diffuse), specular(specular)
{

}
void Light::Init() {

}
void Light::Update(double delta) {

}
glm::vec3 Light::GetAmbient()
{
	return ambient;
}

glm::vec3 Light::GetDiffuse()
{
	return diffuse;
}

glm::vec3 Light::GetSpecular()
{
	return specular;
}

void Light::SetAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void Light::SetDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void Light::SetSpecular(glm::vec3 specular)
{
	this->specular = specular;
}


Light::~Light()
{
}
