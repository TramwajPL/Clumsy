#pragma once

#include "Window.h"
#include "Camera.h"
#include "RenderUtil.h"
#include "../Core/Time.h"
#include "../Core/Timestep.h"


namespace Clumsy {

	class RenderEngine {
	public:
		RenderEngine(GLFWwindow* window, Window& window2, Camera* camera);
		void Start();
		void Stop();
		void processInput(float deltaTime);
		//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		Camera GetCamera() { return *m_Camera; }
		
	private:
		void Run();
		void Render();
		void CleanUp();
		GLFWwindow* m_GLFWWindow;
		Window* m_Window;
		bool isRunning;
		RenderUtil renderUtil;
		float m_LastFrameTime = 0.0f;
		Camera* m_Camera;
	};
}