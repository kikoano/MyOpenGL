#include "FinkiLogoState3D.h"
#include <stb/stb_image.h>
void FinkiLogoState3D::Init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
	modelI = glm::mat4(1.0f);
	modelI = glm::translate(modelI, glm::vec3(-2.0f, 0.0f, 0.0f));
	modelI = glm::scale(modelI, glm::vec3(0.5f, 1.5f, 0.5f));
	glEnable(GL_DEPTH_TEST);
	vertices = {
		// Front face
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,

		// Back face
		-1.0, -1.0, -1.0,
		-1.0,  1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0, -1.0, -1.0,

		// Top face
		-1.0,  1.0, -1.0,
		-1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0, -1.0,

		// Bottom face
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0,  1.0,
		-1.0, -1.0,  1.0,

		// Right face
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0,  1.0,  1.0,
		1.0, -1.0,  1.0,

		// Left face
		-1.0, -1.0, -1.0,
		-1.0, -1.0,  1.0,
		-1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0,
	};
	indices = {
		0,  1,  2,      0,  2,  3,    // front
		4,  5,  6,      4,  6,  7,    // back
		8,  9,  10,     8,  10, 11,   // top
		12, 13, 14,     12, 14, 15,   // bottom
		16, 17, 18,     16, 18, 19,   // right
		20, 21, 22,     20, 22, 23,   // left
	};

	shader = new Shader("Finki.vert", "Finki.frag");


	vaI = new VertexArray();
	vbI = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);

	vaI->AddBuffer(*vbI, layout);

	ibI = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());

	vertices.clear();
	indices.clear();
	draw::drawTorus(20, 40, vertices, indices);
	modelO = glm::mat4(1.0f);
	modelO = glm::translate(modelO, glm::vec3(1.0f, 0.0f, 0.0f));
	modelO = glm::scale(modelO, glm::vec3(1.5f, 1.5f, 1.5f));

	vaO = new VertexArray();
	vbO = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	vaO->AddBuffer(*vbO, layout);

	ibO = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());


}


void FinkiLogoState3D::Pause()
{

}

void FinkiLogoState3D::Resume()
{

}

void FinkiLogoState3D::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera->ProcessKeyboard(key, action);
}

void FinkiLogoState3D::HandleMouseEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseMovement(xoffset, yoffset);

}

void FinkiLogoState3D::HandleScrollEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void FinkiLogoState3D::Update(StateManager* stateManager, double delta)
{
	camera->Update(delta);
}

void FinkiLogoState3D::Render(StateManager* stateManager)
{
	renderer.Clear(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));

	shader->Bind();

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	view = camera->GetViewMatrix();
	projection = glm::perspective(glm::radians(camera->GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	shader->SetUniformMatrix4fv("projection", projection);
	shader->SetUniformMatrix4fv("view", view);
	shader->SetUniformMatrix4fv("model", modelI);
	shader->SetUniform3fv("color", glm::vec3(0.19f, 0.19f, 0.51f));
	vaI->Bind();
	renderer.Render(*vaI, *ibI, *shader, GL_TRIANGLES);

	shader->SetUniformMatrix4fv("model", modelO);
	shader->SetUniform3fv("color", glm::vec3(0.16f, 0.58f, 0.84f));
	vaO->Bind();
	renderer.Render(*vaO, *ibO, *shader, GL_TRIANGLE_STRIP);
}

FinkiLogoState3D::~FinkiLogoState3D() {
	shader->Unbind();
	vaI->Unbind();
	vbI->Unblind();
	ibI->Unblind();
	vaO->Unbind();
	vbO->Unblind();
	ibO->Unblind();
	delete shader;
	delete vaI;
	delete vbI;
	delete ibI;
	delete vaO;
	delete vbO;
	delete ibO;
	delete camera;
}
