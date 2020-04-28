#include <assimp/Importer.hpp>// przenieœæ do innej klasy
#include <assimp/aabb.h> //przenieœæ do innej klasy
#include "RenderEngine/Window.h"
#include "RenderEngine/RenderEngine.h"
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace Clumsy;

int main() {
	Window window(SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow* glfwWindow = window.GetGLFWWindow();
	RenderEngine renderEngine(glfwWindow, window);
	renderEngine.Start();
	window.~Window();
	return 0;
}