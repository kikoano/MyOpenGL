#include "RombState.h"

void RombState::Init()
{
	//Create Vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Check Vertex shader success
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Create Fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	//Check Fragment shader success
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Create program and link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check program success
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	 vertices = {
		0.7f, 0.5f, 0.0f   ,1.0f, 0.0f, 0.0f, // top right
		0.5f, -0.0f, 0.0f  ,1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.0f, 0.0f ,1.0f, 0.0f, 0.0f, // bottom left
		-0.3f, 0.5f, 0.0f  ,1.0f, 0.0f, 0.0f, // top left
							
		0.7f, -0.1f, 0.0f  ,0.0f, 1.0f, 0.0f, // top right
		0.5f, -0.6f, 0.0f  ,0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.6f, 0.0f ,0.0f, 1.0f, 0.0f, // bottom left
		-0.5f, -0.6f, 0.0f ,1.0f, 0.0f, 1.0f, // bottom left
		0.7f, -0.1f, 0.0f  ,1.0f, 0.0f, 1.0f, // top right
		-0.3f, -0.1f, 0.0f ,1.0f, 0.0f, 1.0f // top left


	};

	indices = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle

		4, 5, 6, // first triangle
		7, 8, 9 // second triangle
	};

	// Generate and bind VAO and VBO and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// Set AttribArray
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void RombState::Pause()
{

}

void RombState::Resume()
{

}

void RombState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

}

void RombState::Update(StateManager* stateManager, double delta)
{

}

void RombState::Render(StateManager* stateManager)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
}
RombState::~RombState() {
	glUseProgram(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

