#pragma once
#include "State.h"
#include "..//Camera.h"

class LightState : public State
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	VertexArray* cubeVAO, *lightVAO;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* lightingShader, *lampShader;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	Renderer renderer;
	Texture *texture1, *texture2;
	Camera *camera;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset);
	void HandleScrollEvents(double xoffset, double yoffset);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~LightState();

};
