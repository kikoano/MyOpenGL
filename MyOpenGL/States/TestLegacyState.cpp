#include "TestLegacyState.h"

#define min(x,y) ((x<y) ? x : y)
#define max(x,y) ((x<y) ? y : x)

float xc, yc, r;
int n;
void polyline2d(float points[][3], int nrPoints) {
	glBegin(GL_LINES);
	for (int i = 0; i < nrPoints - 1; i++) {
		if (points[i + 1][2]) {
			glVertex2f(points[i][0], points[i][1]);
			glVertex2f(points[i + 1][0], points[i + 1][1]);
		}
	}
	glEnd();
}
void drawCircle(float radius) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 300; i++) {
		double angle = 2 * /*M_PI **/ i / 300;
		double x = cos(angle);
		double y = sin(angle);
		glVertex2d(x, y);
	}
	glEnd();
}

//
void mnagolnik(int f, int n, float x0, float y0, float r) {
	/* x0, y0 centar, r radius na n-agolnikot */
	float angle, alfa;
	//angle = 2 * M_PI / n; // najdi go agolot
	//alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
	alfa += angle;
	glBegin(GL_LINES);
	while (n--) {
		glVertex2f(xc + r * cos(alfa), yc + r * sin(alfa));
		alfa += angle;
		glVertex2f(xc + r * cos(alfa), yc + r * sin(alfa));
	}
	glEnd();
}
void mnagolnikMy(int n, float x0, float y0, float r) {
	/* x0, y0 centar, r radius na n-agolnikot */
	float angle, alfa;
	//angle = 2 * M_PI / n; // najdi go agolot
	//alfa = -M_PI / 2 + angle / 2; // za da bide ispraven 
	alfa += angle;
	glBegin(GL_LINES);
	while (n--) {
		glVertex2f(x0 + r * cos(alfa), y0 + r * sin(alfa));
		alfa += angle;
		glVertex2f(x0 + r * cos(alfa), y0 + r * sin(alfa));
	}
	glEnd();
}

/* crta n-agolnik na proizvolno mesto na ekranot */
void polyeder(int f, int n, float x0, float y0, float r) {
	/* x0, y0 centar, r radius na n-agolnikot */
	float angle, alfa, xs, ys, xn, yn, s, c;
	//angle = 2 * M_PI / n;
	alfa = /*-M_PI /*/ 2 + angle / 2; /* za da bide ispraven */
	xs = r * cos(alfa);
	ys = r * sin(alfa);
	s = sin(angle);
	c = cos(angle);
	glBegin(GL_LINES);
	while (n--) {
		glVertex2f(xc + xs, yc + ys);
		xn = xs * c - ys * s;
		yn = ys * c + xs * s;
		glVertex2f(xc + xn, yc + yn);
		xs = xn;
		ys = yn;
	}
	glEnd();
}

/* crta n-agolnik na proizvolno mesto na ekranot */
void mnagolnik2(int f, int n, float x0, float y0, float r) {
	/* x0, y0 centar, r radius na n-agolnikot */
	float angle, alfa;
	//angle = 2 * M_PI / n;
	//alfa = -M_PI / 2 + angle / 2; /* za da bide ispraven */
	alfa += angle;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex2f(x0 + r * cos(alfa), y0 + r * sin(alfa));
	while (n--) {
		alfa += angle;
		glVertex2f(xc + r * cos(alfa), yc + r * sin(alfa));
	}
	glEnd();
}

/* crta n-agolnik na proizvolno mesto na ekranot */
void polyeder2(int f, int n, float x0, float y0, float r) {
	/* x0, y0 centar, r radius na n-agolnikot */
	float angle, alfa, xs, ys, xn, yn, s, c;
	//angle = 2 * M_PI / n;
	//alfa = -M_PI / 2 + angle / 2; /* za da bide ispraven */
	xs = r * cos(alfa);
	ys = r * sin(alfa);
	s = sin(angle);
	c = cos(angle);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex2f(x0 + xs, y0 + ys);
	while (n--) {
		xn = xs * c - ys * s;
		yn = ys * c + xs * s;
		glVertex2f(xc + xn, yc + yn);
		xs = xn;
		ys = yn;
	}
	glEnd();
}

