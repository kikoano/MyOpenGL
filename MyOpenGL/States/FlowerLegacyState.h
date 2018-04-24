#pragma once
#include "State.h"

class FlowerLegacyState : public State
{
private:
	void drawLine(float x1, float y1, float x2, float y2);
public:
	void Init();

	void Pause();
	void Resume();

	void HandleKeyEvents(StateManager* stateManager, int key, int action);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);

};
