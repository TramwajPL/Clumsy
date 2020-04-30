#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\ext\matrix_transform.hpp>

#include "RenderEngine.h"
#include "Model.h"
#include "Camera.h"
#include "../Core/GameObject.h"
#include "../Core/EntityComponent.h"

namespace Clumsy {

	RenderEngine::RenderEngine(GLFWwindow* window, Window& window2) :
		m_Window(&window2),
		m_GLFWWindow(window)
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
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;

		CameraComponent camera(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));

		long lastTime = Clumsy::GetTime();
		double unprocessedTime = 0;
		Shader ourShader("../Clumsy/src/Shaders/model_loadingVS.glsl", "../Clumsy/src/Shaders/model_loadingFS.glsl");
		Model m1("../Clumsy/src/models/capsule.obj");


		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		float scale = 0.2f;
		Transform transform(pos, rot, scale);

		GameObject gameObject(transform);

		EntityComponent componentCapsuleModel(&m1);

		gameObject.AddComponent(&componentCapsuleModel);

		componentCapsuleModel.SetParent(gameObject);




		//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		// render loop
		// -----------
		while (!glfwWindowShouldClose(m_GLFWWindow))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			ourShader.use();

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			camera.OnUpdate(timestep);

			// view/projection transformations			
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = glm::lookAt(camera.GetCamera().GetTransform()->GetPos(),
			camera.GetCamera().GetTransform()->GetPos() + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			ourShader.setMat4("projection", projection);
			ourShader.setMat4("view", view);

			// render the loaded model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.3f, -1.8f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
			ourShader.setMat4("model", model);
			gameObject.GetModelComponent()->GetModel().Draw(ourShader);


			glfwSwapBuffers(m_GLFWWindow);
			glfwPollEvents();
		}

		glfwTerminate();


		CleanUp();
	}

	void RenderEngine::Render()
	{
		renderUtil.ClearScreen();
		renderUtil.InitGraphics();
		m_Window->SetIsCloseRequested(true);
	}

	void RenderEngine::CleanUp()
	{
		m_Window->~Window();
	}
}