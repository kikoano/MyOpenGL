#include "LightState.h"
#include <stb/stb_image.h>
void LightState::Init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	glEnable(GL_DEPTH_TEST);
	vertices = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	lightingShader = new Shader("2.2.basic_lighting.vs", "2.2.basic_lighting.fs");
	lampShader = new Shader("2.2.lamp.vs", "2.2.lamp.fs");


	cubeVAO = new VertexArray();
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3); //color

	cubeVAO->AddBuffer(*vb, layout);
	
	lightVAO = new VertexArray();
	
	VertexBufferLayout layout2; // ?
	layout2.Push<float>(3);

	lightVAO->AddBuffer(*vb, layout2);

	/*texture1 = new Texture(RESOURCES_PATH + "Textures\\container.jpg", false);
	texture1->Bind(0);

	texture2 = new Texture(RESOURCES_PATH + "Textures\\awesomeface.png",true);
	texture2->Bind(1);*/

	lightingShader->Bind();
	lampShader->Bind();
	/*shader->SetUniform1i("texture1", 0);
	shader->SetUniform1i("texture2", 1);*/


	//clear all binding
	cubeVAO->Unbind();
	lightVAO->Unbind();
	vb->Unblind();
	ib->Unblind();
	//texture1->Unbind();
	//texture2->Unbind();
}


void LightState::Pause()
{

}

void LightState::Resume()
{

}

void LightState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera->ProcessKeyboard( key,  action);
}

void LightState::HandleMouseEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseMovement(xoffset, yoffset);
}

void LightState::HandleScrollEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void LightState::Update(StateManager* stateManager, double delta)
{
	camera->Update(delta);
}

void LightState::Render(StateManager* stateManager)
{
	renderer.Clear();
	//texture1->Bind(0);
	//texture2->Bind(1);

	lightingShader->Bind();
	lightingShader->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
	lightingShader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
	lightingShader->SetUniform3fv("lightPos", lightPos);
	lightingShader->SetUniform3fv("viewPos", camera->GetPosition());

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	lightingShader->SetUniformMatrix4fv("projection", projection);
	lightingShader->SetUniformMatrix4fv("view", view);

	// world transformation
	glm::mat4 model = glm::mat4(1.0f);
	lightingShader->SetUniformMatrix4fv("model", model);

	renderer.RenderArrays(*cubeVAO, 36, *lightingShader);


	lampShader->Bind();
	lampShader->SetUniformMatrix4fv("projection", projection);
	lampShader->SetUniformMatrix4fv("view", view);
	model = glm::mat4();
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	lampShader->SetUniformMatrix4fv("model", model);

	renderer.RenderArrays(*lightVAO, 36, *lampShader);


	
}

LightState::~LightState() {
	lightingShader->Unbind();
	lampShader->Unbind();
	cubeVAO->Unbind();
	lightVAO->Unbind();
	vb->Unblind();
	ib->Unblind();
	texture1->Unbind();
	texture2->Unbind();
	delete lightingShader;
	delete lampShader;
	delete cubeVAO;
	delete lightVAO;
	delete vb;
	delete ib;
	delete texture1;
	delete texture2;
	delete camera;
}
