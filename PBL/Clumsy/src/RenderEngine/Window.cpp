#include "Window.h"
#include <iostream>
#include "../Core/Time.h"


namespace Clumsy {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
	static bool s_GLFWInitialized = false;

	Window::Window(int width, int height)
	{
		Init(width, height);
	}
	Window::~Window(){}

	void Window::render(GLFWwindow* window)
	{
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	void Window::stop()
	{
		if (!isRunning)
			return;
		isRunning = false;
	}

	void Window::run(GLFWwindow* window)
	{
		bool isRender = false;
		isRunning = true;
		while (isRunning)
		{
			isRender = true;
			// per-frame time logic
			// --------------------
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (glfwWindowShouldClose(window))
				stop();
			game.Input();

			render(window);
		}
	}

	void Window::Init(int width, int height) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		GLFWwindow* window = glfwCreateWindow(width, height, "Disaster", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			//return -1;
		}

		//// render loop
		//while (!glfwWindowShouldClose(window))
		//{
		//	render(window);
		//}
		if (isRunning)
			return;
		run(window);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}
}