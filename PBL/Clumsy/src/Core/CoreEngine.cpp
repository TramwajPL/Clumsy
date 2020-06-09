
#include "../pch.h"

#include "CoreEngine.h"
#include "../EventSystem/EventSystem.h"
#include <stb_image.h>
#include "../RenderEngine/Cube.h"

namespace Clumsy
{
	void CoreEngine::Start()
	{	
		m_IsRunning = true;		

		float lastFrame = 0.0f;



		Shader* shaderCube = new Shader("../Clumsy/src/Shaders/cubeMap_VS.glsl", "../Clumsy/src/Shaders/cubeMap_FS.glsl");

		Cube *cube = new Cube(glm::vec3(3.0f, 0.0f, -5.0f), glm::vec3(1.0f));
		Cube *cube2 = new Cube(glm::vec3(5.0f, 0.0f, 4.0f), glm::vec3(1.0f));

		std::vector<std::string> faces
		{
			("../Clumsy/src/models/skybox/bkg/lightblue/right.png"),
			("../Clumsy/src/models/skybox/bkg/lightblue/left.png"),
			("../Clumsy/src/models/skybox/bkg/lightblue/top.png"),
			("../Clumsy/src/models/skybox/bkg/lightblue/bot.png"),
			("../Clumsy/src/models/skybox/bkg/lightblue/front.png"),
			("../Clumsy/src/models/skybox/bkg/lightblue/back.png"),
		};
		unsigned int cubemapTexture = loadCubemap(faces);

		shaderCube->use();
		shaderCube->setInt("skybox", 0);



		while (!glfwWindowShouldClose(m_Window->GetGLFWWindow()))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// calculate delta time
			// --------------------
			float currentFrame = glfwGetTime();
			m_FrameTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			EventSystem::GetInstance()->ProcessEvents();

			m_Game->ProcessInput(m_Window->GetInput());

			m_Game->Update(m_FrameTime);


			glFrontFace(GL_CCW);

			m_Game->Render();


			glFrontFace(GL_CW);


			shaderCube->use();
			cube->Render(shaderCube, cubemapTexture);
			cube2->Render(shaderCube, cubemapTexture);
			glfwSwapBuffers(m_Window->GetGLFWWindow());
			glfwPollEvents();
		}

		glfwTerminate();
	}

	void CoreEngine::Stop()
	{
		m_IsRunning = false;
	}	

	unsigned int CoreEngine::loadCubemap(std::vector<std::string> faces)
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
}