#pragma once
#include <vector>
#include <glad/glad.h>
#include "..//Draw.cpp"
#include "../Renderer.h"
#include "..//Texture.h"


class State;
class StateManager {
private:
	std::vector<State*> states;
public:
	void Init();

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	void HandleKeyEvents(int key, int action);
	void HandleMouseEvents(double xoffset, double yoffset);
	void HandleScrollEvents(double xoffset, double yoffset);
	void Update(double delta);
	void Render();

	~StateManager();

	//Running()
	//Quit()

};