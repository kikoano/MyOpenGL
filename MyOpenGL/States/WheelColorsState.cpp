#include "WheelColorsState.h"


void WheelColorsState::Init()
{

	shader = new Shader(vertexShaderSource, fragmentShaderSource);

	draw::polyederColorWheel(360, 0.0f, 0.0f,0.8f, vertices);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));


	// Set AttribArray
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//clear all binding
	glBindVertexArray(0);
	vb->Unblind();

}


void WheelColorsState::Pause()
{

}

void WheelColorsState::Resume()
{

}

void WheelColorsState::HandleEvents(StateManager* stateManager, int key, int action)
{

}

void WheelColorsState::Update(StateManager* stateManager, double delta)
{

}

void WheelColorsState::Render(StateManager* stateManager)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size()/6);
}

WheelColorsState::~WheelColorsState() {
	shader->Unbind();
	delete shader;
	glDeleteBuffers(1, &VAO);
	vb->Unblind();
	delete vb;
}
