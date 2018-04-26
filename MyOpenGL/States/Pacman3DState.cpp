#include "Pacman3DState.h"
#include <stb/stb_image.h>
void Pacman3DState::Init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
	
	glEnable(GL_DEPTH_TEST);

	shader = new Shader("Finki.vert", "Finki.frag");

	draw::spherePacman(0.0f, 0.0f, 0.0f, 40, 40, vertices, indices);


	vaBody = new VertexArray();
	vbBody = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);

	vaBody->AddBuffer(*vbBody, layout);

	ibBody = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());

	vertices.clear();
	indices.clear();
	draw::sphere2(0.0f, 0.0f, 0.0f, 40, 40, vertices, indices);

	vaEye = new VertexArray();
	vbEye = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	vaEye->AddBuffer(*vbEye, layout);

	ibEye = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());


}


void Pacman3DState::Pause()
{

}

void Pacman3DState::Resume()
{

}

void Pacman3DState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera->ProcessKeyboard(key, action);
}

void Pacman3DState::HandleMouseEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseMovement(xoffset, yoffset);

}

void Pacman3DState::HandleScrollEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void Pacman3DState::Update(StateManager* stateManager, double delta)
{
	camera->Update(delta);
}

void Pacman3DState::Render(StateManager* stateManager)
{
	renderer.Clear();

	shader->Bind();

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	view = camera->GetViewMatrix();
	projection = glm::perspective(glm::radians(camera->GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	shader->SetUniformMatrix4fv("projection", projection);
	shader->SetUniformMatrix4fv("view", view);
	shader->SetUniform3fv("color", glm::vec3(1.0f,1.0f, 0.0f));
	for (int i = 0; i < 3; i++) {
		modelBody = glm::mat4(1.0f);
		modelBody = glm::translate(modelBody, glm::vec3(0.0f, 0.0f, 0.0f));
		modelBody = glm::rotate(modelBody, glm::radians(i*90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->SetUniformMatrix4fv("model", modelBody);
		vaBody->Bind();
		renderer.Render(*vaBody, *ibBody, *shader, GL_TRIANGLE_STRIP);
	}
	shader->SetUniform3fv("color", glm::vec3(1.0f, 1.0f, 1.0f));
	for (int i = 0; i < 2; i++) {
		modelEye = glm::mat4(1.0f);
		modelEye = glm::translate(modelEye, glm::vec3(0.6f, 1.0f, -0.5f));
		modelEye = glm::translate(modelEye, glm::vec3(0.0f, -0.6f, i *1.0f));
		modelEye = glm::scale(modelEye, glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetUniformMatrix4fv("model", modelEye);
		vaEye->Bind();
		renderer.Render(*vaEye, *ibEye, *shader, GL_TRIANGLE_STRIP);
	}
}

Pacman3DState::~Pacman3DState() {
	shader->Unbind();
	vaBody->Unbind();
	vbBody->Unblind();
	ibBody->Unblind();
	vaEye->Unbind();
	vbEye->Unblind();
	ibEye->Unblind();
	delete shader;
	delete vaBody;
	delete vbBody;
	delete ibBody;
	delete vaEye;
	delete vbEye;
	delete ibEye;
	delete camera;
}
