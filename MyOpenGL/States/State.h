#pragma once
#include "StateManager.h"
#include "../main.h"
#include "..//Shader.h"
#include "..//VertexBuffer.h"
#include "..//IndexBuffer.h"
#include "..//VertexArray.h"


class State {
public:
	virtual void Init() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleKeyEvents(StateManager* stateManager, int key, int action) = 0;
	virtual void HandleMouseEvents(double xoffset, double yoffset) = 0;
	virtual void HandleScrollEvents(double xoffset, double yoffset) = 0;
	virtual void Update(StateManager* stateManager, double delta) = 0;
	virtual void Render(StateManager* stateManager) = 0;

	virtual void RenderGui(StateManager* stateManager) {
		//ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::End();
	}

	void ChangeState(StateManager* stateManager, State* state) {
		stateManager->ChangeState(state);
	}
	virtual ~State() = 0 {}

};