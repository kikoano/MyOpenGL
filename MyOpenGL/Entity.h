#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Entity {
protected:
	glm::vec3 position;
public:
	Entity(glm::vec3 position);
	virtual void Init() = 0;
	virtual void Update(double delta) = 0;
	inline glm::vec3 GetPosition() {
		return position;
	}
};