#include "Tree.h"

glm::mat4 Tree::projection;
glm::mat4 Tree::view;
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
	model = new Mesh(this->type);

}
void Tree::UpdateProView(glm::mat4 projection, glm::mat4 view)
{
	Tree::projection = projection;
	Tree::view = view;
}
void Tree::Init()
{
	shaderModel = glm::scale(shaderModel,glm::vec3(0.1f, 0.1f, 0.1f));
	shaderModel = glm::translate(shaderModel, position);
}

void Tree::Update(double delta) 
{
	shader.Bind();
	shader.SetUniformMatrix4fv("projection", projection);
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("model", shaderModel);
}

void Tree::Render()
{
	model->draw(shader);
}



Tree::~Tree()
{
	delete model;
}
