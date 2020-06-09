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
	class ParticleGenerator;

	class RenderEngine
	{
	public:
		static RenderEngine* GetInstance();
		static void CreateInstance(GLFWwindow* window, Window* window2, Camera* camera);
		TextureClass loadTextureFromFile(const char* file, bool alpha);
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

		unsigned int loadCubemap(std::vector<std::string> faces);

		glm::mat4 getProjection() {
			return projection;
		}

		glm::mat4 getView() {
			return view;
		}

		Camera* getCamera() {
			return m_Camera;
		}

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
		Shader* particleShader;
		//Shader* shaderCube;
		Shader* shaderSkybox;

		unsigned int skyboxVAO, skyboxVBO, cubemapTexture;

		glm::mat4 projection;
		glm::mat4 view;

		TextureClass particleTexture;
		ParticleGenerator* particles;

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
	};
}