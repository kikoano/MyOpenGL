#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Entity {
protected:
	glm::vec3 position;
	static glm::mat4 projection;
	static glm::mat4 view;
public:
	static void UpdateProView(glm::mat4 projection, glm::mat4 view);
	Entity();
	Entity(glm::vec3 position);
	virtual void Init() = 0;
	virtual void Update(double delta) = 0;
	virtual void Render() {}
	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 position);

};