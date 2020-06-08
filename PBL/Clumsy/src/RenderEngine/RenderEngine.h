#pragma once

#include <glad/glad.h>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Lighting.h"
#include "RenderUtil.h"
#include "PostProcessor.h"

#include "../Core/Time.h"
#include "../Core/Timestep.h"
#include "../Core/GameObject.h"
#include "../PhysicsEngine/Plane.h"


namespace Clumsy 
{
	//class Shader;
	class GUI;
	class Button;
	class StoreGUI;
	class WarehouseGUI;

	class RenderEngine
	{
	public:
		static RenderEngine* GetInstance();
		static void CreateInstance(GLFWwindow* window, Window* window2, Camera* camera);

		//void Start();
		//void Stop();
		void processInput(float deltaTime);
		Camera GetCamera() { return *m_Camera; }
		void Render(GameObject object);
		void RenderGUI();
		void AddLights(const BaseLight& light) { m_Lights.push_back(&light); }
		const BaseLight& GetActiveLight() const { return *m_ActiveLight; }
		void setFrustum(glm::mat4 viewProjection);
		bool pointInPlane(Plane p, glm::vec3 point);
		bool IsInFrustum(const Collider* aabb);
		int m_Counter = 0;
		std::vector<Plane> GetPl() { return pl; }

		Button* GetCenterButton() { return m_ButtonCameraOnPlayer; }
		Button* GetEndTurnButton() { return m_ButtonEndTurn; }
		Button* GetRestartButton() { return m_ButtonRestart; }
		StoreGUI* GetStoreGUI() { return m_StoreGUI; }
		WarehouseGUI* GetWarehouseGUI() { return m_WarehouseGUI; }

		bool isFrustumSet = false;
		bool wasCameraMoved = true;

		Shader* GetPostShader() { return m_Postprocessing; }

		PostProcessor* GetPostProcessor() { return Effects; }
		float GetShakeTime() { return m_ShakeTime; }
		void SetShakeTime(float time) { m_ShakeTime = time; }

		//movement
		bool m_Movement = false;
		glm::vec3* GetDestination() { return m_Destination; }
		glm::vec3* GetCurrentPosition() { return m_CurrentPosition; }
		glm::vec3* GetDeltaMove() { return m_DeltaMove; }
		void SetDestination(glm::vec3* pos) { m_Destination = pos; }
		void SetCurrentPosition(glm::vec3* pos) { m_CurrentPosition = pos; }
		void SetDeltaMove(glm::vec3* delta) { m_DeltaMove = delta; }

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
		Shader* m_Postprocessing;
		Shader* simpleDepthShader;
		Shader* debugDepthQuadShader;
		Shader* textShader;
		Shader* buttonShader;

		std::vector<const BaseLight*> m_Lights;
		const BaseLight* m_ActiveLight;

		std::vector<Plane> pl;

		//unsigned int depthMapFBO;
		//unsigned int depthMap;

		static RenderEngine* m_Instance;
		RenderEngine(GLFWwindow* window, Window* window2, Camera* camera);
		
		GUI* gui;
		Button* m_ButtonCameraOnPlayer;
		Button* m_ButtonEndTurn;
		Button* m_ButtonRestart;
		StoreGUI* m_StoreGUI;
		WarehouseGUI* m_WarehouseGUI;

		PostProcessor* Effects;
		float m_ShakeTime;

		//movement
		glm::vec3* m_Destination;
		glm::vec3* m_CurrentPosition;
		glm::vec3* m_DeltaMove;
	};
}