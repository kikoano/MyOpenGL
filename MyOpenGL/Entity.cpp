#include "Entity.h"

glm::mat4 Entity::projection;
glm::mat4 Entity::view;
Entity::Entity() {

}
Entity::Entity(glm::vec3 position) : position(position)
{
}
void Entity::UpdateProView(glm::mat4 projection, glm::mat4 view)
{
	Entity::projection = projection;
	Entity::view = view;
}
glm::vec3 Entity::GetPosition() const{
	return position;
}

void Entity::SetPosition(glm::vec3 position) {
	this->position = position;
}
