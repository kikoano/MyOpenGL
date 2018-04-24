#pragma once
#include "State.h"
class Projection3DState : public State
{
private:
	unsigned int VAO;
	unsigned int texture1, texture2;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* shader;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	std::vector<glm::vec3> cubePositions;
public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset);
	void HandleScrollEvents(double xoffset, double yoffset);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~Projection3DState();

};
