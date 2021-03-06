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
#include "States\TextureTestState.h"
#include "States\Projection3DState.h"
#include "States\BallBounceState.h"
#include "States\CameraState.h"
#include "States\LightState.h"
#include "States\ColorCubeState.h"
#include "States\FinkiLogoState3D.h"
#include "States\Pacman3DState.h"
#include "States\TestCubeState.h"
#include "States\FpsCameraStrate.h"
#include "States\LightMapState.h"
#include "States\ProceduralTerrain.h"
#include "States\ModelState.h"

unsigned int WIDTH = 600;
unsigned int HEIGHT = 600;
StateManager stateManager;
bool wireflame = false;
bool debugMode = false;
int glVersion = 0;
int currentState = 0;

bool firstMouse = true;
float lastX;
float lastY;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char * argv[]) {
	WIDTH = 600;
	HEIGHT = 600;
	// Choose OpenGL version
	std::cout << "1.Legacy OpenGL" << std::endl;
	std::cout << "2.Modern OpenGL 2D" << std::endl;
	std::cout << "3.Modern OpenGL 3D" << std::endl;
	std::cout << "4.Modern Advanced OpenGL 3D" << std::endl;
	std::cout << "5.Procedural Terrian Generation" << std::endl;
	while (glVersion < 1 || glVersion >5)
		std::cin >> glVersion;
	system("cls");

	// Load GLFW and Create a Window
	glfwInit();
	if (glVersion == 1) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
		std::cout << "Legacy OpenGL" << std::endl;
	}
	else if (glVersion == 2) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "Modern OpenGL 2D" << std::endl;
	}
	else if (glVersion == 3) {
		WIDTH = 1280;
		HEIGHT = 720;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "Modern OpenGL 3D" << std::endl;
	}
	else if (glVersion == 4) {
		WIDTH = 1280;
		HEIGHT = 720;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "Modern Advanced OpenGL 3D" << std::endl;
	}
	else if (glVersion == 5) {
		WIDTH = 1280;
		HEIGHT = 720;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "Procedural Terrian Generation" << std::endl;
	}

	 lastX = WIDTH / 2.0f;
	 lastY = HEIGHT / 2.0f;
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSwapInterval(0); //vsync 1 on 0 off

	//State Manager
	stateManager.Init();
	if (glVersion == 5)
		stateManager.PushState(new ProceduralTerrain());
	else
		stateManager.PushState(new TestState());

	//imgui init
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, false); //future add ImGui_ImplGlfw_KeyCallback?
	ImGui::StyleColorsDark();
	ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
	if(glVersion<4)
		ImGui::SetNextWindowSizeConstraints(ImVec2(400.0f, 120.0f), ImVec2(400.0f, 120.0f));
	else
		ImGui::SetNextWindowSizeConstraints(ImVec2(400.0f, 310.0f), ImVec2(400.0f, 310.0f));
	//ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiSetCond_FirstUseEver);


	// Rendering Loop

	double lastTime = glfwGetTime();
	double deltaTime;

	while (!glfwWindowShouldClose(window)) {

		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		// input
		glfwPollEvents();

		ImGui_ImplGlfwGL3_NewFrame();

		stateManager.Update(deltaTime);
		stateManager.Render();

		// Render imgui

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());


		// Flip Buffers and Draw
		glfwSwapBuffers(window);


	}
	//stateManager.~StateManager(); //maybe

	// Destroy imgui
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	WIDTH = width;
	HEIGHT = height;
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
			else if (glVersion == 3) {
				stateManager.ChangeState(new Projection3DState());
			}
			else if (glVersion == 4) {
				stateManager.ChangeState(new LightMapState());
			}
		}
		if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new RombState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new HouseLegacyState());
			}
			else if (glVersion == 3) {
				stateManager.ChangeState(new BallBounceState());
			}
			else if (glVersion == 4) {
				stateManager.ChangeState(new ModelState());
			}
		}
		if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new FlowerState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new TabletLegacyState());
			}
			else if (glVersion == 3) {
				stateManager.ChangeState(new CameraState());
			}
			
		}
		if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new FinkiLogoState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new YingYangLegacyState());
			}
			else if (glVersion == 3) {
				stateManager.ChangeState(new ColorCubeState());
			}
		
		}
		if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new WheelColorsState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new FlowerLegacyState());
			}
			else if (glVersion == 3) {
				stateManager.ChangeState(new FinkiLogoState3D());
			}
		}
		if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new GradientState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new FlowerLegacyState());
			}
			else if (glVersion == 3) {
				stateManager.ChangeState(new Pacman3DState());
			}
		}
		if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new PacmanState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new FlowerLegacyState());
			}
			else if (glVersion == 3) {
				stateManager.ChangeState(new LightState());
			}
		}
		if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
			if (glVersion == 2)
				stateManager.ChangeState(new TextureTestState());
			else if (glVersion == 1) {
				stateManager.ChangeState(new FlowerLegacyState());
			}
			else if (glVersion == 3) {
				stateManager.ChangeState(new FpsCameraStrate());
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
	//Debug mode
	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
		debugMode = !debugMode;
		if (debugMode)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	stateManager.HandleKeyEvents(key, action);
	}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;
		if (!debugMode) {
			stateManager.HandleMouseEvents(xoffset, yoffset);
		}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (!debugMode) {
		stateManager.HandleScrollEvents(xoffset, yoffset);
	}
}