#include "HouseLegacyState.h"


void HouseLegacyState::Init()
{
	// Select the projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset The Projection Matrix
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	glOrtho(0.0f, 30, 30, 0.0f, -1.0f, 1.0f);

	// Switch the active matrix to MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void HouseLegacyState::Pause()
{

}

void HouseLegacyState::Resume()
{

}

void HouseLegacyState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{




}

void HouseLegacyState::Update(StateManager* stateManager, double delta)
{


}

void HouseLegacyState::Render(StateManager* stateManager)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glBegin(GL_QUADS);
	glColor3f(0.996f, 0.6f, 0.004f);

	glVertex2f(2.0f, 24.0f);
	glVertex2f(7.0f, 26.0f);
	glVertex2f(7.0f, 21.0f);
	glVertex2f(2.0f, 19.0f);

	glVertex2f(10.0f, 27.0f);
	glVertex2f(10.0f, 22.0f);
	glVertex2f(15.0f, 24.0f);
	glVertex2f(15.0f, 29.0f);

	glVertex2f(2.0f, 19.0f);
	glVertex2f(15.0f, 24.5f);
	glVertex2f(15.0f, 16.0f);
	glVertex2f(2.0f, 12.0f);

	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(2.0f, 12.0f);
	glVertex2f(15.0f, 16.0f);
	glVertex2f(11.0f, 7.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(11.0f, 7.0f);
	glVertex2f(22.0f, 2.0f);
	glVertex2f(27.0f, 12.0f);
	glVertex2f(15.0f, 16.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(15.0f, 16.0f);
	glVertex2f(15.0f, 29.0f);
	glVertex2f(27.0f, 24.0f);
	glVertex2f(27.0f, 12.0f);
	glEnd();



}

