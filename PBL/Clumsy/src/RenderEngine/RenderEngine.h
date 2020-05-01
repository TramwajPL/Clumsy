#pragma once
#include "Window.h"
#include "RenderUtil.h"
#include "../../RenderUtil.h"
#include "../Core/Time.h"
#include "Camera.h"
#include "../Core/Timestep.h"


namespace Clumsy {

	class RenderEngine {
	public:
		RenderEngine(GLFWwindow* window, Window& window2, Camera* camera);
		void Start();
		void Stop();
		void processInput(float deltaTime);
		
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