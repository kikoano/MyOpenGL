#include "main.h"
#include "States\StateManager.h"
#include "States\TestState.h"
#include "States\TriangleState.h"
#include "States\TestLegacyState.h"
#include "States\QuardState.h"
#include "States\HouseLegacyState.h"
#include "States\TabletLegacyState.h"
#include "States\FlowerLegacyState.h"
#include "States\YingYangLegacyState.h"
#include "States\TransformState.h"
#include "States\WheelColorsState.h"
#include "States\FinkiLogoState.h"
#include "States\RombState.h"
#include "States\FlowerState.h"
#include "States\GradientState.h"
#include "States\PacmanState.h"



StateManager stateManager;
bool wireflame = false;
int glVersion = 0;
int currentState = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char * argv[]) {

	// Choose OpenGL version
	std::cout << "1.Legacy OpenGL" << std::endl;
	std::cout << "2.Modern OpenGL" << std::endl;
	while (glVersion == 0)
		std::cin >> glVersion;
	system("cls");

	// Load GLFW and Create a Window
	glfwInit();
	if (glVersion == 1) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
		std::cout << "OpenGL 2.0 " << std::endl;
	}
	else if (glVersion == 2) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "OpenGL 3.3 " << std::endl;
	}
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	auto window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);

	// Check for Valid Context
	if (window == nullptr) {
		fprintf(stderr, "Failed to Create OpenGL Context");
		return EXIT_FAILURE;
	}

	// Create context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//gladLoadGL();
	//fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
	// Set keys
	glfwSetKeyCallback(window, key_callback);

	glfwSwapInterval(0); //vsync 1 on 0 off

	//State Manager
	stateManager.Init();
	stateManager.PushState(new TestState());

	// Rendering Loop

	double lastTime = glfwGetTime();
	double deltaTime;
	while (!glfwWindowShouldClose(window)) {

		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		// input
		glfwPollEvents();

		stateManager.Update(deltaTime);
		stateManager.Render();

		// Flip Buffers and Draw
		glfwSwapBuffers(window);


	}
	//stateManager.~StateManager(); //maybe
	glfwTerminate();
	return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (currentState != key) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
			stateManager.ChangeState(new TestState());
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new TriangleState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new TestLegacyState());
			}
		}
		if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new RombState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new HouseLegacyState());
			}
		}
		if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new FlowerState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new TabletLegacyState());
			}
		}
		if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new FinkiLogoState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new YingYangLegacyState());
			}
		}
		if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new WheelColorsState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new FlowerLegacyState());
			}
		}
		if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new GradientState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new FlowerLegacyState());
			}
		}
		if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new PacmanState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new FlowerLegacyState());
			}
		}
	}
	currentState = key;
	//WireFrame mode
	if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) {
		wireflame = !wireflame;
		if (wireflame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	stateManager.HandleEvents(key, action);
}