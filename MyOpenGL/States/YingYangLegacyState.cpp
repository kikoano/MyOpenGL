#include "YingYangLegacyState.h"

#define min(x,y) ((x<y) ? x : y)
#define max(x,y) ((x<y) ? y : x)


void YingYangLegacyState::Init()
{
	// Select the projection Matrix
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	// Reset The Projection Matrix
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0, 1.0f);

	// Switch the active matrix to MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void YingYangLegacyState::Pause()
{
	
}

void YingYangLegacyState::Resume()
{

}

void YingYangLegacyState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

}

void YingYangLegacyState::Update(StateManager* stateManager, double delta)
{

}

void YingYangLegacyState::Render(StateManager* stateManager)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.1, 0.25, 0.41);
	glVertex2f(-10.0f, 10.0f);
	glColor3f(0.5, 0.65, 0.89);
	glVertex2f(10.0f, 10.0f);
	glVertex2f(10.0f, -10.0f);
	glVertex2f(-10.0f, -10.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	draw::polyederLegacyHalfFill(300, 0.0f, 0.0f, 8.0f, M_PI / 2);

	glColor3f(0.0f, 0.0f, 0.0f);
	draw::polyederLegacyHalfFill(300, 0.0f, 0.0f, 8.0f, 3*M_PI / 2);


	glColor3f(1.0f, 1.0f, 1.0f);
	draw::polyederLegacyFill(300, 0.0f, 4.0f, 4.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	draw::polyederLegacyFill(300, 0.0f, -4.0f, 4.0f);
	

	glColor3f(1.0f, 1.0f, 1.0f);
	draw::polyederLegacyFill(300, 0.0f, -4.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	draw::polyederLegacyFill(300, 0.0f, 4.0f, 1.0f);

}
void YingYangLegacyState::drawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

