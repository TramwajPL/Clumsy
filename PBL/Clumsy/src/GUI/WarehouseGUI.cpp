
#include "../pch.h"

#include <glad/glad.h>

#include "WarehouseGUI.h"
#include "../RenderEngine/Shader.h"

namespace Clumsy
{
	WarehouseGUI::WarehouseGUI()
	{
		BackgroundInit();

		// Buttons
		Button* exitButton = new Button(glm::vec2(0.36f, 0.33f), "X", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.07f, 0.1f));
		m_Buttons.push_back(exitButton);
		Button* storeWoodButton = new Button(glm::vec2(-0.27f, 0.1f), "Store", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.19f, 0.1f));
		m_Buttons.push_back(storeWoodButton);
		Button* withdrawWoodButton = new Button(glm::vec2(-0.27f, -0.09f), "Withdraw", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.19f, 0.1f));
		m_Buttons.push_back(withdrawWoodButton);

		gui = new GUI();
	}

	void WarehouseGUI::Render(Shader* shaderButton, Shader* shaderText, int SCR_WIDTH, int SCR_HEIGHT)
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
			gui->RenderText(shaderText, "Wood stored: ", SCR_WIDTH - 950.0f, SCR_HEIGHT - 550.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			gui->RenderText(shaderText, m_Buttons[0]->GetText(), SCR_WIDTH - 625.0f, SCR_HEIGHT - 375.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			for (int i = 1; i < m_Buttons.size(); i++)
			{
				gui->RenderText(shaderText, m_Buttons[i]->GetText(), SCR_WIDTH - 1300, SCR_HEIGHT - 400 - 100 * i, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			}
		}
	}

	void WarehouseGUI::BackgroundInit()
	{
		float vertices[] =
		{
			0.4f, 0.4f, 0.0f,  // top right 
			-0.4f, 0.4f, 0.0f, // bottom right 
			-0.4f, -0.4f, 0.0f, // bottom left 
			-0.4f, -0.4f, 0.0f, // bottom left 
			0.4f, -0.4f, 0.0f,  // top left //really: bootm right
			0.4f, 0.4f, 0.0f, // top right 
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

	void WarehouseGUI::HandleButtonClick(float screenX, float screenY)
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
			m_Buttons[1]->OnClick();
		}
		else if (screenX > (m_Buttons[2]->GetCorner().x - (m_Buttons[2]->GetScale().x / 2)) && screenX < (m_Buttons[2]->GetCorner().x + (m_Buttons[2]->GetScale().x / 2))
			&& screenY < (m_Buttons[2]->GetCorner().y + m_Buttons[2]->GetScale().y) && screenY > m_Buttons[2]->GetCorner().y)
		{
			m_Buttons[2]->OnClick();
		}
	}
}