#include "Grass.h"


Grass::Grass(Type type, glm::vec3 position):Entity(position)
{
	if (type == TYPE1) 
		this->type = type1;
	else if (type == TYPE2)
		this->type = type2;
	else if (type == TYPE3)
		this->type = type3;
	else if (type == TYPE4)
		this->type = type4;
	else if (type == TYPE5)
		this->type = type5;
	else if (type == TYPE6)
		this->type = type6;
	else if (type == TYPE7)
		this->type = type7;
	else if (type == TYPE8)
		this->type = type8;
	else if (type == TYPE9)
		this->type = type9;
	model = std::make_unique<Mesh>(this->type);

}
void Grass::Init()
{
	shaderModel = glm::translate(shaderModel, position);
}

void Grass::Update(double delta)
{
	shader.Bind();
	shader.SetUniformMatrix4fv("projection", projection);
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("model", shaderModel);
	shader.SetUniform3fv("skyColor", glm::vec3(0.87f, 0.91f, 0.94f));
	shader.Unbind();
}

void Grass::Render()
{
	model->draw(shader);
}

void Grass::SetScale(float size)
{
	float scale;
	if(type == type2 || type == type3)
		scale = size / 10000.0f;
	else if (type == type1)
		scale = size / 3000.0f;
	else if (type == type8 || type == type9)
		scale = size / 4000.0f;
	else 
		scale = size / 2000.0f;
	shaderModel = glm::translate(shaderModel, position);
	shaderModel = glm::scale(shaderModel, glm::vec3(scale, scale, scale));
	shaderModel = glm::translate(shaderModel, -position);
}



Grass::~Grass()
{

}
