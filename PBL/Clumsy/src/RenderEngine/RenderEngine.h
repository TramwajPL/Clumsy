#pragma once
#include "Window.h"
#include "RenderUtil.h"
#include "../../RenderUtil.h"
#include "../Core/Time.h"


namespace Clumsy {

	class RenderEngine {
	public:
		RenderEngine(GLFWwindow* window, Window& window2);
		void Start();
		void Stop();
		
	private:
		void Run();
		void Render();
		void CleanUp();
		GLFWwindow* m_GLFWWindow;
		Window* m_Window;
		bool isRunning;
		RenderUtil renderUtil;
	};
}