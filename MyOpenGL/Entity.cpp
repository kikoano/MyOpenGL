#include "Entity.h"

Entity::Entity(glm::vec3 position) : position(position)
{
}
glm::vec3 Entity::GetPosition() {
	return position;
}

void Entity::SetPosition(glm::vec3 position) {
	this->position = position;
}
