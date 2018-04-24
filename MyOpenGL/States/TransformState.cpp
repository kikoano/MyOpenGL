#include "TransformState.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void TransformState::Init()
{
	shader = new Shader(vertexShaderSource, fragmentShaderSource);

	//vertices = draw::polyeder(10, 0, 0, 0.5f);
	/*for (int i = 0; i < vertices->size; i++) {
		std::cout << &vertices[i] << std::endl;
	}*/
	// Generate and bind VAO and VBO



	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])* indices.size(), &indices[0], GL_STATIC_DRAW);

	// Set AttribArray
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//clear all binding
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



}

void TransformState::Pause()
{

}

void TransformState::Resume()
{

}

void TransformState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

}

void TransformState::HandleMouseEvents(double xoffset, double yoffset)
{
}

void TransformState::HandleScrollEvents(double xoffset, double yoffset)
{
}

void TransformState::Update(StateManager* stateManager, double delta)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.1f, 0.1f, 0.0f));
	trans = glm::rotate(trans, 300.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::translate(trans, glm::vec3(-0.1f, -0.1f, 0.0f));
	if (i > 1000) {
		trans = glm::scale(trans, glm::vec3(2, 2, 1));
		if (i > 2000)
			i = 0;
	}
	shader->SetUniformMatrix4fv("scale", trans);
	i++;
}

void TransformState::Render(StateManager* stateManager)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Bind();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
TransformState::~TransformState() {
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shader->Unbind();
	delete shader;
}
