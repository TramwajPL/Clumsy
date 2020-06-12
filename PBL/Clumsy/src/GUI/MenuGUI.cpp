
#include "../pch.h"

#include <glad/glad.h>

#include "MenuGUI.h"

namespace Clumsy
{
	MenuGUI::MenuGUI()
	{
		BackgroundInit();

		 //Buttons
		//Button* exitButton = new Button(glm::vec2(0.36f, 0.33f), "X", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.07f, 0.1f));
		//m_Buttons.push_back(exitButton);
		Button* b1 = new Button(glm::vec2(-0.01f, 0.2f), "PLAY", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b1);
		Button* b2 = new Button(glm::vec2(-0.01f, 0.05f), "EXIT", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b2);
		//Button* b3 = new Button(glm::vec2(-0.01f, -0.1f), "Enable scorching ground (5 wood)", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		//m_Buttons.push_back(b3);
		//Button* b4 = new Button(glm::vec2(-0.01f, -0.25f), "Hire a lumberjack (5 wood)", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		//m_Buttons.push_back(b4);

		gui = new GUI();
	}

	void MenuGUI::Render(Shader* shaderButton, Shader* shaderText, int SCR_WIDTH, int SCR_HEIGHT)
	{
		if (m_Enabled)
		{
			// Render background
			shaderButton->use();
			glBindVertexArray(VAO);
			glm::mat4 model = glm::mat4(1.0f);
			shaderButton->setMat4("model", model);
			shaderButton->setVec3("Color", glm::vec3(0.0f, 0.9f, 0.9f));
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Render buttons
			for (int i = 0; i < m_Buttons.size(); i++)
			{
				m_Buttons[i]->Render(shaderButton);
			}

			// Render text
			//gui->RenderText(shaderText, m_Buttons[0]->GetText(), SCR_WIDTH - 625.0f, SCR_HEIGHT - 375.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			for (int i = 0; i < m_Buttons.size(); i++)
			{
				gui->RenderText(shaderText, m_Buttons[i]->GetText(), SCR_WIDTH - 1250, SCR_HEIGHT - 445 - 80 * i, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			}
		}
	}

	void MenuGUI::BackgroundInit()
	{
		float vertices[] =
		{
			1.0f, 1.0f, 0.0f,  // top right 
			-1.0f, 1.0f, 0.0f, // bottom right 
			-1.0f, -1.0f, 0.0f, // bottom left 
			-1.0f, -1.0f, 0.0f, // bottom left 
			1.0f, -1.0f, 0.0f,  // top left //really: bootm right
			1.0f, 1.0f, 0.0f, // top right 
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

	void MenuGUI::HandleButtonClick(float screenX, float screenY, GLFWwindow* glfwWindow)
	{
		if (screenX > (m_Buttons[0]->GetCorner().x - (m_Buttons[0]->GetScale().x / 2)) && screenX < (m_Buttons[0]->GetCorner().x + (m_Buttons[0]->GetScale().x / 2))
			&& screenY < (m_Buttons[0]->GetCorner().y + m_Buttons[0]->GetScale().y) && screenY > m_Buttons[0]->GetCorner().y)
		{
			m_Buttons[0]->OnClick();
			m_Enabled = false;
		}
		else if (screenX > (m_Buttons[1]->GetCorner().x - (m_Buttons[1]->GetScale().x / 2)) && screenX < (m_Buttons[1]->GetCorner().x + (m_Buttons[1]->GetScale().x / 2))
			&& screenY < (m_Buttons[1]->GetCorner().y + m_Buttons[1]->GetScale().y) && screenY > m_Buttons[1]->GetCorner().y)
		{
			m_Enabled = false;
			m_Buttons[1]->OnClick();
		}
		else if (screenX > (m_Buttons[2]->GetCorner().x - (m_Buttons[2]->GetScale().x / 2)) && screenX < (m_Buttons[2]->GetCorner().x + (m_Buttons[2]->GetScale().x / 2))
			&& screenY < (m_Buttons[2]->GetCorner().y + m_Buttons[2]->GetScale().y) && screenY > m_Buttons[2]->GetCorner().y)
		{
			m_Buttons[2]->OnClick();
			glfwSetWindowShouldClose(glfwWindow, true);
		}
		//else if (screenX > (m_Buttons[3]->GetCorner().x - (m_Buttons[3]->GetScale().x / 2)) && screenX < (m_Buttons[3]->GetCorner().x + (m_Buttons[3]->GetScale().x / 2))
		//	&& screenY < (m_Buttons[3]->GetCorner().y + m_Buttons[3]->GetScale().y) && screenY > m_Buttons[3]->GetCorner().y)
		//{
		//	m_Buttons[3]->OnClick();
		//}
		//else if (screenX > (m_Buttons[4]->GetCorner().x - (m_Buttons[4]->GetScale().x / 2)) && screenX < (m_Buttons[4]->GetCorner().x + (m_Buttons[4]->GetScale().x / 2))
		//	&& screenY < (m_Buttons[4]->GetCorner().y + m_Buttons[4]->GetScale().y) && screenY > m_Buttons[4]->GetCorner().y)
		//{
		//	m_Buttons[4]->OnClick();
		//}
	}
}