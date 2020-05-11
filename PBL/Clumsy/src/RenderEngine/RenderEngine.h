#pragma once

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "RenderUtil.h"
#include "../Core/Time.h"
#include "../Core/Timestep.h"
#include "../Core/GameObject.h"
#include "../Audio/AudioMaster.h"
#include "Lighting.h"


namespace Clumsy 
{
	//class Shader;
	class RenderEngine 
	{
	public:
		RenderEngine(GLFWwindow* window, Window* window2, Camera* camera, AudioMaster* am);
		//void Start();
		//void Stop();
		void processInput(float deltaTime);
		Camera GetCamera() { return *m_Camera; }
		void Render(GameObject object);
		void AddLights(const BaseLight& light) { m_Lights.push_back(&light);}
		const BaseLight& GetActiveLight() const { return *m_ActiveLight; }

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
		std::vector<const BaseLight*> m_Lights;
		const BaseLight* m_ActiveLight;
		AudioMaster* m_Am;
		//Shader shader; // <-- probably will be needed

	};
}