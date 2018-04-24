#include "TestState.h"

void TestState::Init()
{

}


void TestState::Pause()
{
	
}

void TestState::Resume()
{
	
}

void TestState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{
	
}

void TestState::HandleMouseEvents(double xoffset, double yoffset)
{
}

void TestState::HandleScrollEvents(double xoffset, double yoffset)
{
}

void TestState::Update(StateManager* stateManager, double delta)
{

}

void TestState::Render(StateManager* stateManager)
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

