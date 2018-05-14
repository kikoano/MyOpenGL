#pragma once
#include "State.h"

class FlowerState : public State
{
private:
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 color;\n"
		"void main()\n"
		"{\n"
		"	color=aColor;\n"
		"   gl_Position = vec4(aPos.xyz, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"in vec3 color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(color , 1.0f);\n"
		"}\n\0";
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* shader;
	void DrawPart();
	void P1(int i, bool scale, int &index);
	void P2(int i, bool scale, int &index);

public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset);
	void HandleScrollEvents(double xoffset, double yoffset);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	~FlowerState();

};
