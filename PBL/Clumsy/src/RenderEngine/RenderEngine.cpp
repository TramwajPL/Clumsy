#include "../pch.h"
#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\ext\matrix_transform.hpp>

#include "Model.h"
#include "RenderEngine.h"
#include "../Core/Timestep.h"
#include "../Core/GameObject.h"
#include "../Core/MousePicker.h"
#include "../Core/EntityComponent.h"
#include "../Core/Game.h"
#include "../Components/RenderModelComponent.h"

#include "../PhysicsEngine/Aabb.h"

namespace Clumsy {


	RenderEngine::RenderEngine(GLFWwindow* window, Window* window2, Camera* camera) :
		m_Window(window2), m_GLFWWindow(window), m_Camera(camera)
	{
		isRunning = false;
		m_Shader = new Shader("../Clumsy/res/shaders/model_loadingVS.glsl", "../Clumsy/res/shaders/model_loadingFS.glsl");

		glEnable(GL_DEPTH_TEST);

	}

	
	void RenderEngine::Render(GameObject object)
	{
		//renderUtil.ClearScreen();
		//renderUtil.InitGraphics();
		//m_Window->SetIsCloseRequested(true);
		// pass projection matrix to shader (note that in this case it could change every frame)
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		processInput(timestep.GetSeconds());

		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
		m_Shader->setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = m_Camera->GetViewMatrix();
		m_Shader->setMat4("view", view);
		 
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

		//if (glfwGetKey(m_GLFWWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
		//{
		//	object.GetTransform().SetPos(object.GetTransform().GetPos() - 2.0f);
		//	std::cout << "lewo" << std::endl;
		//	//object.GetTransform().GetPos() -= 2.0f;
		//}



	}
}