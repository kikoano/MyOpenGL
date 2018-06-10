#include "ProceduralTerrain.h"
#include <glm/gtx/norm.hpp>

TerrainGenerator TerrainMesh::generator;
void ProceduralTerrain::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera = Camera(glm::vec3(10.0f, 50.0f, 100.0f), true);
	camera.SetMovementSpeed(imGuiVars.cameraSpeed);

	imGuiVars.vertexCount = pow(2, imGuiVars.vertexCount);
	TerrainMesh::generator.SetPerlin(imGuiVars.vertexCount, imGuiVars.size, imGuiVars.randomseed, imGuiVars.persistence, imGuiVars.frequency, imGuiVars.amplitude, imGuiVars.octaves);
	terrian = std::make_unique<TerrainMesh>(glm::vec3(0.0f, 0.0f, 0.0f));
	terrian->Generate(imGuiVars.vertexCount, imGuiVars.size);

	skybox.Init();
	light->Init();
	terrian->Init();

	GenerateTrees();
}


void ProceduralTerrain::Pause()
{

}

void ProceduralTerrain::Resume()
{

}

void ProceduralTerrain::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	camera.ProcessKeyboard(key, action);
}

void ProceduralTerrain::HandleMouseEvents(double xoffset, double yoffset)
{
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void ProceduralTerrain::HandleScrollEvents(double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void ProceduralTerrain::RenderGui(StateManager* stateManager) {
	ImGui::SliderFloat3("Light Translation", &lightPos.x, -200.0f, 200.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	light->SetPosition(lightPos);
	ImGui::ColorEdit3("Light Color", &lightColor.x); // Edit 3 floats representing a color
	light->SetDiffuse(lightColor);
	light->SetSpecular(lightColor);
	ImGui::SliderFloat("Camera speed", &imGuiVars.cameraSpeed, 0.0f, 100.0f);
	/*if (ImGui::SliderInt("Vertex Count", &imGuiVars.vertexCount, 0.0f, 512.0f))
		imGuiVars.vertexCount = pow(2, round(log2(imGuiVars.vertexCount)));*/
	ImGui::SliderInt("Size", &imGuiVars.size, 0.0f, 1000.0f);
	ImGui::SliderInt("Seed", &imGuiVars.randomseed, 0.0f, 100000.0f);
	ImGui::SliderFloat("Persistence", &imGuiVars.persistence, 0.0f, 1.0f);
	ImGui::SliderFloat("Frequency", &imGuiVars.frequency, 0.0f, 1.0f);
	ImGui::SliderFloat("Amplitude", &imGuiVars.amplitude, 0.0f, 100.0f);
	ImGui::SliderInt("Octaves", &imGuiVars.octaves, 0.0f, 10.0f);
	ImGui::SliderInt("Scale Tiles", &imGuiVars.scaleTiles, 0.0f, 100.0f);
	if (ImGui::Button("Generate")) {
		TerrainMesh::generator.SetPerlin(imGuiVars.vertexCount, imGuiVars.size,imGuiVars.randomseed, imGuiVars.persistence, imGuiVars.frequency, imGuiVars.amplitude, imGuiVars.octaves);
		terrian = std::make_unique<TerrainMesh>(glm::vec3(0.0f, 0.0f, 0.0f));
		terrian->Generate(imGuiVars.vertexCount, imGuiVars.size);
		terrian->Init();
		GenerateTrees();
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void ProceduralTerrain::GenerateTrees()
{
	entities.clear();
	for (int i = 0; i < imGuiVars.vertexCount; i++) {
		for (int j = 0; j < imGuiVars.vertexCount; j++) {
			double noise = TerrainMesh::generator.GetPerlinNoise().GetHeight(j, i);
			if (noise * 60 < 0) {
				int random = rand() % 1000;
				if (random == 999) {
					int type = rand() % 6;
					std::unique_ptr<Tree> tree = std::make_unique<Tree>(static_cast<Tree::Type>(type), glm::vec3((float)j / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size, noise - 0.5f, (float)i / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size));
					tree->SetScale(imGuiVars.size);
					tree->Init();
					entities.push_back(std::move(tree));
				}
				else if (random == 998 || random == 997) {
					int type = rand() % 2 + 1;
					std::unique_ptr<Grass> grass = std::make_unique<Grass>(static_cast<Grass::Type>(type), glm::vec3((float)j / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size, noise - 0.5f, (float)i / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size));
					grass->SetScale(imGuiVars.size);
					grass->Init();
					entities.push_back(std::move(grass));
				}
				else if (random >= 993 && random < 997) {
					std::unique_ptr<Grass> grass = std::make_unique<Grass>(Grass::TYPE1, glm::vec3((float)j / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size, noise - 0.5f, (float)i / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size));
					grass->SetScale(imGuiVars.size);
					grass->Init();
					entities.push_back(std::move(grass));
				}
				else if (random == 991 || random == 992) {
					int type = rand() % 6 + 3;
					std::unique_ptr<Grass> grass = std::make_unique<Grass>(static_cast<Grass::Type>(type), glm::vec3((float)j / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size, noise - 0.5f, (float)i / (float)(imGuiVars.vertexCount - 1) * imGuiVars.size));
					grass->SetScale(imGuiVars.size);
					grass->Init();
					entities.push_back(std::move(grass));
				}
			}
		}
	}
}

void ProceduralTerrain::Update(StateManager* stateManager, double delta)
{
	camera.Update(delta);
	camera.SetMovementSpeed(imGuiVars.cameraSpeed);
	for (auto &e : entities) {
		if (glm::length2(camera.GetPosition() - e->GetPosition()) > 24000.0f)
			continue;
		e->Update(delta);
	}
	std::sort(entities.begin(), entities.end(),
		[&](const std::unique_ptr<Entity> &a, const std::unique_ptr<Entity> &b)
	{
		return glm::length2(camera.GetPosition() - a->GetPosition()) >= glm::length2(camera.GetPosition() - b->GetPosition());
	});
	skybox.Update(delta);
	light->GetModel() = glm::translate(light->GetModel(), light->GetPosition());
	light->Update(delta);
	terrian->Update(delta);

}

void ProceduralTerrain::Render(StateManager* stateManager)
{
	renderer.Clear();

	terrian->UpdateLight(*light, camera, imGuiVars.scaleTiles);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 160.0f);
	glm::mat4 view = camera.GetViewMatrix();

	light->Render();
	terrian->Render();

	Entity::UpdateProView(projection, view);
	skybox.Render();
	for (auto &e : entities) {
		if (glm::length2(camera.GetPosition() - e->GetPosition()) > 24000.0f)
			continue;
		e->Render();
	}
}

ProceduralTerrain::~ProceduralTerrain() {
	glDisable(GL_CULL_FACE);
}
