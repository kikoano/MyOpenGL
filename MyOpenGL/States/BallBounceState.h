#pragma once
#include "State.h"
class BallBounceState : public State
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
public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~BallBounceState();

};
