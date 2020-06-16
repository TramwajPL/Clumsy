
#include "../pch.h"

#include <glad/glad.h>

#include "StoreGUI.h"
#include "../EventSystem/EventSystem.h"

namespace Clumsy
{
	StoreGUI::StoreGUI()
	{
		BackgroundInit();

		// Buttons
		Button* exitButton = new Button(glm::vec2(0.36f, 0.33f), "X", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.07f, 0.1f));
		m_Buttons.push_back(exitButton);
		Button* b1 = new Button(glm::vec2(-0.01f, 0.2f), "Increase wood capacity (2 wood)", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b1);
		Button* b2 = new Button(glm::vec2(-0.01f, 0.05f), "Increase number of actions (2 wood)", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b2);
		Button* b3 = new Button(glm::vec2(-0.01f, -0.1f), "Enable scorching ground (5 wood)", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b3);
		Button* b4 = new Button(glm::vec2(-0.01f, -0.25f), "Hire a lumberjack (5 wood)", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b4);

		gui = new GUI();
	}

	void StoreGUI::Render(Shader* shaderButton, Shader* shaderText, int SCR_WIDTH, int SCR_HEIGHT)
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
			gui->RenderText(shaderText, m_Buttons[0]->GetText(), SCR_WIDTH - 625.0f, SCR_HEIGHT - 375.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			for (int i = 1; i < m_Buttons.size(); i++)
			{
				gui->RenderText(shaderText, m_Buttons[i]->GetText(), SCR_WIDTH - 1250, SCR_HEIGHT - 365 - 80 * i, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			}
		}
	}

	void StoreGUI::BackgroundInit()
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

	void StoreGUI::HandleButtonClick(float screenX, float screenY)
	{
		if (screenX > (m_Buttons[0]->GetCorner().x - (m_Buttons[0]->GetScale().x / 2)) && screenX < (m_Buttons[0]->GetCorner().x + (m_Buttons[0]->GetScale().x / 2))
			&& screenY < (m_Buttons[0]->GetCorner().y + m_Buttons[0]->GetScale().y) && screenY > m_Buttons[0]->GetCorner().y)
		{
			m_Buttons[0]->OnClick();
			m_Enabled = false;
			m_Player->IncrementActionCount();
		}
		// increase wood capacity
		else if (screenX > (m_Buttons[1]->GetCorner().x - (m_Buttons[1]->GetScale().x / 2)) && screenX < (m_Buttons[1]->GetCorner().x + (m_Buttons[1]->GetScale().x / 2))
			&& screenY < (m_Buttons[1]->GetCorner().y + m_Buttons[1]->GetScale().y) && screenY > m_Buttons[1]->GetCorner().y)
		{
			m_Buttons[1]->m_EffectTime = 0.2f;
			m_Buttons[1]->OnClick();
			if (m_Player->GetWoodCount() >= 2)
			{
				m_Player->IncrementMaxWood();
				m_Player->PayInWood(2);
				m_Buttons[1]->m_Ok = true;
			}
			else
			{
				m_Buttons[1]->m_Fail = true;
			}
		}
		// increase number of actions
		else if (screenX > (m_Buttons[2]->GetCorner().x - (m_Buttons[2]->GetScale().x / 2)) && screenX < (m_Buttons[2]->GetCorner().x + (m_Buttons[2]->GetScale().x / 2))
			&& screenY < (m_Buttons[2]->GetCorner().y + m_Buttons[2]->GetScale().y) && screenY > m_Buttons[2]->GetCorner().y)
		{
			m_Buttons[2]->m_EffectTime = 0.2f;
			m_Buttons[2]->OnClick();
			if (m_Player->GetWoodCount() >= 2)
			{
				m_Player->IncrementMaxActions();
				m_Player->PayInWood(2);
				m_Buttons[2]->m_Ok = true;
			}
			else
			{
				m_Buttons[2]->m_Fail = true;
			}
		}
		// enable scorching ground
		else if (screenX > (m_Buttons[3]->GetCorner().x - (m_Buttons[3]->GetScale().x / 2)) && screenX < (m_Buttons[3]->GetCorner().x + (m_Buttons[3]->GetScale().x / 2))
			&& screenY < (m_Buttons[3]->GetCorner().y + m_Buttons[3]->GetScale().y) && screenY > m_Buttons[3]->GetCorner().y)
		{
			m_Buttons[3]->m_EffectTime = 0.2f;
			m_Buttons[3]->OnClick();
			if (m_Player->GetWoodCount() >= 5)
			{
				// TODO wypalanko
				m_Player->PayInWood(5);
				m_Player->enableBurn();
				m_Buttons[3]->m_Ok = true;
			}
			else
			{
				m_Buttons[3]->m_Fail = true;
			}
		}
		// hire a lumberjack
		else if (screenX > (m_Buttons[4]->GetCorner().x - (m_Buttons[4]->GetScale().x / 2)) && screenX < (m_Buttons[4]->GetCorner().x + (m_Buttons[4]->GetScale().x / 2))
			&& screenY < (m_Buttons[4]->GetCorner().y + m_Buttons[4]->GetScale().y) && screenY > m_Buttons[4]->GetCorner().y)
		{
			m_Buttons[4]->m_EffectTime = 0.2f;
			m_Buttons[4]->OnClick();
			if (m_Player->GetWoodCount() >= 5)
			{
				m_Player->PayInWood(5);
				EventSystem::GetInstance()->SendEvent("hire");
				m_Buttons[4]->m_Ok = true;
			}
			else
			{
				m_Buttons[4]->m_Fail = true;
			}
		}
	}

	void StoreGUI::Update(float deltaTime)
	{
		for (int i = 1; i < m_Buttons.size(); i++)
		{
			m_Buttons[i]->Update(deltaTime);
		}
	}
}