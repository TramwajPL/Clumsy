
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
		m_Shader = new Shader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");

		glEnable(GL_DEPTH_TEST);

	}

	//void RenderEngine::Start()
	//{
	//	if (isRunning)
	//		return;

	//	Run();
	//}

	//void RenderEngine::Stop()
	//{
	//	if (!isRunning)
	//		return;
	//	if (glfwWindowShouldClose(m_GLFWWindow))
	//		isRunning = false;
	//}
	//////////////////////////////////////////////////////////////////////////////////////////
	//TA FUNKCJA NIE BEDZIE POTRZEBNA ZGODNIE Z ZALOZENIAMI

<<<<<<< HEAD
		long lastTime = Clumsy::GetTime();
		double unprocessedTime = 0;
		Shader ourShader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");
		Model m1("../Clumsy/src/models/capsule.obj");


		glm::vec3 pos = glm::vec3(0.0f, 0.0f, -2.0f);
		glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		float scale = 0.1f;
		Transform transform(pos, rot, scale);
		Transform transform2(pos + glm::vec3(0.2f, 0.2f, 0.0f), rot, scale);

		GameObject gameObject(transform);
		//GameObject gameObject2(transform2);
=======
	//void RenderEngine::Run()
	//{
	//	isRunning = true;

	//	// settings
	//	/*const unsigned int SCR_WIDTH = 800;
	//	const unsigned int SCR_HEIGHT = 600;*/


	//	long lastTime = Clumsy::GetTime();
	//	double unprocessedTime = 0;
	///*	
	//	Shader ourShader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");
	//	Model m1("../Clumsy/src/models/capsule.obj");

>>>>>>> development

	//	glm::vec3 pos = glm::vec3(0.0f, 0.3f, -1.8f);
	//	glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	//	float scale = 0.1f;
	//	Transform transform(pos, rot, scale);
	//	Transform transform2(pos + glm::vec3(0.2f, 0.2f, 0.0f), rot, scale);

<<<<<<< HEAD
		gameObject.AddComponent(&componentCapsuleModel);
		//gameObject2.AddComponent(&componentCapsuleModel);
		
		componentCapsuleModel.SetParent(gameObject);
		//componentCapsuleModel.SetParent(gameObject2);
=======
	//	GameObject gameObject(transform);
	//	GameObject gameObject2(transform2);
>>>>>>> development

	//	EntityComponent componentCapsuleModel(&m1);

	//	gameObject.AddComponent(&componentCapsuleModel);
	//	gameObject2.AddComponent(&componentCapsuleModel);
	//	
	//	componentCapsuleModel.SetParent(gameObject);
	//	componentCapsuleModel.SetParent(gameObject2);*/


	//	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//	//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	//	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//	// render loop
	//	// -----------
	//	const unsigned int SCR_WIDTH = 800;
	//	const unsigned int SCR_HEIGHT = 600;

	//	Shader ourShader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");

	//	//TestGame game;
	//	//game.Init();

	//	while (!glfwWindowShouldClose(m_GLFWWindow))
	//	{
	//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//		glClear(GL_COLOR_BUFFER_BIT);

<<<<<<< HEAD
			processInput(timestep.GetSeconds());
			/*mp.Update();
			
			std::cout << "RAY: " << mp.GetCurrentRay().x << " , " << mp.GetCurrentRay().y << " , " << mp.GetCurrentRay().z << std::endl;*/
		
			// pass projection matrix to shader (note that in this case it could change every frame)
			glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			ourShader.setMat4("projection", projection);
=======
	//		//ourShader.use();
>>>>>>> development

	//		float time = (float)glfwGetTime();
	//		Timestep timestep = time - m_LastFrameTime;
	//		m_LastFrameTime = time;



	//		//camera.OnUpdate(timestep);

	//		processInput(timestep.GetSeconds());
	//	
	//		// pass projection matrix to shader (note that in this case it could change every frame)
	//		//glm::mat4 projection = glm::perspective(glm::radians(m_Camera->GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//		//ourShader.setMat4("projection", projection);

<<<<<<< HEAD
			//model1 = gameObject2.TranslateModelMatrix(model1);
			//model1 = gameObject2.ScaleModelMatrix(model1);

			ourShader.setMat4("model", model1);
			//gameObject2.GetModelComponent()->GetModel().Draw(ourShader);
=======
	//		//// camera/view transformation
	//		//glm::mat4 view = m_Camera->GetViewMatrix();
	//		//ourShader.setMat4("view", view);

	//		//// render the loaded model
	//		//glm::mat4 model = glm::mat4(1.0f);
	//		////model = glm::translate(model, glm::vec3(0.0f, 0.3f, -1.8f)); // translate it down so it's at the center of the scene
	//		////model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
	//		//model = gameObject.TranslateModelMatrix(model);
	//		//model = gameObject.ScaleModelMatrix(model);
>>>>>>> development

	//		//ourShader.setMat4("model", model);
	//		//gameObject.GetModelComponent()->GetModel().Draw(ourShader);


	//		//glm::mat4 model1 = glm::mat4(1.0f);

	//		//model1 = gameObject2.TranslateModelMatrix(model1);
	//		//model1 = gameObject2.ScaleModelMatrix(model1);

	//		//ourShader.setMat4("model", model1);
	//		//gameObject2.GetModelComponent()->GetModel().Draw(ourShader);


	//		//////////////////////////////////////////////////////////////////////////////////////
	//		//TESTING GAME TREE
	//
	//		//std::cout << game.getRoot().GetAllChildren().size() << std::endl;
	//		//Render(game.getRoot());
	//		//game.Render(this);

	//		glfwSwapBuffers(m_GLFWWindow);
	//		glfwPollEvents();
	//	}

	//	glfwTerminate();


	//	CleanUp();
	//}

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