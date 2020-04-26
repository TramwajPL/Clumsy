#pragma once
#include <glad/glad.h>
#include <glfw3.h>
#include "../Core/Game.h"

namespace Clumsy {
	class Window {
	public:
		Window(int width, int height);

		virtual ~Window();
		void Init(int width, int height);
		void render(GLFWwindow* window);// 
		void stop();
		void run(GLFWwindow* window);
	private:
		bool isRunning = false;
		// timing
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;
		Game game;
	};
}