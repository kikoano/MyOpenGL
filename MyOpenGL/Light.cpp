#include "Light.h"


Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Entity(position), ambient(ambient), diffuse(diffuse), specular(specular)
{

}
void Light::Init() {
	model = glm::translate(model, position);
	va = std::make_unique<VertexArray>();
	vb = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(vertices[0]), true);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	va->AddBuffer(*vb, layout);
}
void Light::Update(double delta)
{
	shader.Bind();
	shader.SetUniform3fv("color", diffuse);
	shader.SetUniformMatrix4fv("projection", projection);
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("model", model);
	shader.Unbind();
}
void Light::Render()
{
	shader.Bind();
	va->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	va->Unbind();
	shader.Unbind();
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

glm::mat4 & Light::GetModel()
{
	return model;
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
