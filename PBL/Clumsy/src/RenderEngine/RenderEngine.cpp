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
		m_Shader = new Shader("../Clumsy/src/Shaders/phongVS.glsl", "../Clumsy/src/Shaders/phongFS.glsl");
		m_Shader = new Shader("../Clumsy/res/shaders/model_loadingVS.glsl", "../Clumsy/res/shaders/model_loadingFS.glsl");

		glEnable(GL_DEPTH_TEST);
	}

	
	void RenderEngine::Render(GameObject object)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		processInput(timestep.GetSeconds());

		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
		m_Shader->setMat4("projection", projection);

		// camera/view transformation
		m_Shader->use();
		glm::mat4 view = m_Camera->GetViewMatrix();
		m_Shader->setMat4("view", view);

		m_Shader->setVec3("baseColor", 1.0f, 1.0f, 1.0);
		m_Shader->setVec3("ambientLight", 0.2f, 0.2f, 0.2f);
		//m_Shader->setDirectional("directionalLight", new DirectionalLight(glm::vec3(1.0,1.0,1.0), glm::vec3(1, 1, 1), 0.8f));


		for (unsigned int i = 0; i < m_Lights.size(); i++)
		{
			m_ActiveLight = m_Lights[i];
			//std::cout << m_Lights.size() << "hhhhhhhhhhhhhhh" << std::endl;
			m_Shader->setDirectional("directionalLight", (DirectionalLight*)&GetActiveLight());
		}
			object.RenderAll(*m_Shader, *this);//  <--- tutaj ma sie renderowac
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