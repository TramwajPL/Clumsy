
#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>

#include "Clumsy.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Clumsy::Camera* camera = new Clumsy::Camera(glm::vec3(0.0f, -5.0f, 3.0f));

Clumsy::Window* window = new Clumsy::Window(SCR_WIDTH, SCR_HEIGHT);

glm::mat4 projectionMP = glm::perspective(glm::radians(camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

Clumsy::MousePicker mp(camera, window, projectionMP);

glm::vec3 v1 = glm::vec3(0.0f, 0.0f, -2.0f) - glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 v2 = glm::vec3(0.0f, 0.0f, -2.0f) + glm::vec3(1.0f, 1.0f, 1.0f);

Clumsy::Aabb a1(v1, v2);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Cursor Position at " << xpos << " : " << ypos << std::endl;
		mp.Update();

		std::cout << "RAY: " << mp.GetCurrentRay().x << " , " << mp.GetCurrentRay().y << " , " << mp.GetCurrentRay().z << std::endl;

		std::cout << mp.CheckCollision(a1) << std::endl;
	}
}

int main() 
{
	GLFWwindow* glfwWindow = window->GetGLFWWindow();

	Clumsy::RenderEngine* renderEngine = new Clumsy::RenderEngine(glfwWindow, window, camera);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

	Clumsy::Game* game = new Clumsy::Game();

	Clumsy::CoreEngine coreEngine(60.0f, window, renderEngine, game);

	renderEngine->Start();
	window->~Window();
	return 0;
}