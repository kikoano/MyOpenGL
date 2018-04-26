#pragma once
#include "State.h"
#include "..//Camera.h"

class FinkiLogoState3D : public State
{
private:
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	VertexArray* vaI,*vaO;
	VertexBuffer* vbI, *vbO;
	IndexBuffer* ibI,*ibO;
	Shader* shader;
	glm::mat4 modelI, modelO;
	glm::mat4 view;
	glm::mat4 projection;
	Renderer renderer;
	Camera *camera;
public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset);
	void HandleScrollEvents(double xoffset, double yoffset);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~FinkiLogoState3D();

};
