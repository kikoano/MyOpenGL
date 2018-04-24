#pragma once
#include "State.h"
class PacmanState : public State
{
private:
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"uniform mat4 model;\n"
		"uniform mat4 projection;\n"
		"out vec3 color;\n"
		"void main()\n"
		"{\n"
		"	color = aColor;\n"
		"	gl_Position = projection * model * vec4(aPos, 1.0f);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"in vec3 color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(color , 1.0f);\n"
		"}\n\0";
	const char* vertexShaderSource2 = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"uniform mat4 model;\n"
		"uniform mat4 projection;\n"
		"out vec3 color;\n"
		"void main()\n"
		"{\n"
		"	color = aColor;\n"
		"	gl_Position = projection * model * vec4(aPos, 1.0f);\n"
		"}\0";
	const char *fragmentShaderSource2 = "#version 330 core\n"
		"in vec3 color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(color , 1.0f);\n"
		"}\n\0";
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> indicesSize;
	struct Entity {
		bool direction[4];
		bool flip = false;
		float speed = 200.0f;
		glm::vec3 position;
		glm::mat4 model;
	} pacman, ghost;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader shader1;
	Shader shader2;
	glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH,(float) HEIGHT, 0.0f, -1.0f, 1.0f);
public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset);
	void HandleScrollEvents(double xoffset, double yoffset);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	PacmanState();
	~PacmanState();

};
