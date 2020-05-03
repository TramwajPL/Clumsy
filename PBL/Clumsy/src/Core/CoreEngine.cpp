
#include "../pch.h"

#include "CoreEngine.h"

namespace Clumsy
{
	void CoreEngine::Start()
	{
	/*	if (m_IsRunning)
		{
			return;
		}

		m_IsRunning = true;



		while (m_IsRunning)
		{
			m_Game->Render(m_RenderEngine);

			glfwSwapBuffers(m_Window->GetGLFWWindow());
			glfwPollEvents();
		}*/
		///////////////////
		m_IsRunning = true;
		

		while (!glfwWindowShouldClose(m_Window->GetGLFWWindow()))
		{
			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_Game->Render(m_RenderEngine);

			glfwSwapBuffers(m_Window->GetGLFWWindow());
			glfwPollEvents();
		}

		glfwTerminate();

	}

	void CoreEngine::Stop()
	{
		m_IsRunning = false;
	}
}