
#include "../pch.h"

#include "CoreEngine.h"
#include "../EventSystem/EventSystem.h"
#include <stb_image.h>

namespace Clumsy
{
	void CoreEngine::Start()
	{	
		m_IsRunning = true;		

		float lastFrame = 0.0f;



		Shader* shaderCube = new Shader("../Clumsy/src/Shaders/cubeMap_VS.glsl", "../Clumsy/src/Shaders/cubeMap_FS.glsl");

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);


		float cubeVertices[] = {
			// Back face
-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // Bottom-left
 0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // bottom-right   
 0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // top-right             
 0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // top-right
-0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // top-left
-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // bottom-left               
// Front face
-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // bottom-left
 0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top-right
 0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // bottom-right       
 0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top-right
-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // bottom-left
-0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top-left       
// Left face
-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-right
-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-left
-0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // top-left      
-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-left
-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-right
-0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // bottom-right
// Right face
 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-left
 0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // top-right     
 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-right         
 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-right
 0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // bottom-left
 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-left
// Bottom face      
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, // top-right
 0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, // bottom-left
 0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, // top-left       
 0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, // bottom-left
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, // top-right
-0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, // bottom-right
// Top face
-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, // top-left
 0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, // top-right
 0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, // bottom-right                
 0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, // bottom-right
-0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, // bottom-left
-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f // top-left    
		};
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


		//for (int i = 0; i < 108; i++) {
		//	skyboxVertices[i] *= -1.0f;
		//}

		unsigned int cubeVAO, cubeVBO;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));




		std::vector<std::string> faces
		{
			("../Clumsy/src/models/skybox/right.jpg"),
			("../Clumsy/src/models/skybox/left.jpg"),
			("../Clumsy/src/models/skybox/top.jpg"),
			("../Clumsy/src/models/skybox/bottom.jpg"),
			("../Clumsy/src/models/skybox/front.jpg"),
			("../Clumsy/src/models/skybox/back.jpg"),
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
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.5f, 0.5f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.2f, 0.4f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.4f, 0.4f));
			shaderCube->setMat4("model", model);
			shaderCube->setMat4("view", RenderEngine::GetInstance()->getView());
			shaderCube->setMat4("projection", RenderEngine::GetInstance()->getProjection());
			shaderCube->setVec3("cameraPos", RenderEngine::GetInstance()->getCamera()->GetPosition());

			glBindVertexArray(cubeVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);




			glfwSwapBuffers(m_Window->GetGLFWWindow());
			glfwPollEvents();
		}
		glDeleteVertexArrays(1, &cubeVAO);
		//glDeleteVertexArrays(1, &skyboxVAO);
		glDeleteBuffers(1, &cubeVBO);
		//glDeleteBuffers(1, &skyboxVAO);
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