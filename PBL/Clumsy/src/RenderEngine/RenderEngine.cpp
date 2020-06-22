#include "../pch.h"

#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>
#include <stb_image.h>

#include "Model.h"
#include "RenderEngine.h"
#include "TexturedRect.h"

#include "../GUI/GUI.h"
#include "../GUI/Button.h"
#include "../GUI/MenuGUI.h"
#include "../GUI/PokemonGUI.h"
#include "../GUI/StoreGUI.h"
#include "../GUI/WarehouseGUI.h"


#include "../GUI/CreditsGUI.h"
#include "../Game/Enemy.h"

#include "../Core/Game.h"
#include "../Core/Timestep.h"
#include "../Game/TurnSystem.h"
#include "../Core/GameObject.h"
#include "../Core/MousePicker.h"
#include "../PhysicsEngine/Aabb.h"
#include "../Core/EntityComponent.h"
#include "../Components/RenderModelComponent.h"
#include "ParticleSystem.h"
#include "../GUI/DestructionBar.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

//const unsigned int SCR_WIDTH = 1366;
//const unsigned int SCR_HEIGHT = 768;

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
		greenParticleTexture = loadTextureFromFile("../Clumsy/src/models/greenParticle.png", GL_TRUE);
		textShader = new Shader("../Clumsy/src/Shaders/text_VS.glsl", "../Clumsy/src/Shaders/text_FS.glsl");
		buttonShader = new Shader("../Clumsy/src/Shaders/button_VS.glsl", "../Clumsy/src/Shaders/button_FS.glsl");

		shaderCube = new Shader("../Clumsy/src/Shaders/cubeMap_VS.glsl", "../Clumsy/src/Shaders/cubeMap_FS.glsl");

		Effects = new PostProcessor(*m_Postprocessing, SCR_WIDTH, SCR_HEIGHT);
		shaderCube = new Shader("../Clumsy/src/Shaders/cubeMap_VS.glsl", "../Clumsy/src/Shaders/cubeMap_FS.glsl");
		
		mainMenuShader = new Shader("../Clumsy/src/Shaders/main_menu_VS.glsl", "../Clumsy/src/Shaders/main_menu_FS.glsl");

		//models
		playerModel = new Clumsy::Model();
		playerModel->loadModel("../Clumsy/src/models/man/model.dae");

		enemyModel = new Clumsy::Model();
		enemyModel->loadModel("../Clumsy/src/models/enemyModels/Idle/Idle.dae"); 

		m3 = new Model();
		m4 = new Model();
		m5 = new Model();
		m6 = new Model();
		m7 = new Model();
		mBurned = new Model();
		mShop = new Model();

		m3->loadModel("../Clumsy/src/models/hexes/groundEarth_base_color.obj");
		m4->loadModel("../Clumsy/src/models/hexes/Desert_ground_Albedo.obj");
		m5->loadModel("../Clumsy/src/models/hexes/Stone_Albedo.obj");
		m6->loadModel("../Clumsy/src/models/hexes/Water_Albedo.obj");
		m7->loadModel("../Clumsy/src/models/hexes/tree_Oliwiw.obj");
		mBurned->loadModel("../Clumsy/src/models/hexes/Burned_ground.obj");
		mShop->loadModel("../Clumsy/src/models/shop/shop.obj");

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		m_Shader->use();
		m_Shader->setInt("diffuseTexture", 0);
		m_Shader->setInt("shadowMap", 1);
		debugDepthQuadShader->use();
		debugDepthQuadShader->setInt("depthMap", 0);

		particleSystem = new ParticleSystem(particleShader, particleTexture);
		greenParticle = new ParticleSystem(particleShader, greenParticleTexture);

		gui = new GUI();
		m_ButtonCameraOnPlayer = new Button(glm::vec2(-0.88f, 0.65f), "Find Player", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.2f, 0.08f));
		m_ButtonEndTurn = new Button(glm::vec2(-0.88f, 0.55f), "End Turn", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.2f, 0.08f));
		m_ButtonRestart = new Button(glm::vec2(-0.88f, 0.45f), " Restart", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.2f, 0.08f));
		m_StoreGUI = new StoreGUI();
		m_WarehouseGUI = new WarehouseGUI();
		m_MenuGUI = new MenuGUI();
		m_CreditsGUI = new CreditsGUI();

		//m_PokemonGUI = new PokemonGUI();
	    m_TexturedRect = new TexturedRect("../Clumsy/src/models/tutek1.jpg", glm::vec3(0.9f, 0.9f, 0.0f), glm::vec3(0.9, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.9f, 0.0f));
		
		m_Instruction2 = new TexturedRect("../Clumsy/src/models/tutek2.jpg", glm::vec3(0.9f, 0.9f, 0.0f), glm::vec3(0.9, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.9f, 0.0f));
		m_Instruction3 = new TexturedRect("../Clumsy/src/models/tutek3.jpg", glm::vec3(0.9f, 0.9f, 0.0f), glm::vec3(0.9, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.9f, 0.0f));

		m_PokemonGUI = new PokemonGUI(buttonShader);
	   // m_TexturedRect = new TexturedRect("../Clumsy/src/models/tutek1.jpg", glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(-0.5f, 0.5f, 0.0f));
	    m_PokemonRect = new TexturedRect("../Clumsy/src/models/battle2.jpg", glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
	    m_PokemonEnemy = new TexturedRect("../Clumsy/src/models/ent.jpg", glm::vec3(0.7f, 0.8f, 0.0f), glm::vec3(0.7f, 0.4f, 0.0f), glm::vec3(0.5f, 0.4f, 0.0f), glm::vec3(0.5f, 0.8f, 0.0f));
	    m_PokemonPlayer = new TexturedRect("../Clumsy/src/models/lumberjack.jpg", glm::vec3(-0.6f, 0.4f, 0.0f), glm::vec3(-0.6f, 0.0f, 0.0f), glm::vec3(-0.8f, 0.0f, 0.0f), glm::vec3(-0.8f, 0.4f, 0.0f));

		background = new DestructionBar(glm::vec3(-0.5f, -0.82f, 0.5f), glm::vec3(0.14f, 0.52f, 0.25f), buttonShader);
		destructionBar = new DestructionBar(glm::vec3(-0.5f, -0.83f, 0.5f), glm::vec3(0.65f, 0.52f, 0.09f), buttonShader);

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
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_ALWAYS);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Counter = 0;

		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;
		processInput(timestep.GetSeconds());

		// lighting info
		glm::vec3 lightPos(20.0f, 40.0f, -20.0f);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;

		float near_plane = 100.1f, far_plane = 1050.0f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(glm::vec3(20.0f, 40.0f, -20.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;

		// render scene from light's point of view
		simpleDepthShader->use();
		simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT );
		object.RenderAll(*simpleDepthShader);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, Effects->DepthFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Effects->MSFBO);
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = m_Camera->GetViewMatrix();


		m_Shader->use();
		m_Shader->use();
		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = m_Camera->GetViewMatrix();
		m_Shader->setMat4("projection", projection);
		m_Shader->setMat4("view", view);
		// set light uniforms
		m_Shader->SetDirectionalLight(0.6, m_Camera->GetPosition(), lightPos, lightSpaceMatrix);


		if (isFrustumSet == false) {
			glm::mat4 comboMatrix = view * glm::transpose(projection);
			setFrustum(comboMatrix);
			isFrustumSet = true;
		}

		object.RenderAll(*m_Shader);
		
		for (int i = 0; i < m_Cubes.size(); i++)
		{
			m_Cubes[i]->Render(shaderCube);
		}

		if (isPlayed == true) {
			particleSystem->GenerateNewParticles(timestep.GetSeconds(), m_TreePosition);
			fireTime += timestep.GetSeconds();
			if (fireTime >= fireMaxTime)
			{
				isPlayed = false;
				fireTime = 0;
			}
		}
		particleSystem->Update(timestep.GetSeconds(), view, projection);
		particleSystem->Render(view, projection);

		if (enemySpawn == true && isPlayed == false) {
			for (int i = 0; i < m_TreeSpawnPosition.size(); i++)
			{
				greenParticle->GenerateNewParticles(timestep.GetSeconds(), m_TreeSpawnPosition[i]);
			}
			particleTime += timestep.GetSeconds();
			if (particleTime >= particleMaxTime)
			{
				enemySpawn = false;
				particleTime = 0;
			}
		}

		greenParticle->Update(timestep.GetSeconds(), view, projection);
		greenParticle->Render(view, projection); //?
	}

	void RenderEngine::RenderGUI()
	{
		glDisable(GL_CULL_FACE);
		buttonShader->use();
		background->Render(glm::vec3(m_XScaleBackground, 0.10f, 0.3f)); //zmieni� Y
		destructionBar->Render(glm::vec3(m_ScaleUp, 0.13f, 0.3f));
		glEnable(GL_CULL_FACE);

		glDisable(GL_DEPTH_TEST);

		glm::mat4 projectionGUI = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
		textShader->use();
		textShader->setMat4("projection", projectionGUI);
		
		mainMenuShader->use();
	
		if (m_ThirdInstruction)
		{
			if (m_FirstInstruction && m_SecondInstruction) {
				m_TexturedRect->Render(mainMenuShader);
			} else if (m_FirstInstruction == false && m_SecondInstruction == true) {
				m_Instruction2->Render(mainMenuShader);
			}
			else {
				m_Instruction3->Render(mainMenuShader);
			}
		}
		// fail info
		if (m_MoveTooFar)
		{
			gui->RenderText(textShader, "I can't go that far at once!", SCR_WIDTH / 2 - 200.0f, SCR_HEIGHT - 200.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		if (m_TooMuchWood)
		{
			gui->RenderText(textShader, "Not enough space for wood!", SCR_WIDTH / 2 - 225.0f, SCR_HEIGHT - 250.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		if (m_TileOccupied)
		{
			gui->RenderText(textShader, "Tile already occupied!", SCR_WIDTH / 2 - 185.0f, SCR_HEIGHT - 300.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
		}


		Player* player = dynamic_cast<Player*>(TurnSystem::GetInstance()->GetActivePlayer());
		if (player)
		{
			gui->RenderText(textShader, "Wood: " + std::to_string(player->GetWoodCount()) + " / " + std::to_string(player->GetMaxWood()), 
				25.0f, SCR_HEIGHT - 100.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(textShader, "Actions: " + std::to_string(player->GetAvailableActions()), 
				25.0f, SCR_HEIGHT - 150.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
		}

		if (!m_StoreGUI->IsEnabled() && !m_WarehouseGUI->IsEnabled())
		{
			buttonShader->use();
			m_ButtonCameraOnPlayer->Render(buttonShader);
			m_ButtonEndTurn->Render(buttonShader);
			m_ButtonRestart->Render(buttonShader);
			
			gui->RenderText(textShader, m_ButtonCameraOnPlayer->GetText(), 25.0f, SCR_HEIGHT - 200.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(textShader, m_ButtonEndTurn->GetText(), 25.0f, SCR_HEIGHT - 250.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(textShader, m_ButtonRestart->GetText(), 25.0f, SCR_HEIGHT - 300.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));

						
		}

		m_StoreGUI->Render(mainMenuShader ,buttonShader, textShader, SCR_WIDTH, SCR_HEIGHT);
		m_WarehouseGUI->Render(mainMenuShader ,buttonShader, textShader, SCR_WIDTH, SCR_HEIGHT);
		
	
	}

	void RenderEngine::RenderMainMenu()
	{
		glDisable(GL_DEPTH_TEST);

		glm::mat4 projectionGUI = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
		textShader->use();
		textShader->setMat4("projection", projectionGUI);
		//mainMenuShader->use();


		m_MenuGUI->Render(mainMenuShader, buttonShader, textShader, SCR_WIDTH, SCR_HEIGHT);
	}

	void RenderEngine::RenderCreditsGUI() {
		glDisable(GL_DEPTH_TEST);

		glm::mat4 projectionGUI = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
		textShader->use();
		textShader->setMat4("projection", projectionGUI);
		//mainMenuShader->use();


		m_CreditsGUI->Render(mainMenuShader, buttonShader, textShader, SCR_WIDTH, SCR_HEIGHT);
	
	}

	void RenderEngine::RenderPokemonGUI()
	{
		glDisable(GL_DEPTH_TEST);

		glm::mat4 projectionGUI = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
		textShader->use();
		textShader->setMat4("projection", projectionGUI);
		//mainMenuShader->use();

		m_PokemonRect->Render(mainMenuShader);
		m_PokemonPlayer->Render(mainMenuShader);
		m_PokemonEnemy->Render(mainMenuShader);
		m_PokemonGUI->Render(mainMenuShader, buttonShader, textShader, SCR_WIDTH, SCR_HEIGHT);
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

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_G) == GLFW_PRESS) {
			Effects->m_Grey = !Effects->m_Grey;
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_O) == GLFW_PRESS) {
			m_StoreGUI->SetEnabled(!m_StoreGUI->IsEnabled());
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_P) == GLFW_PRESS) {
			m_WarehouseGUI->SetEnabled(!m_WarehouseGUI->IsEnabled());
		}

	}

	unsigned int RenderEngine::loadCubemap(std::vector<std::string> faces)
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
	}

	void RenderEngine::UpdateCubes()
	{
		for (int i = 0; i < m_Cubes.size(); i++)
			m_Cubes[i]->Update();
	}

}