
#include "../pch.h"

#include "CoreEngine.h"
#include "../EventSystem/EventSystem.h"
#include <stb_image.h>

namespace Clumsy
{
	void CoreEngine::Start()
	{	
		m_IsRunning = true;		

		float lastFrame = 0.0f;

		while (!glfwWindowShouldClose(m_Window->GetGLFWWindow()))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// calculate delta time
			// --------------------
			float currentFrame = glfwGetTime();
			m_FrameTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			EventSystem::GetInstance()->ProcessEvents();

			m_Game->ProcessInput(m_Window->GetInput());

			m_Game->Update(m_FrameTime);

			m_Game->Render();

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