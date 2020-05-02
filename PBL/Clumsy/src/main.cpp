
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

#include "Clumsy.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, 0.0f, 3.0f));

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

int main() 
{
	Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* glfwWindow = window->GetGLFWWindow();

	Clumsy::RenderEngine* renderEngine = new Clumsy::RenderEngine(glfwWindow, window, camera);
	glfwSetScrollCallback(glfwWindow, scroll_callback);

	Clumsy::Game* game = new Clumsy::Game();

	Clumsy::CoreEngine coreEngine(60.0f, window, renderEngine, game);

	renderEngine->Start();
	window->~Window();
	return 0;
}