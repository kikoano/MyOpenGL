#include "FinkiLogoState.h"


void FinkiLogoState::Init()
{
	shader = new Shader(vertexShaderSource, fragmentShaderSource);

	draw::polyederElement(4, -0.5f, 0.0f, 0.1f, 0.5f, vertices, indices);
	draw::polyederRingElement(100, 0.2f, 0.0f, 0.4f, 0.25f, vertices, indices);


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));
	ib = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());


	// Set AttribArray
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//clear all binding
	glBindVertexArray(0);
	vb->Unblind();
	ib->Unblind();

}

void FinkiLogoState::Pause()
{

}

void FinkiLogoState::Resume()
{

}

void FinkiLogoState::HandleEvents(StateManager* stateManager, int key, int action)
{

}

void FinkiLogoState::Update(StateManager* stateManager, double delta)
{

}

void FinkiLogoState::Render(StateManager* stateManager)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Bind();
	shader->SetUniform4f("color", glm::vec4(0.19f, 0.19f, 0.51f, 1.0f));
	glBindVertexArray(VAO);
	ib->Bind();
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, nullptr);
	shader->SetUniform4f("color", glm::vec4(0.16f, 0.58f, 0.84f, 1.0f));
	glDrawElements(GL_TRIANGLE_STRIP, indices.size() - 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

	
}

FinkiLogoState::~FinkiLogoState() {
	shader->Unbind();
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	vb->Unblind();
	ib->Unblind();
	delete vb;
	delete ib;
}

