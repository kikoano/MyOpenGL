#include "CameraState.h"
#include <stb/stb_image.h>
void CameraState::Init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	glEnable(GL_DEPTH_TEST);
	vertices = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	shader = new Shader("Projection3D.vert", "Projection3D.frag");


	va = new VertexArray();
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2); //textures

	va->AddBuffer(*vb, layout);

	ib = new IndexBuffer(&indices[0], sizeof(indices[0])* indices.size());

	texture1 = new Texture(RESOURCES_PATH + "Textures\\container.jpg", false);
	texture1->Bind(0);

	texture2 = new Texture(RESOURCES_PATH + "Textures\\awesomeface.png",true);
	texture2->Bind(1);

	shader->Bind();
	shader->SetUniform1i("texture1", 0);
	shader->SetUniform1i("texture2", 1);


	//clear all binding
	va->Unbind();
	vb->Unblind();
	ib->Unblind();
	texture1->Unbind();
	texture2->Unbind();
}


void CameraState::Pause()
{

}

void CameraState::Resume()
{

}

void CameraState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera->ProcessKeyboard( key,  action);
}

void CameraState::HandleMouseEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseMovement(xoffset, yoffset);

}

void CameraState::HandleScrollEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void CameraState::Update(StateManager* stateManager, double delta)
{
	camera->Update(delta);
}

void CameraState::Render(StateManager* stateManager)
{
	float color[] = { 0.2f, 0.3f, 0.3f, 1.0f };
	renderer.Clear(color);
	texture1->Bind(0);
	texture2->Bind(1);

	shader->Bind();

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	view = camera->GetViewMatrix(); //camera->GetViewMatrix(); //glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(camera->GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	shader->SetUniformMatrix4fv("projection", projection);
	shader->SetUniformMatrix4fv("view", view);

	va->Bind();
	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model=glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader->SetUniformMatrix4fv("model", model);
		renderer.RenderArrays(*va, 36, *shader);
	}
}

CameraState::~CameraState() {
	shader->Unbind();
	va->Unbind();
	vb->Unblind();
	ib->Unblind();
	texture1->Unbind();
	texture2->Unbind();
	delete shader;
	delete va;
	delete vb;
	delete ib;
	delete texture1;
	delete texture2;
	delete camera;
}
