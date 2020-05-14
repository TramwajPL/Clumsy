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
				glm::vec3(-4.5f,  0.0f,  1.0f),
				glm::vec3(4.5f, 0.0f, 1.0f),
				glm::vec3(0.0f,  0.0f, -4.0f),
				glm::vec3(0.0f,  0.0f, 4.0f)
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

		// SetDirectionalLight(direction, ambient, diffuse, specular) 
		m_Shader->SetDirectionalLight(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.5f, 0.5f, 0.5f));

		// point light 1
		m_Shader->SetPointLight("0" , pointLightPositions[0], glm::vec3(0.05f, 0.05f, 0.05),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
		// point light 2
		m_Shader->SetPointLight("1", pointLightPositions[1], glm::vec3(0.05f, 0.05f, 0.05),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
		// point light 3
		m_Shader->SetPointLight("2", pointLightPositions[2], glm::vec3(0.05f, 0.05f, 0.05),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
		// point light 4
		m_Shader->SetPointLight("3", pointLightPositions[3], glm::vec3(0.05f, 0.05f, 0.05),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));


		// spotLight
		m_Shader->SetSpotLight(m_Camera->GetPosition(), m_Camera->GetFront(), glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));


		for (unsigned int i = 0; i < m_Lights.size(); i++)
		{
			m_ActiveLight = m_Lights[i];
			//std::cout << m_Lights.size() << "hhhhhhhhhhhhhhh" << std::endl;
			//m_Shader->setDirectional("directionalLight", (DirectionalLight*)&GetActiveLight());
		}
			object.RenderAll(*m_Shader);//  <--- tutaj ma sie renderowac
		//TODO: renderowanie po drzewie calym



		 
		object.GetTransform();
		//object.RenderAll(*m_Shader);
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