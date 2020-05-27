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

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

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

		m_Shader = new Shader("../Clumsy/src/Shaders/shadows_shader_VS.glsl", "../Clumsy/src/Shaders/shadows_shader_FS.glsl");
		simpleDepthShader = new Shader("../Clumsy/src/Shaders/shadow_mapping_depth_VS.glsl", "../Clumsy/src/Shaders/shadow_mapping_depth_FS.glsl");
		debugDepthQuadShader = new Shader("../Clumsy/src/Shaders/debug_depth_quad_VS.glsl", "../Clumsy/src/Shaders/debug_depth_quad_FS.glsl");
		//m_Shader = new Shader("../Clumsy/res/shaders/model_loadingVS.glsl", "../Clumsy/res/shaders/model_loadingFS.glsl");
		
		glEnable(GL_DEPTH_TEST);


		glGenFramebuffers(1, &depthMapFBO);
		// create depth texture
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_Shader->use();
		m_Shader->setInt("diffuseTexture", 0);
		m_Shader->setInt("shadowMap", 1);
		debugDepthQuadShader->use();
		debugDepthQuadShader->setInt("depthMap", 0);


	}

	void RenderEngine::CreateInstance(GLFWwindow* window, Window* window2, Camera* camera)
	{
		assert(!m_Instance);
		m_Instance = new RenderEngine(window, window2, camera);
	}

	RenderEngine* RenderEngine::GetInstance()
	{
		assert(m_Instance);
		return m_Instance;
	}
	
	void RenderEngine::Render(GameObject object)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		//glm::vec3 pointLightPositions[] = {
		//		glm::vec3(-4.5f,  0.0f,  1.0f),
		//		glm::vec3(4.5f, 0.0f, 1.0f),
		//		glm::vec3(1.0f,  0.0f, -4.0f),
		//		glm::vec3(1.0f,  0.0f, 4.0f)
		//};

		// configure depth map FBO
		// -----------------------
		
				// lighting info
		glm::vec3 lightPos(20.0f, 40.0f, -20.0f);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0f, far_plane = 15.0f;
		
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(glm::vec3 (2.0f, 4.0f, -2.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		// render scene from light's point of view
		simpleDepthShader->use();
		simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		object.RenderAll(*simpleDepthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// reset viewport
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 2. render scene as normal using the generated depth/shadow map  
	   // --------------------------------------------------------------
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Shader->use();
		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = m_Camera->GetViewMatrix();
		m_Shader->setMat4("projection", projection);
		m_Shader->setMat4("view", view);
		// set light uniforms
		m_Shader->SetDirectionalLight(0.6, m_Camera->GetPosition(), lightPos, lightSpaceMatrix);
;
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		object.RenderAll(*m_Shader);


		processInput(timestep.GetSeconds());

		/////////////////////////////////////////////////////////// OLD GUY

		//glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
		//m_Shader->setMat4("projection", projection);

		//// camera/view transformation
		//m_Shader->use();
		//
		////m_Shader->setInt("material.diffuse", 0);
		////	m_Shader->setInt("material.specular", 1);

		//glm::mat4 view = m_Camera->GetViewMatrix();
		//m_Shader->setMat4("view", view);

		////m_Shader->use();
		//m_Shader->setVec3("viewPos", m_Camera->GetPosition());
		//m_Shader->setFloat("material.shininess", 32.0f);

		//// SetDirectionalLight(direction, ambient, diffuse, specular) 
		//m_Shader->SetDirectionalLight(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.05f, 0.05f, 0.05f),
		//	glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));

		//// point light 1
		//m_Shader->SetPointLight("0" , pointLightPositions[0], glm::vec3(0.05f, 0.05f, 0.05),
		//	glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
		//// point light 2
		//m_Shader->SetPointLight("1", pointLightPositions[1], glm::vec3(0.05f, 0.05f, 0.05),
		//	glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
		//// point light 3
		//m_Shader->SetPointLight("2", pointLightPositions[2], glm::vec3(0.05f, 0.05f, 0.05),
		//	glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
		//// point light 4
		//m_Shader->SetPointLight("3", pointLightPositions[3], glm::vec3(0.05f, 0.05f, 0.05),
		//	glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));

		//// spotLight
		//m_Shader->SetSpotLight(m_Camera->GetPosition(), m_Camera->GetFront(), glm::vec3(0.0f, 0.0f, 0.0f),
		//	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		///////////////////////////////////////////////////


		//object.RenderAll(*m_Shader);


		//object.GetTransform();
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