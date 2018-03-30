#pragma once
#include <vector>
#include "../main.h"
#include <glad/glad.h>
#include "..//Draw.cpp"

class State;
class StateManager {
private:
	std::vector<State*> states;
public:
	void Init();

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	void HandleEvents(int key, int action);
	void Update(double delta);
	void Render();

	~StateManager();

	//Running()
	//Quit()

};