#include "Tree.h"


Tree::Tree(Type type, glm::vec3 position):Entity(position)
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
	model = std::make_unique<Mesh>(this->type);

}
void Tree::Init()
{
	shaderModel = glm::translate(shaderModel, position);
}

void Tree::Update(double delta) 
{
	shader.Bind();
	shader.SetUniformMatrix4fv("projection", projection);
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("model", shaderModel);
	shader.SetUniform3fv("skyColor", glm::vec3(0.87f, 0.91f, 0.94f));
	shader.Unbind();
}

void Tree::Render()
{
	model->draw(shader);
}

void Tree::SetScale(float size)
{
	float scale = (size) / 700.0f;
	shaderModel = glm::translate(shaderModel, position);
	shaderModel = glm::scale(shaderModel, glm::vec3(scale, scale, scale));
	shaderModel = glm::translate(shaderModel, -position);
}



Tree::~Tree()
{

}
