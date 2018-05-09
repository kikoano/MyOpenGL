#include "FpsCameraStrate.h"
#include <stb/stb_image.h>
void FpsCameraStrate::Init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f),false);

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
	lampShader = new Shader("lampColor.vert", "lampColor.frag");

	modelPlate = glm::translate(modelPlate, modelPos);
	modelPlate = glm::scale(modelPlate, glm::vec3(5.0f, 1.0f, 5.0f));


	cubeVAO = new VertexArray();
	vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3); //normals?

	cubeVAO->AddBuffer(*vb, layout);
	
	lightVAO = new VertexArray();
	
	VertexBufferLayout layout2; // ?
	layout2.Push<float>(3);
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


void FpsCameraStrate::Pause()
{

}

void FpsCameraStrate::Resume()
{

}

void FpsCameraStrate::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera->ProcessKeyboard( key,  action);
}

void FpsCameraStrate::HandleMouseEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseMovement(xoffset, yoffset);
}

void FpsCameraStrate::HandleScrollEvents(double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}
void FpsCameraStrate::RenderGui(StateManager* stateManager) {
		//ImGui::Begin("Edit");
		ImGui::SliderFloat3("Light Translation", &lightPos.x, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::ColorEdit3("Light Color", &lightColor.x); // Edit 3 floats representing a color
		ImGui::Text("Position Y: %f", camera->GetPosition().y);
		ImGui::Text("Velocity: %f", camera->GetVelocity().y);
		ImGui::Text("Acceration: %f", camera->GetAcceration());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//::End();
}

void FpsCameraStrate::Update(StateManager* stateManager, double delta)
{
	camera->Update(delta);
}

void FpsCameraStrate::Render(StateManager* stateManager)
{
	renderer.Clear();
	//texture1->Bind(0);
	//texture2->Bind(1);

	lightingShader->Bind();
	lightingShader->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
	lightingShader->SetUniform3fv("lightColor",lightColor);
	lightingShader->SetUniform3fv("lightPos", lightPos);
	lightingShader->SetUniform3fv("viewPos", camera->GetPosition());

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	lightingShader->SetUniformMatrix4fv("projection", projection);
	lightingShader->SetUniformMatrix4fv("view", view);

	// world transformation
	
	lightingShader->SetUniformMatrix4fv("model", modelPlate);

	renderer.RenderArrays(*cubeVAO, 36, *lightingShader);


	lampShader->Bind();
	lampShader->SetUniform3fv("color", lightColor);
	lampShader->SetUniformMatrix4fv("projection", projection);
	lampShader->SetUniformMatrix4fv("view", view);
	modelLamp = glm::mat4(1.0f);
	modelLamp = glm::translate(modelLamp, lightPos);
	modelLamp = glm::scale(modelLamp, glm::vec3(0.2f)); // a smaller cube
	lampShader->SetUniformMatrix4fv("model", modelLamp);

	renderer.RenderArrays(*lightVAO, 36, *lampShader);


	
}

FpsCameraStrate::~FpsCameraStrate() {
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
