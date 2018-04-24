#include "BallBounceState.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
void BallBounceState::Init()
{
	glEnable(GL_DEPTH_TEST);

	draw::sphere(0.0f, 0.0f, 0.0f, 40, 40, vertices, indices);
	shader = new Shader("BallBounce.vert", "BallBounce.frag");


	va = new VertexArray();
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	va->AddBuffer(*vb, layout);

	ib = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());

	//clear all binding
	va->Unbind();
	vb->Unblind();
	ib->Unblind();
}


void BallBounceState::Pause()
{

}

void BallBounceState::Resume()
{

}

void BallBounceState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

}

void BallBounceState::Update(StateManager* stateManager, double delta)
{
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() / 2.0f, glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	shader->SetUniformMatrix4fv("model", model);
	shader->SetUniformMatrix4fv("view", view);
	shader->SetUniformMatrix4fv("projection", projection);
}

void BallBounceState::Render(StateManager* stateManager)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Bind();

	va->Bind();
	ib->Bind();
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

}

BallBounceState::~BallBounceState() {
	shader->Unbind();
	va->Unbind();
	vb->Unblind();
	ib->Unblind();
	delete shader;
	delete va;
	delete vb;
	delete ib;
}
