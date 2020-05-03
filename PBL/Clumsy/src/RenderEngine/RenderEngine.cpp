
#include "../pch.h"
#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\ext\matrix_transform.hpp>

#include "Model.h"
#include "RenderEngine.h"
#include "../Core/Timestep.h"
#include "../Core/GameObject.h"
#include "../Core/EntityComponent.h"
#include "../Core/Game.h"
#include "../Components/RenderModelComponent.h"

namespace Clumsy {
	class TestGame : public Game {
	public:
		virtual void Init() {
			glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
			float scale = 1.0f;
			Transform transform(pos, rot, scale);

			Model m1("../Clumsy/src/models/capsule.obj");

			AddToScene((new GameObject(transform))->AddComponent(new RenderModelComponent(m1)));
		}
	};

	RenderEngine::RenderEngine(GLFWwindow* window, Window* window2, Camera* camera) :
		m_Window(window2),
		m_GLFWWindow(window),
		m_Camera(camera)
	{
		isRunning = false;
	}

	void RenderEngine::Start()
	{
		if (isRunning)
			return;

		Run();
	}

	void RenderEngine::Stop()
	{
		if (!isRunning)
			return;
		if (glfwWindowShouldClose(m_GLFWWindow))
			isRunning = false;
	}

	void RenderEngine::Run()
	{
		isRunning = true;

		// settings
		/*const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;*/


		long lastTime = Clumsy::GetTime();
		double unprocessedTime = 0;
	/*	
		Shader ourShader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");
		Model m1("../Clumsy/src/models/capsule.obj");


		glm::vec3 pos = glm::vec3(0.0f, 0.3f, -1.8f);
		glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		float scale = 0.1f;
		Transform transform(pos, rot, scale);
		Transform transform2(pos + glm::vec3(0.2f, 0.2f, 0.0f), rot, scale);

		GameObject gameObject(transform);
		GameObject gameObject2(transform2);

		EntityComponent componentCapsuleModel(&m1);

		gameObject.AddComponent(&componentCapsuleModel);
		gameObject2.AddComponent(&componentCapsuleModel);
		
		componentCapsuleModel.SetParent(gameObject);
		componentCapsuleModel.SetParent(gameObject2);*/


		//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		// render loop
		// -----------
		while (!glfwWindowShouldClose(m_GLFWWindow))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//ourShader.use();

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;



			//camera.OnUpdate(timestep);

			processInput(timestep.GetSeconds());
		
			// pass projection matrix to shader (note that in this case it could change every frame)
			//glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			//ourShader.setMat4("projection", projection);

			//// camera/view transformation
			//glm::mat4 view = m_Camera->GetViewMatrix();
			//ourShader.setMat4("view", view);

			//// render the loaded model
			//glm::mat4 model = glm::mat4(1.0f);
			////model = glm::translate(model, glm::vec3(0.0f, 0.3f, -1.8f)); // translate it down so it's at the center of the scene
			////model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
			//model = gameObject.TranslateModelMatrix(model);
			//model = gameObject.ScaleModelMatrix(model);

			//ourShader.setMat4("model", model);
			//gameObject.GetModelComponent()->GetModel().Draw(ourShader);


			//glm::mat4 model1 = glm::mat4(1.0f);

			//model1 = gameObject2.TranslateModelMatrix(model1);
			//model1 = gameObject2.ScaleModelMatrix(model1);

			//ourShader.setMat4("model", model1);
			//gameObject2.GetModelComponent()->GetModel().Draw(ourShader);


			//////////////////////////////////////////////////////////////////////////////////////
			//TESTING GAME TREE
			TestGame game;
			game.Init();
			Render(game.getRoot());


			glfwSwapBuffers(m_GLFWWindow);
			glfwPollEvents();
		}

		glfwTerminate();


		CleanUp();
	}

	void RenderEngine::Render(GameObject object)
	{
		//renderUtil.ClearScreen();
		//renderUtil.InitGraphics();
		//m_Window->SetIsCloseRequested(true);

		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;


		Shader ourShader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = m_Camera->GetViewMatrix();
		ourShader.setMat4("view", view);


		object.RenderAll(ourShader);//  <--- tutaj ma sie renderowac
		//TODO: renderowanie po drzewie calym
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