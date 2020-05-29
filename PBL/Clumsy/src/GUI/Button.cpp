
#include "../pch.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>
#include "Button.h"

namespace Clumsy
{

	Button::Button(glm::vec2 corner, float height, float width, std::string text, glm::vec3 color) :
		m_Corner(corner),
		m_Height(height),
		m_Width(width),
		m_Text(text),
		m_Color(color)
	{
		m_Min = glm::vec3(m_Corner.x, m_Corner.y, 0.0f);
		m_Max = glm::vec3(m_Corner.x + m_Width, m_Corner.y + m_Height, 10.01f);
		m_Collider = new Aabb(m_Min, m_Max);

		//float vertices[] = {
		//m_Max.x, m_Max.y, 0.0f,  // top right
		//m_Max.x, m_Min.y, 0.0f,  // bottom right
		//m_Min.x, m_Min.y, 0.0f,  // bottom left
		////m_Min.x, m_Min.y, 0.0f,  // bottom left
		////m_Min.x, m_Max.y, 0.0f,   // top left 
		////m_Max.x, m_Max.y, 0.0f,  // top right
		//};
		//
		float vertices[] = { 
			0.06f, 0.06f, 0.0f,  // top right 
			-0.06f, 0.06f, 0.0f,// bottom right 
			-0.06f, -0.06f, 0.0f, // bottom left 
			-0.06f, -0.06f, 0.0f, // bottom left 
			0.06f, -0.06f, 0.0f,  // top left //really: bootm right
			0.06f, 0.06f, 0.0f,// top right 
		};
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		/*glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);*/

		/*unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int widthT, heightT, nrChannels;
		unsigned char* data = stbi_load("../Clumsy/src/models/capsule0.jpg", &widthT, &heightT, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);*/

	}

	void Button::Render(Shader* shader)
	{
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture);
		shader->use();
		glBindVertexArray(VAO); 
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_Corner,0.0f));
		shader->setMat4("model",model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Button::OnClick()
	{
		std::cout << "Center Button clicked " << std::endl;
	}
	
	void Button::CleanUp()
	{
		glDeleteVertexArrays(1, &VAO); 
		glDeleteBuffers(1, &VBO); 
	}
}