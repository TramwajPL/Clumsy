#pragma once

#include "Window.h"
#include "Camera.h"
#include "RenderUtil.h"
#include "../Core/Time.h"
#include "../Core/Timestep.h"
#include "../Core/GameObject.h"
#include "Shader.h"

namespace Clumsy {
	//class Shader;
	class RenderEngine {
	public:
		RenderEngine(GLFWwindow* window, Window* window2, Camera* camera);
		//void Start();
		//void Stop();
		void processInput(float deltaTime);
		Camera GetCamera() { return *m_Camera; }
		void Render(GameObject object);
		
	private:
		//void Run();
		void CleanUp();
		GLFWwindow* m_GLFWWindow;
		Window* m_Window;
		bool isRunning;
		RenderUtil renderUtil;
		float m_LastFrameTime = 0.0f;
		Camera* m_Camera;
		Shader* m_Shader;
		
		//Shader shader; // <-- probably will be needed
	};
}