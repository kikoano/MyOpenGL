#pragma once
#include "State.h"

class TransformState : public State
{
private:
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 scale;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = scale * vec4(aPos, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n\0";
	unsigned int VBO, VAO, EBO;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader* shader;
	int i = 0;
public:
	void Init();

	void Pause();
	void Resume();

	void HandleEvents(StateManager* stateManager, int key, int action);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~TransformState();

};
