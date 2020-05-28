
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
		m_Max = glm::vec3(m_Corner.x + m_Width, m_Corner.y + m_Height, 0.01f);
		m_Collider = new Aabb(m_Min, m_Max);

		float vertices[] = {
		m_Max.x, m_Max.y, 0.0f,  // top right
		m_Max.x, m_Min.y, 0.0f,  // bottom right
		m_Min.x, m_Min.y, 0.0f,  // bottom left
		m_Min.x, m_Max.y, 0.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Button::Render(Shader* shader)
	{
		shader->use();
		shader->setVec3("buttonColor", m_Color);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Button::OnClick()
	{

	}
	
	void Button::CleanUp()
	{
		glDeleteVertexArrays(1, &VAO); 
		glDeleteBuffers(1, &VBO); 
		glDeleteBuffers(1, &EBO);
	}
}