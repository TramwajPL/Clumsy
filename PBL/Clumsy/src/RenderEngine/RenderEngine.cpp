#include "../pch.h"

#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>
#include <stb_image.h>

#include "Model.h"
#include "RenderEngine.h"

#include "../GUI/GUI.h"
#include "../GUI/Button.h"
#include "../GUI/StoreGUI.h"
#include "../GUI/WarehouseGUI.h"

#include "../Core/Game.h"
#include "../Core/Timestep.h"
#include "../Core/GameObject.h"
#include "../Core/MousePicker.h"
#include "../PhysicsEngine/Aabb.h"
#include "../Core/EntityComponent.h"
#include "../Components/RenderModelComponent.h"
#include "../Particles/ParticleGenerator.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

//const unsigned int SCR_WIDTH = 1366;
//const unsigned int SCR_HEIGHT = 768;//zmieniæ

namespace Clumsy
{
	RenderEngine::RenderEngine(GLFWwindow* window, Window* window2, Camera* camera) :
		m_Window(window2),
		m_GLFWWindow(window),
		m_Camera(camera)
	{
		isRunning = false;

		m_Shader = new Shader("../Clumsy/src/Shaders/shadows_shader_VS.glsl", "../Clumsy/src/Shaders/shadows_shader_FS.glsl");
		m_Postprocessing = new Shader("../Clumsy/src/Shaders/post_VS.glsl", "../Clumsy/src/Shaders/post_FS.glsl");
		simpleDepthShader = new Shader("../Clumsy/src/Shaders/shadow_mapping_depth_VS.glsl", "../Clumsy/src/Shaders/shadow_mapping_depth_FS.glsl");
		debugDepthQuadShader = new Shader("../Clumsy/src/Shaders/debug_depth_quad_VS.glsl", "../Clumsy/src/Shaders/debug_depth_quad_FS.glsl");
		particleShader = new Shader("../Clumsy/src/Shaders/particle_VS.glsl", "../Clumsy/src/Shaders/particle_FS.glsl");
		particleTexture = loadTextureFromFile("../Clumsy/src/models/flame.png", GL_TRUE);
		textShader = new Shader("../Clumsy/src/Shaders/text_VS.glsl", "../Clumsy/src/Shaders/text_FS.glsl");
		buttonShader = new Shader("../Clumsy/src/Shaders/button_VS.glsl", "../Clumsy/src/Shaders/button_FS.glsl");
		Effects = new PostProcessor(*m_Postprocessing, SCR_WIDTH, SCR_HEIGHT);
		shaderCube = new Shader("../Clumsy/src/Shaders/cubeMap_VS.glsl", "../Clumsy/src/Shaders/cubeMap_FS.glsl");
		shaderSkybox = new Shader("../Clumsy/src/Shaders/skybox_VS.glsl", "../Clumsy/src/Shaders/skybox_FS.glsl");
		
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		//float cubeVertices[] = {
		//	// positions          // normals
		//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,



		//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,



		//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,



		//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,



		//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,



		//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		//};
		//float skyboxVertices[] = {
		//	// positions          
		//	-1.0f,  1.0f, -1.0f,
		//	-1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f,  1.0f, -1.0f,
		//	-1.0f,  1.0f, -1.0f,

		//	-1.0f, -1.0f,  1.0f,
		//	-1.0f, -1.0f, -1.0f,
		//	-1.0f,  1.0f, -1.0f,
		//	-1.0f,  1.0f, -1.0f,
		//	-1.0f,  1.0f,  1.0f,
		//	-1.0f, -1.0f,  1.0f,

		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,

		//	-1.0f, -1.0f,  1.0f,
		//	-1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f, -1.0f,  1.0f,
		//	-1.0f, -1.0f,  1.0f,

		//	-1.0f,  1.0f, -1.0f,
		//	 1.0f,  1.0f, -1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	-1.0f,  1.0f,  1.0f,
		//	-1.0f,  1.0f, -1.0f,

		//	-1.0f, -1.0f, -1.0f,
		//	-1.0f, -1.0f,  1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	-1.0f, -1.0f,  1.0f,
		//	 1.0f, -1.0f,  1.0f
		//};

		//glGenVertexArrays(1, &cubeVAO);
		//glGenBuffers(1, &cubeVBO);
		//glBindVertexArray(cubeVAO);
		//glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		//glGenVertexArrays(1, &skyboxVAO);
		//glGenBuffers(1, &skyboxVBO);
		//glBindVertexArray(skyboxVAO);
		//glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		//glGenFramebuffers(1, &depthMapFBO);
		//// create depth texture
		//glGenTextures(1, &depthMap);
		//glBindTexture(GL_TEXTURE_2D, depthMap);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		//float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		//// attach depth texture as FBO's depth buffer
		//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		//glDrawBuffer(GL_NONE);
		//glReadBuffer(GL_NONE);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		m_Shader->use();
		m_Shader->setInt("diffuseTexture", 0);
		m_Shader->setInt("shadowMap", 1);
		debugDepthQuadShader->use();
		debugDepthQuadShader->setInt("depthMap", 0);

		particles = new ParticleGenerator( particleShader, particleTexture, 500);
		gui = new GUI();
		m_ButtonCameraOnPlayer = new Button(glm::vec2(-0.9f, 0.65f), " Center", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.15f, 0.08f));
		m_ButtonEndTurn = new Button(glm::vec2(-0.9f, 0.55f), "End Turn", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.15f, 0.08f));
		m_ButtonRestart = new Button(glm::vec2(-0.9f, 0.45f), " Restart", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.15f, 0.08f));
		m_StoreGUI = new StoreGUI();
		m_WarehouseGUI = new WarehouseGUI();

		//glEnable(GL_DEPTH_TEST);
		//glDepthMask(GL_TRUE);
		//glDepthFunc(GL_LESS);
		//glDepthRange(0.0f, 1.0f);


		//std::vector<std::string> faces
		//{
		//	("../Clumsy/src/models/skybox/right.jpg"),
		//	("../Clumsy/src/models/skybox/left.jpg"),
		//	("../Clumsy/src/models/skybox/top.jpg"),
		//	("../Clumsy/src/models/skybox/bottom.jpg"),
		//	("../Clumsy/src/models/skybox/front.jpg"),
		//	("../Clumsy/src/models/skybox/back.jpg"),
		//};
		//cubemapTexture = loadCubemap(faces);

		//shaderCube->use();
		//shaderCube->setInt("skybox", 0);


		//shaderSkybox->use();
		//shaderSkybox->setInt("skybox", 0);



	}

	TextureClass RenderEngine::loadTextureFromFile(const char* file, bool alpha)
	{
		// create texture object
		TextureClass texture;
		if (alpha)
		{
			texture.Internal_Format = GL_RGBA;
			texture.Image_Format = GL_RGBA;
		}
		// load image
		int width, height, nrChannels;
		unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
		// now generate texture
		texture.Generate(width, height, data);
		// and finally free image data
		stbi_image_free(data);
		return texture;
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

	void RenderEngine::setFrustum(glm::mat4 viewProjection)
	{
		if (pl.size() > 0) {
			pl.clear();
		}

		Plane left(glm::vec3(viewProjection[0][3] + viewProjection[0][0], viewProjection[1][3] + viewProjection[1][0],
			viewProjection[2][3] + viewProjection[2][0]), viewProjection[3][3] + viewProjection[3][0]);
		pl.push_back(left);

		Plane right(glm::vec3(viewProjection[0][3] - viewProjection[0][0], viewProjection[1][3] - viewProjection[1][0],
			viewProjection[2][3] - viewProjection[2][0]), viewProjection[3][3] - viewProjection[3][0]);
		pl.push_back(right);

		Plane top(glm::vec3(viewProjection[0][3] - viewProjection[0][1], viewProjection[1][3] - viewProjection[1][1],
			viewProjection[2][3] - viewProjection[2][1]), viewProjection[3][3] - viewProjection[3][1]);
		pl.push_back(top);

		Plane down(glm::vec3(viewProjection[0][3] + viewProjection[0][1], viewProjection[1][3] + viewProjection[1][1],
			viewProjection[2][3] + viewProjection[2][1]), viewProjection[3][3] + viewProjection[3][1]);
		pl.push_back(down);

		Plane near(glm::vec3(viewProjection[0][3] + viewProjection[0][2], viewProjection[1][2] + viewProjection[1][0],
			viewProjection[2][3] + viewProjection[2][2]), viewProjection[3][3] + viewProjection[3][2]);
		pl.push_back(near);

		Plane far(glm::vec3(viewProjection[0][3] - viewProjection[0][2], viewProjection[1][2] - viewProjection[1][0],
			viewProjection[2][3] - viewProjection[2][2]), viewProjection[3][3] - viewProjection[3][2]);
		pl.push_back(far);

		pl[0].SetNormal(glm::normalize(pl[0].GetNormal()));
		pl[1].SetNormal(glm::normalize(pl[1].GetNormal()));
		pl[2].SetNormal(glm::normalize(pl[2].GetNormal()));
		pl[3].SetNormal(glm::normalize(pl[3].GetNormal()));
		pl[4].SetNormal(glm::normalize(pl[4].GetNormal()));
		pl[5].SetNormal(glm::normalize(pl[5].GetNormal()));
	}

	bool RenderEngine::pointInPlane(Plane p, glm::vec3 point)
	{
		bool result;
		float distance = glm::dot(p.GetNormal(), point) + p.GetDistance();
		if (distance < 0) {
			result = true;
		}
		else
		{
			result = false;
		}
		return result;
	}

	bool RenderEngine::IsInFrustum(const Collider* aabb)
	{
		std::vector<glm::vec3> points; // p1, p2, p3, p4, p5, p6, p7, p8;

		glm::vec3 p;
		p = aabb->GetMinExtends();
		points.push_back(p);

		p = aabb->GetMaxExtends();
		points.push_back(p);

		p.x = points[1].x;
		p.y = points[0].y;
		p.z = points[0].z;
		points.push_back(p);

		p.x = points[1].x;
		p.y = points[1].y;
		p.z = points[0].z;
		points.push_back(p);

		p.x = points[0].x;
		p.y = points[1].y;
		p.z = points[0].z;
		points.push_back(p);

		p.x = points[0].x;
		p.y = points[0].y;
		p.z = points[1].z;
		points.push_back(p);

		p.x = points[0].x;
		p.y = points[1].y;
		p.z = points[1].z;
		points.push_back(p);

		p.x = points[1].x;
		p.y = points[0].y;
		p.z = points[1].z;
		points.push_back(p);

		for (int i = 0; i < points.size(); i++)
		{
			for (int j = 0; j < pl.size(); j++)
			{
				if (pointInPlane(pl[j], points[i]))
					return false;
			}
		}
		return true;
	}

	void RenderEngine::Render(GameObject object)
	{
		//glEnable(GL_DEPTH_TEST);


		m_Counter = 0;

		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;
		processInput(timestep.GetSeconds());

		// lighting info
		glm::vec3 lightPos(20.0f, 40.0f, -20.0f);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;

		float near_plane = 1.0f, far_plane = 15.0f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(glm::vec3(2.0f, 4.0f, -2.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;

		// render scene from light's point of view
		simpleDepthShader->use();
		simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

		/*glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		object.RenderAll(*simpleDepthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

		// reset viewport
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 2. render scene as normal using the generated depth/shadow map  
		//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Shader->use();
		projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = m_Camera->GetViewMatrix();
		m_Shader->setMat4("projection", projection);
		m_Shader->setMat4("view", view);
		// set light uniforms
		m_Shader->SetDirectionalLight(0.6, m_Camera->GetPosition(), lightPos, lightSpaceMatrix);
		

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, depthMap);

		if (isFrustumSet == false) {
			glm::mat4 comboMatrix = view * glm::transpose(projection);
			setFrustum(comboMatrix);
			isFrustumSet = true;
		}

		object.RenderAll(*m_Shader);
		//glm::mat4 projectionParticles = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
		//particleShader->use();
		//particleShader->SetInteger("sprite", 0, GL_TRUE);
		//particleShader->setMat4("projection", projectionParticles);
		//particles->Update(timestep.GetSeconds(), 2);
		//particles->Draw();

		//glEnable(GL_DEPTH_TEST);


		//shaderCube->use();
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.5f, 0.5f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.2f, 0.4f, 0.0f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 0.4f));
		//shaderCube->setMat4("model", model);
		//shaderCube->setMat4("view", view);
		//shaderCube->setMat4("projection", projection);
		//shaderCube->setVec3("cameraPos", m_Camera->GetPosition());

		//glBindVertexArray(cubeVAO);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);


		//glDepthMask(GL_FALSE);
		//glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		//shaderSkybox->use();
		//glm::mat4 model1 = glm::mat4(1.0f);
		//model1 = glm::rotate(model1, glm::radians(130.0f), glm::vec3(0.0f, 0.5f, 0.5f));
		//model1 = glm::rotate(model1, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, -0.5f));
		//model1 = glm::rotate(model1, glm::radians(20.0f), glm::vec3(0.2f, 0.4f, 0.6f));
		//view = glm::mat4(glm::mat3(m_Camera->GetViewMatrix())); // remove translation from the view matrix
		//shaderSkybox->setMat4("view", view);
		//shaderSkybox->setMat4("projection", projection);
		//shaderSkybox->setMat4("model", model1);
		//// skybox cube
		//glBindVertexArray(skyboxVAO);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);
		//glDepthFunc(GL_LESS); // set depth function back to default

		//glDepthMask(GL_TRUE);
		
	//	glDisable(GL_CULL_FACE);
	}

	void RenderEngine::RenderGUI()
	{
		glDisable(GL_DEPTH_TEST);

		glm::mat4 projectionGUI = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
		textShader->use();
		textShader->setMat4("projection", projectionGUI);

		if (!m_StoreGUI->IsEnabled() && !m_WarehouseGUI->IsEnabled())
		{
			buttonShader->use();
			m_ButtonCameraOnPlayer->Render(buttonShader);
			m_ButtonEndTurn->Render(buttonShader);
			m_ButtonRestart->Render(buttonShader);
						
			gui->RenderText(textShader, "Wood: ", 25.0f, SCR_HEIGHT - 100.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(textShader, "Actions: ", 25.0f, SCR_HEIGHT - 150.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(textShader, m_ButtonCameraOnPlayer->GetText(), 25.0f, SCR_HEIGHT - 200.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(textShader, m_ButtonEndTurn->GetText(), 25.0f, SCR_HEIGHT - 250.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(textShader, m_ButtonRestart->GetText(), 25.0f, SCR_HEIGHT - 300.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
		}

		m_StoreGUI->Render(buttonShader, textShader, SCR_WIDTH, SCR_HEIGHT);
		m_WarehouseGUI->Render(buttonShader, textShader, SCR_WIDTH, SCR_HEIGHT);
	}

	void RenderEngine::CleanUp()
	{
		m_Window->~Window();
	}

	void RenderEngine::processInput(float deltaTime)
	{
		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_GLFWWindow, true);

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_W) == GLFW_PRESS) {
			isFrustumSet = false;
			m_Camera->ProcessKeyboard(UP, deltaTime);
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_S) == GLFW_PRESS) {
			isFrustumSet = false;
			m_Camera->ProcessKeyboard(DOWN, deltaTime);
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_A) == GLFW_PRESS) {
			isFrustumSet = false;
			m_Camera->ProcessKeyboard(LEFT, deltaTime);
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_D) == GLFW_PRESS) {
			isFrustumSet = false;
			m_Camera->ProcessKeyboard(RIGHT, deltaTime);
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_R) == GLFW_PRESS) {
			isFrustumSet = false;
			m_Camera->ProcessKeyboard(FORWARD, deltaTime);
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_F) == GLFW_PRESS) {
			isFrustumSet = false;
			m_Camera->ProcessKeyboard(BACKWARD, deltaTime);
		}

	}

	/*unsigned int RenderEngine::loadCubemap(std::vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrComponents;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}*/

}