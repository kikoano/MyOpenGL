#include "GradientState.h"

void GradientState::CreateVertex(glm::vec4 v, int& index, int type, float color) {
	indices.push_back(index++);
	vertices.push_back(v.x);
	vertices.push_back(v.y);
	vertices.push_back(v.z);
	if (type == 0) {
		vertices.push_back(color);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
	}
	else if (type == 1) {
		vertices.push_back(0.0f);
		vertices.push_back(color);
		vertices.push_back(0.0f);
	}
	else if (type == 2) {
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(color);
	}
}
void GradientState::Init()
{

	shader = new Shader(vertexShaderSource, fragmentShaderSource);
	int index = 0;


	for (int y = 0; y < 3; y++) {
		float colorInc = 1.0f / 10.0f;
		float color = 0.0f;

		for (int x = 0; x < 10; x++) {
			glm::mat4 transformModel = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.2f, -y * 0.7f, 0.0f));

			glm::vec4 v = transformModel * glm::vec4(-1.0f, 1.0, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			v = transformModel * glm::vec4(-1.0f, 0.3f, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			v = transformModel * glm::vec4(-0.8f, 0.3f, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			indices.push_back(index-1);

			v = transformModel * glm::vec4(-0.8f, 1.0f, 0.0f, 1.0f);
			CreateVertex(v, index, y, color);

			indices.push_back(index-4);

			color += colorInc;
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	ib = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());

	// Set AttribArray
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//clear all binding
	glBindVertexArray(0);
	vb->Unblind();
	ib->Unblind();
}


void GradientState::Pause()
{

}

void GradientState::Resume()
{

}

void GradientState::HandleEvents(StateManager* stateManager, int key, int action)
{

}

void GradientState::Update(StateManager* stateManager, double delta)
{

}

void GradientState::Render(StateManager* stateManager)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Bind();
	glBindVertexArray(VAO);
	ib->Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

GradientState::~GradientState() {
	shader->Unbind();
	delete shader;
	glDeleteBuffers(1, &VAO);
	vb->Unblind();
	ib->Unblind();
	delete vb;
	delete ib;
}
