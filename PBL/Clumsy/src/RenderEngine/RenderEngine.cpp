#include "../pch.h"

#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\ext\matrix_transform.hpp>

#include "Model.h"
#include "RenderEngine.h"
#include "../Core/Game.h"
#include "../Core/Timestep.h"
#include "../Core/GameObject.h"
#include "../Core/MousePicker.h"
#include "../PhysicsEngine/Aabb.h"
#include "../Core/EntityComponent.h"
#include "../Components/RenderModelComponent.h"

namespace Clumsy 
{
	RenderEngine::RenderEngine(GLFWwindow* window, Window* window2, Camera* camera) :
		m_Window(window2), 
		m_GLFWWindow(window), 
		m_Camera(camera)
	{
		isRunning = false;
		//m_Shader = new Shader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");
		//m_Shader = new Shader("../Clumsy/src/Shaders/phongVS.glsl", "../Clumsy/src/Shaders/phongFS.glsl");

		m_Shader = new Shader("../Clumsy/src/Shaders/lights_VS.glsl", "../Clumsy/src/Shaders/lights_FS.glsl");
		//m_Shader = new Shader("../Clumsy/res/shaders/model_loadingVS.glsl", "../Clumsy/res/shaders/model_loadingFS.glsl");


		glEnable(GL_DEPTH_TEST);
	}

	
	void RenderEngine::Render(GameObject object)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		glm::vec3 pointLightPositions[] = {
				glm::vec3(-1000.7f,  0.2f,  2.0f),
				glm::vec3(-100.3f, 0.0f, 1.0f),
				glm::vec3(-100.0f,  0.0f, 0.0f),
				glm::vec3(0.0f,  2.0f, -0.0f)
		};

		processInput(timestep.GetSeconds());

		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
		m_Shader->setMat4("projection", projection);

		// camera/view transformation
		m_Shader->use();
		
		//m_Shader->setInt("material.diffuse", 0);
	//	m_Shader->setInt("material.specular", 1);

		glm::mat4 view = m_Camera->GetViewMatrix();
		m_Shader->setMat4("view", view);

		m_Shader->use();
		m_Shader->setVec3("viewPos", m_Camera->GetPosition());
		m_Shader->setFloat("material.shininess", 32.0f);

		//m_Shader->setVec3("baseColor", 1.0f, 1.0f, 1.0f);
		//m_Shader->setVec3("ambientLight", 0.2f, 0.2f, 0.2f);
		//m_Shader->setDirectional("directionalLight", new DirectionalLight(glm::vec3(1.0,1.0,1.0), glm::vec3(1, 1, 1), 0.8f));
			  
		// directional light
		m_Shader->setVec3("dirLight.direction", -1.0f, -1.0f, -1.0f);
		m_Shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		m_Shader->setVec3("dirLight.diffuse", 0.9f, 0.9f, 0.9f);
		m_Shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		m_Shader->setVec3("pointLights[0].position", pointLightPositions[0]);
		m_Shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		m_Shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		m_Shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		m_Shader->setFloat("pointLights[0].constant", 1.0f);
		m_Shader->setFloat("pointLights[0].linear", 0.09);
		m_Shader->setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		m_Shader->setVec3("pointLights[1].position", pointLightPositions[1]);
		m_Shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		m_Shader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		m_Shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		m_Shader->setFloat("pointLights[1].constant", 1.0f);
		m_Shader->setFloat("pointLights[1].linear", 0.09);
		m_Shader->setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		m_Shader->setVec3("pointLights[2].position", pointLightPositions[2]);
		m_Shader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		m_Shader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		m_Shader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		m_Shader->setFloat("pointLights[2].constant", 1.0f);
		m_Shader->setFloat("pointLights[2].linear", 0.09);
		m_Shader->setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		m_Shader->setVec3("pointLights[3].position", pointLightPositions[3]);
		m_Shader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		m_Shader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		m_Shader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		m_Shader->setFloat("pointLights[3].constant", 1.0f);
		m_Shader->setFloat("pointLights[3].linear", 0.09);
		m_Shader->setFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		m_Shader->setVec3("spotLight.position", m_Camera->GetPosition());
		m_Shader->setVec3("spotLight.direction", -m_Camera->GetFront());
		m_Shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		m_Shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		m_Shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		m_Shader->setFloat("spotLight.constant", 1.0f);
		m_Shader->setFloat("spotLight.linear", 0.09);
		m_Shader->setFloat("spotLight.quadratic", 0.032);
		m_Shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_Shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		for (unsigned int i = 0; i < m_Lights.size(); i++)
		{
			m_ActiveLight = m_Lights[i];
			//std::cout << m_Lights.size() << "hhhhhhhhhhhhhhh" << std::endl;
			//m_Shader->setDirectional("directionalLight", (DirectionalLight*)&GetActiveLight());
		}
			object.RenderAll(*m_Shader);//  <--- tutaj ma sie renderowac
		//TODO: renderowanie po drzewie calym



		 
		object.GetTransform();
		object.RenderAll(*m_Shader);
	}

	void RenderEngine::CleanUp()
	{
		m_Window->~Window();
	}

	void RenderEngine::processInput(float deltaTime)
	{
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_GLFWWindow, true);

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_W) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_S) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(DOWN, deltaTime);
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_A) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_D) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_R) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_F) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(BACKWARD, deltaTime);

	}
}