#pragma once
#include "State.h"

class FinkiLogoState : public State
{
private:
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.xyz, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"   FragColor = color;\n"
		"}\n\0";
	unsigned int VAO;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* shader;

public:
	void Init();

	void Pause();
	void Resume();

	void HandleEvents(StateManager* stateManager, int key, int action);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~FinkiLogoState();

};
