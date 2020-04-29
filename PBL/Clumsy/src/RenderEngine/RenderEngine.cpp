#include "RenderEngine.h"

namespace Clumsy {

	RenderEngine::RenderEngine(GLFWwindow* window, Window& window2) :
		m_Window(&window2),
		m_GLFWWindow(window)
	{
		isRunning = false;
	}

	void RenderEngine::Start()
	{
		if (isRunning)
			return;

		Run();
	}

	void RenderEngine::Stop()
	{
		if (!isRunning)
			return;
		if (glfwWindowShouldClose(m_GLFWWindow))
		isRunning = false;
	}

	void RenderEngine::Run()
	{
		isRunning = true;

		long lastTime = Clumsy::GetTime();
		double unprocessedTime = 0;

		while (isRunning) 
		{
			long startTime = Clumsy::GetTime();
			long passedTime = startTime - lastTime;

			unprocessedTime += passedTime;
			if (m_Window->IsCloseRequested()) {
				Stop();
			}
			m_Window->render(m_GLFWWindow);
			Render();
		}

		CleanUp();
	}

	void RenderEngine::Render()
	{
		renderUtil.ClearScreen();
		renderUtil.InitGraphics();
		m_Window->SetIsCloseRequested(true);
	}

	void RenderEngine::CleanUp()
	{
		m_Window->~Window();
	}
}