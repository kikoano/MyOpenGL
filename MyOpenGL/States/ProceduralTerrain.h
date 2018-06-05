#pragma once
#include "State.h"
#include "..//Camera.h"
#include "../Materials/Terrian.h"
#include "../Light.h"
#include "../TerrainGenerator.h";
class ProceduralTerrain : public State
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	VertexArray* cubeVAO, *lightVAO;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* lightingShader, *lampShader;
	glm::mat4 modelPlate = glm::mat4(1.0f);
	glm::mat4 modelLamp = glm::mat4(1.0f);
	glm::mat4 view;
	glm::mat4 projection;
	Renderer renderer;
	Texture *texture1, *texture2;
	Camera *camera;
	Material *material;
	Light *light;
	glm::vec3 modelPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 lightPos = glm::vec3(-85.0f, 100.0f, 2.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	TerrainGenerator *generator;
	struct ImGuiVars {
		float persistence = 0.3f;
		float frequency = 0.02f;
		float amplitude = 50.0f;
		int octaves = 7;
		int randomseed = 2341;
		int vertexCount = 8; //9
		int vertexFull = 8; //9
		int size = 200; //400
		float cameraSpeed = 6.0f;
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
	~ProceduralTerrain();

};
