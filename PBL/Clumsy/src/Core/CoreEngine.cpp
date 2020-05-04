
#include "../pch.h"

#include "CoreEngine.h"
#include <stb_image.h>

namespace Clumsy
{
	void CoreEngine::Start()
	{
	/*	if (m_IsRunning)
		{
			return;
		}

		m_IsRunning = true;



		while (m_IsRunning)
		{
			m_Game->Render(m_RenderEngine);

			glfwSwapBuffers(m_Window->GetGLFWWindow());
			glfwPollEvents();
		}*/
		///////////////////
		m_IsRunning = true;
		//Shader testAmbientShader("../Clumsy/src/Shaders/phongVS.glsl","../Clumsy/src/Shaders/phongFS.glsl");

		//// set up vertex data (and buffer(s)) and configure vertex attributes
		//float vertices[] = {
		//	-0.5f, -0.5f, 0.0f, // left  
		//	 0.5f, -0.5f, 0.0f, // right 
		//	 0.0f,  0.5f, 0.0f  // top   
		//};

		//unsigned int VBO, VAO;
		//glGenVertexArrays(1, &VAO);
		//glGenBuffers(1, &VBO);
		//glBindVertexArray(VAO);

		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glBindVertexArray(0);

		//unsigned int texture1;
		//// texture 1
		//// ---------
		//glGenTextures(1, &texture1);
		//glBindTexture(GL_TEXTURE_2D, texture1);
		//// set the texture wrapping parameters
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//// set texture filtering parameters
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//// load image, create texture and generate mipmaps
		//int width, height, nrChannels;
		//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		//unsigned char* data = stbi_load("../Clumsy/src/models/test.png", &width, &height, &nrChannels, 0);
		//if (data)
		//{
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//	glGenerateMipmap(GL_TEXTURE_2D);
		//}
		//else
		//{
		//	std::cout << "Failed to load texture" << std::endl;
		//}
		//stbi_image_free(data);
		//testAmbientShader.use();
		//testAmbientShader.setInt("texture1", 0);

		while (!glfwWindowShouldClose(m_Window->GetGLFWWindow()))
		{
			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//// bind textures on corresponding texture units
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, texture1);

			//glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
			//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

			//testAmbientShader.use();
			//// get matrix's uniform location and set matrix
			//testAmbientShader.setMat4("transform",transform);
			//testAmbientShader.setVec3("baseColor", 1.0f, 1.0f, 1.0);
			//testAmbientShader.setVec3("ambientLight", 0.2f, 0.2f, 0.2f);

			//glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 3);


			m_Game->Render(m_RenderEngine);

			glfwSwapBuffers(m_Window->GetGLFWWindow());
			glfwPollEvents();
		}

		glfwTerminate();

	}

	void CoreEngine::Stop()
	{
		m_IsRunning = false;
	}
}