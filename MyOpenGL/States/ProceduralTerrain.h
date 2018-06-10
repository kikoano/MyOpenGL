#pragma once
#include "State.h"
#include "..//Camera.h"
#include "../Materials/Terrian.h"
#include "../Light.h"
#include "../TerrainGenerator.h";
#include "../Tree.h"
#include "../Grass.h";
#include "../Skybox.h"
#include "../TerrainMesh.h"

class ProceduralTerrain : public State
{
private:
	glm::mat4 view;
	glm::mat4 projection;
	Renderer renderer;
	Camera camera;
	glm::vec3 lightPos = glm::vec3(-85.0f, 100.0f, 2.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	std::unique_ptr<Light> light = std::make_unique<Light>(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	std::unique_ptr<TerrainMesh> terrian;
	Skybox skybox;
	std::vector<std::unique_ptr<Entity>> entities;
	struct ImGuiVars {
		float persistence = 0.3f;
		float frequency = 0.037f; //0.02
		float amplitude = 50.0f;
		int octaves = 7;
		int randomseed = 2341;
		int vertexCount = 8; //9
		int size = 200; //400
		float cameraSpeed = 20.0f;
		int scaleTiles = 10;
	} imGuiVars;
public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset);
	void HandleScrollEvents(double xoffset, double yoffset);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	void RenderGui(StateManager* stateManager) override;
	void GenerateTrees();
	~ProceduralTerrain();

};
