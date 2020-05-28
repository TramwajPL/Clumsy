
#include "../pch.h"

#include <glad/glad.h>

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
			0.5f, 0.5f, 0.0f, // top right 
			-0.5f, 0.5f, 0.0f, // bottom right 
			-0.5f, -0.5f, 0.0f, // bottom left 
			-0.5f, -0.5f, 0.0f, // bottom left 
			0.5f, -0.5f, 0.0f, // top left
			0.5f, 0.5f, 0.0f, // top right 
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

	}

	void Button::Render(Shader* shader)
	{
		shader->use();
		glBindVertexArray(VAO); 
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