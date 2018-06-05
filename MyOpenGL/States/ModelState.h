#pragma once
#include "State.h"
#include "..//Camera.h"
#include "..//Mesh.h"
#include "..//Tree.h"
class ModelState : public State
{
private:
	Shader shader = Shader("model.vert", "model.frag");
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), true);
	Mesh *myMesh = new Mesh("f_tree1\\obj__tree1.obj");
	Tree tree = Tree(Tree::TYPE1, glm::vec3(0.0f, 0.0f, 0.0f));
	Tree tree2 = Tree(Tree::TYPE2, glm::vec3(0.0f, 0.0f, 100.0f));
	//Model myModel = Model(RESOURCES_PATH + "Models\\nanosuit\\nanosuit.obj");
	//Model myModel2 =Model(RESOURCES_PATH + "Models\\Tree\\Tree.obj");
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
