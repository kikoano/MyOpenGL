#include "FlowerState.h"


void FlowerState::Init()
{
	shader = new Shader(vertexShaderSource, fragmentShaderSource);

	DrawPart();
	float color1[] = { 1.0f, 0.749f, 0.0f };
	draw::polyederElementColor(30, 0.0f, 0.0f, 0.08f, vertices, indices, color1);
	float color2[] = { 1.0f, 1.0f, 0.0f };
	draw::polyederElementColor(30, 0.0f, 0.0f, 0.06f, vertices, indices, color2);

	unsigned int max = *max_element(indices.begin(), indices.end()) + 1;
	indices.push_back(max);
	vertices.push_back(0.15f);
	vertices.push_back(-1.0f);
	vertices.push_back(0.0f);

	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	indices.push_back(max + 1);
	vertices.push_back(0.15f);
	vertices.push_back(-0.3f);
	vertices.push_back(0.0f);

	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

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

void FlowerState::Pause()
{

}

void FlowerState::Resume()
{

}

void FlowerState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

}

void FlowerState::Update(StateManager* stateManager, double delta)
{

}
void FlowerState::DrawPart() {
	int index = 0;

	indices.push_back(index++);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(0.5f);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	for (int i = 0; i < 4; i++) {

		P1(i, false, index);

	}
	for (int i = 0; i < 4; i++) {
		P1(i, true, index);
	}
	for (int i = 0; i < 4; i++) {
		P2(i, false, index);
	}
	for (int i = 0; i < 4; i++) {
		P2(i, true, index);
	}

}
void FlowerState::P1(int i,bool scale, int&index) {
	if (i != 0 || scale)
		indices.push_back(0);

	glm::mat4 modelRotate = glm::mat4(1.0f);
	modelRotate = glm::rotate(modelRotate, glm::radians(i*90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	if (scale)
		modelRotate = glm::scale(modelRotate, glm::vec3(1.0f, -1.0f, 0.0f));

	glm::vec4 v = glm::vec4(0.3f, 0.15f, 0.0f, 1.0f);


	v = modelRotate * v;
	indices.push_back(index++);
	vertices.push_back(v.x);
	vertices.push_back(v.y);
	vertices.push_back(v.z);

	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);

	v = glm::vec4(0.6f, 0.0f, 0.0f, 1.0f);

	v = modelRotate * v;

	indices.push_back(index++);
	vertices.push_back(v.x);
	vertices.push_back(v.y);
	vertices.push_back(v.z);

	vertices.push_back(0.5f);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
}
void FlowerState::P2(int i, bool scale, int&index) {
	glm::mat4 modelRotate = glm::mat4(1.0f);
	modelRotate = glm::rotate(modelRotate, glm::radians(i*90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	if (scale)
		modelRotate = glm::scale(modelRotate, glm::vec3(1.0f, -1.0f, 0.0f));
	glm::vec4 v = glm::vec4(0.43f, 0.43f, 0.0f, 1.0f);

	v = modelRotate * v;
	int offset = (scale) ? 8 : 0;
	indices.push_back(i * 2 + offset + 1);
	indices.push_back(index++);
	vertices.push_back(v.x);
	vertices.push_back(v.y);
	vertices.push_back(v.z);

	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
}

void FlowerState::Render(StateManager* stateManager)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Bind();
	glBindVertexArray(VAO);
	ib->Bind();

		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT,nullptr);
		glLineWidth(2.0f);
		glDrawElements(GL_LINES, 16, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLE_FAN, 64, GL_UNSIGNED_INT, (void*)(40 * sizeof(unsigned int)));
		glLineWidth(3.0f);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(104 * sizeof(unsigned int)));
}

FlowerState::~FlowerState() {
	glLineWidth(1.0f);
	shader->Unbind();
	delete shader;
	glDeleteBuffers(1, &VAO);
	vb->Unblind();
	delete vb;
	ib->Unblind();
	delete ib;
}

