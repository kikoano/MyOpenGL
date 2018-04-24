#pragma once
#include "State.h"
#include "..//Camera.h"

class CameraState : public State
{
private:
	unsigned int VAO;
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
	Renderer renderer;
	Texture *texture1, *texture2;
	Camera *camera;
public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset) override;
	void HandleScrollEvents(double xoffset, double yoffset) override;
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~CameraState();

};
