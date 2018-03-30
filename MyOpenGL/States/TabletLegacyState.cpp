#include "TabletLegacyState.h"

void TabletLegacyState::Init()
{
	// Select the projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset The Projection Matrix
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	glOrtho(0.0f, 30.0f, 30.0f, 0.0f, -1.0f, 1.0f);

	// Switch the active matrix to MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TabletLegacyState::Pause()
{

}

void TabletLegacyState::Resume()
{

}

void TabletLegacyState::HandleEvents(StateManager* stateManager, int key, int action)
{




}

void TabletLegacyState::Update(StateManager* stateManager, double delta)
{


}

void TabletLegacyState::Render(StateManager* stateManager)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(5.0f, 5.0f);
	glVertex2f(25.0f,5.0f);
	glVertex2f(25.0f, 25.0f);
	glVertex2f(5.0f, 25.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(10.0f, 5.0f);
	glVertex2f(5.0f, 10.0f);

	glVertex2f(25.0f, 20.0f);
	glVertex2f(20.0f, 25.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(12.0f, 8.0f);
	glVertex2f(22.0f, 8.0f);
	glVertex2f(18.0f, 22.0f);
	glVertex2f(8.0f, 22.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(8.0f, 22.0f);
	glVertex2f(18.0f,22.0f);
	glVertex2f(18.0f, 23.5f);
	glVertex2f(8.0f, 23.5f);

	glVertex2f(18.0f, 22.0f);
	glVertex2f(18.0f, 23.5f);
	glVertex2f(22.0f, 9.5f);
	glVertex2f(22.0f, 8.0f);

	glVertex2f(13.0f, 10.0f);
	glVertex2f(20.0f, 10.0f);
	glVertex2f(17.0f, 20.0f);
	glVertex2f(10.0f, 20.0f);
	glEnd();
	draw::polyederLegacyFill(30, 13.5f, 21.0f, 0.7f);

}
