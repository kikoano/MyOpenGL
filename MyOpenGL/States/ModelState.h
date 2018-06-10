#pragma once
#include "State.h"
#include "..//Camera.h"
#include "..//Mesh.h"
#include "..//Tree.h"
#include "../Skybox.h"
class ModelState : public State
{
private:
	Skybox skybox;
	Shader shader = Shader("model.vert", "model.frag");
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), true);
	std::unique_ptr<Tree> tree1 = std::make_unique<Tree>(Tree::TYPE1, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model2 = glm::mat4(1.0f);
	glm::mat4 view;
	glm::mat4 projection;
	Renderer renderer;
	glm::vec3 modelPos = glm::vec3(0.0f, -1.75f, 0.0f);

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
	~ModelState();

};
