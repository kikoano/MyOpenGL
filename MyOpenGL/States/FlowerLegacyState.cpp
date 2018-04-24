#include "FlowerLegacyState.h"

void FlowerLegacyState::Init()
{
	// Select the projection Matrix
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	// Reset The Projection Matrix
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	//glOrtho(-15.0f, 15.0, -15.0, 15.0, -1.0, 1.0);
	//glOrtho(-1.0f, 1.0, -1.0, 1.0, -1.0, 1.0);
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0, 1.0f);

	// Switch the active matrix to MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void FlowerLegacyState::Pause()
{
	
}

void FlowerLegacyState::Resume()
{

}

void FlowerLegacyState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

}

void FlowerLegacyState::Update(StateManager* stateManager, double delta)
{

}
 void drawPart() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(3.0f, 1.5f);
	glColor3f(0.5f, 0.0f, 1.0f);
	glVertex2f(6.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(3.0f, 1.5f);
	glVertex2f(4.3f, 4.3f);
	glEnd();
}
void FlowerLegacyState::Render(StateManager* stateManager)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glLineWidth(2.0f);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(i * 90, 0.0f, 0.0f, 1.0f);
		drawPart();
		if (i == 3) {
			glLineWidth(3.0f);
			glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(3.0f, 1.5f);
			glVertex2f(10.0f, 1.5f);
			glEnd();
		}
		glPopMatrix();
		glPushMatrix();
		glScalef(1.0f, -1.0f, 1.0f);
		glRotatef(i * 90, 0.0f, 0.0f, 1.0f);
		drawPart();
		glPopMatrix();
	}

	glColor3f(1.0f, 0.749f, 0.0f);
	draw::polyederLegacyFill(30, 0.0f, 0.0f, 0.8f);
	glColor3f(1.0f, 1.0f, 0.0f);
	draw::polyederLegacyFill(30, 0.0f, 0.0f, 0.6f);


}
void FlowerLegacyState::drawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