void TestLegacyState::Init()
{
	//directions false
	for (int i = 0; i < sizeof(direction); i++)
		direction[i] = false;
	for (int i = 0; i < sizeof(direction); i++)
		rotate[i] = false;
	// Select the projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset The Projection Matrix
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	//glOrtho(-15.0f, 15.0, -15.0, 15.0, -1.0, 1.0);
	//glOrtho(-1.0f, 1.0, -1.0, 1.0, -1.0, 1.0);
	//glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, 1.0f, -1.0f);

	// Switch the active matrix to MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void TestLegacyState::Pause()
{

}

void TestLegacyState::Resume()
{

}

void TestLegacyState::HandleKeyEvents(StateManager* stateManager, int key, int action)
{

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
			direction[0] = true;
		else if (action == GLFW_RELEASE)
			direction[0] = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS)
			direction[1] = true;
		else if (action == GLFW_RELEASE)
			direction[1] = false;
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS)
			direction[2] = true;
		else if (action == GLFW_RELEASE)
			direction[2] = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS)
			direction[3] = true;
		else if (action == GLFW_RELEASE)
			direction[3] = false;
	}
	if (key == GLFW_KEY_LEFT) {
		if (action == GLFW_PRESS)
			rotate[0] = true;
		else if (action == GLFW_RELEASE)
			rotate[0] = false;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (action == GLFW_PRESS)
			rotate[1] = true;
		else if (action == GLFW_RELEASE)
			rotate[1] = false;
	}


}

void TestLegacyState::Update(StateManager* stateManager, double delta)
{
	if (direction[0]) {
		y -= speed * delta;
	}
	if (direction[1]) {
		y += speed * delta;
	}
	if (direction[2]) {
		x -= speed * delta;
	}
	if (direction[3]) {
		x += speed * delta;
	}
	if (rotate[0]) {
		angle -= speed * delta;
	}
	if (rotate[1]) {
		angle += speed * delta;
	}

}

void TestLegacyState::Render(StateManager* stateManager)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//1
	/*glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 2.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(2.0f, 2.0f);
	glVertex2f(2.0f, 1.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	drawLine(-15, 0, 15, 0);

	glColor3f(0.0f, 1.0f, 0.0f);
	drawLine(0, -15, 0, 15);

	float delta = 0.5f;
	glColor3f(1.0f, 1.0f, 1.0f);
	for (float i = -15; i < 15; i += 5) {
		drawLine(i, -delta,i,delta);
		drawLine(-delta, i, delta, i);
	}
	*/
	//2
	/*glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
	glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
	glVertex2f(-0.2f, 0.7f);
	glVertex2f(-0.8f, 0.7f);

	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex2f(-0.7f, -0.6f);
	glVertex2f(-0.1f, -0.6f);
	glVertex2f(-0.1f, 0.0f);
	glVertex2f(-0.7f, 0.0f);

	glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
	glVertex2f(-0.9f, -0.7f);
	glColor3f(1.0f, 1.0f, 1.0f); // White
	glVertex2f(-0.5f, -0.7f);
	glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
	glVertex2f(-0.5f, -0.3f);
	glColor3f(1.0f, 1.0f, 1.0f); // White
	glVertex2f(-0.9f, -0.3f);
	glEnd();

	glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(0.3f, -0.4f);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex2f(0.9f, -0.4f);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex2f(0.6f, -0.9f);
	glEnd();

	glBegin(GL_POLYGON);            // These vertices form a closed polygon
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex2f(0.4f, 0.2f);
	glVertex2f(0.6f, 0.2f);
	glVertex2f(0.7f, 0.4f);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.3f, 0.4f);
	glEnd();
	*/
	//3
	//mnagolnik(f, n, xc, yc, r);
	//polyeder(f, n, xc, yc, r);
	//mnagolnik2(f, n, xc, yc, r);
	//polyeder2(f, n, xc, yc, r);
	//mnagolnikMy(100, 0, 0, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef((WIDTH / 2.0f) + x, (HEIGHT / 2.0f) + y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(-50.0f, -50.0f);
	glVertex2f(-50.0f, 50.0f);
	glVertex2f(50.0f, 50.0f);
	glVertex2f(50.0f, -50.0f);
	glEnd();



}
void TestLegacyState::drawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

