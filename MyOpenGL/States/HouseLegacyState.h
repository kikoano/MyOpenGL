#pragma once
#include "State.h"

class HouseLegacyState : public State
{
public:
	void Init();

	void Pause();
	void Resume();

	void HandleEvents(StateManager* stateManager, int key, int action);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);

};
