#pragma once
#include "State.h"
class TestState : public State
{
private:

public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);
	TestState() { }

};
