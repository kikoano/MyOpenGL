#include "ModelState.h"

void ModelState::Init()
{
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	model = glm::translate(model, modelPos);
	tree1->Init();
	skybox.Init();
}


void ModelState::Pause()
{

}

void ModelState::Resume()
{

}

void ModelState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera.ProcessKeyboard(key, action);
}

void ModelState::HandleMouseEvents(double xoffset, double yoffset)
{
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void ModelState::HandleScrollEvents(double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void ModelState::RenderGui(StateManager* stateManager) {
	ImGui::SliderFloat3("Model Translation", &modelPos.x, -200.0f, 200.0f);
	ImGui::Text("X:%f Y:%f Z:%f",camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}

void ModelState::Update(StateManager* stateManager, double delta)
{
	camera.Update(delta);
	tree1->Update(delta);
	skybox.Update(delta);
}

void ModelState::Render(StateManager* stateManager)
{
	renderer.Clear();

	shader.Bind();
	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	Entity::UpdateProView(projection, view);

	shader.SetUniformMatrix4fv("projection", projection);
	shader.SetUniformMatrix4fv("view", view);

	// world transformation
	//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	

	shader.SetUniformMatrix4fv("model", model);
	//myMesh->draw(shader);
	tree1->Render();
	skybox.Render();
}

ModelState::~ModelState() {
	shader.Unbind();
}
