#pragma once
#include "StateManager.h"
#include "..//Shader.h"
#include "..//VertexBuffer.h"
#include "..//IndexBuffer.h"

class State {
public:
	virtual void Init() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(StateManager* stateManager, int key, int action) = 0;
	virtual void Update(StateManager* stateManager, double delta) = 0;
	virtual void Render(StateManager* stateManager) = 0;

	void ChangeState(StateManager* stateManager, State* state) {
		stateManager->ChangeState(state);
	}
	virtual ~State() = 0 {}

};