#include <assimp/Importer.hpp>// przenie�� do innej klasy
#include <assimp/aabb.h> //przenie�� do innej klasy
#include "RenderEngine/Window.h"
#include "RenderEngine/RenderEngine.h"
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace Clumsy;

Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

int main() 
{
	Window window(SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* glfwWindow = window.GetGLFWWindow();
	RenderEngine renderEngine(glfwWindow, window, camera);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	renderEngine.Start();
	window.~Window();
	return 0;
}