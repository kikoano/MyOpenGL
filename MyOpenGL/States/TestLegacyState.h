#pragma once
#include "State.h"

class TestLegacyState : public State
{
private:
	double x = 0;
	double y = 0;
	double speed = 200.0;
	double rotateSpeed = 0;
	double angle = 0;;
	bool direction[4];
	bool rotate[2];
	void drawLine(float x1, float y1, float x2, float y2);
public:
	void Init();

	void Pause();
	void Resume();

	void HandleEvents(StateManager* stateManager, int key, int action);
	void Update(StateManager* stateManager, double delta);
	void Render(StateManager* stateManager);

};
