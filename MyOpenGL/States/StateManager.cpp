#include "StateManager.h"
#include "State.h"

void StateManager::Init() {

}

void StateManager::ChangeState(State* state)
{
	while (!states.empty()){
		states.back()->~State();
		states.pop_back();
	}
	states.push_back(state);
	states.back()->Init();
}
void StateManager::PushState(State* state)
{
	if (!states.empty()) {
		states.back()->Pause();
	}

	states.push_back(state);
	states.back()->Init();
}

void StateManager::PopState()
{
	if (!states.empty()) {
		states.back()->~State();
		states.pop_back();
	}

	if (!states.empty()) {
		states.back()->Resume();
	}
}

void StateManager::HandleKeyEvents(int key, int action)
{
	states.back()->HandleKeyEvents(this, key, action);
}

void StateManager::HandleMouseEvents(double xoffset, double yoffset)
{
	states.back()->HandleMouseEvents(xoffset, yoffset);
}

void StateManager::HandleScrollEvents(double xoffset, double yoffset)
{
	states.back()->HandleMouseEvents(xoffset, yoffset);
}

void StateManager::Update(double delta)
{
	states.back()->Update(this, delta);
}

void StateManager::Render()
{
	states.back()->Render(this);
}
StateManager::~StateManager() {
	for (int i = 0; i < states.size(); i++)
	{
		delete (states[i]);
	}
	states.clear();
}
