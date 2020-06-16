#include "../pch.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "PokemonGUI.h"

namespace Clumsy {
	PokemonGUI::PokemonGUI()
	{
		BackgroundInit();

		//Buttons
		Button* b1 = new Button(glm::vec2(-0.01f, 0.2f), "Attack", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b1);
		Button* b2 = new Button(glm::vec2(-0.01f, 0.05f), "Heal", glm::vec3(0.16f, 0.03f, 0.29f), glm::vec2(0.7f, 0.1f));
		m_Buttons.push_back(b2);

		gui = new GUI();
	}

	void PokemonGUI::Render(Shader* shader, Shader* shaderButton, Shader* shaderText, int SCR_WIDTH, int SCR_HEIGHT)
	{
		m_Shader = shader;
		m_SCRWIDTH = SCR_WIDTH;
		m_SCRHEIGHT = SCR_HEIGHT;
		if (m_Enabled)
		{
			glEnable(GL_TEXTURE_2D);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// bind Texture
			glBindTexture(GL_TEXTURE_2D, texture);

			// render container
			shader->use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			// Render buttons
			for (int i = 0; i < m_Buttons.size(); i++)
			{
				m_Buttons[i]->Render(shaderButton);
			}

			// Render text
			for (int i = 0; i < m_Buttons.size(); i++)
			{
				gui->RenderText(shader, m_Buttons[i]->GetText(), m_SCRWIDTH - 1250, m_SCRHEIGHT - 445 - 80 * i, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
			}
		}
	}

	void PokemonGUI::BackgroundInit()
	{
		float vertices[] = {
			// positions          // colors           // texture coords
			 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);


		// load and create a texture 
		// -------------------------
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		/*unsigned char* data = stbi_load(std::string("../Clumsy/src/models/container.jpg").c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			std::cout << "Ladowana tekstura" << std::endl;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);*/
	}

	void PokemonGUI::HandleButtonClick(float screenX, float screenY, GLFWwindow* glfwWindow)
	{
		if (screenX > (m_Buttons[0]->GetCorner().x - (m_Buttons[0]->GetScale().x / 2)) && screenX < (m_Buttons[0]->GetCorner().x + (m_Buttons[0]->GetScale().x / 2))
			&& screenY < (m_Buttons[0]->GetCorner().y + m_Buttons[0]->GetScale().y) && screenY > m_Buttons[0]->GetCorner().y)
		{
			m_EnemyHp - m_AttackValue;
			if (m_EnemyHp <= 0)
				m_BattleState = WON;
			m_BattleState = ENEMYTURN;
			m_Buttons[0]->OnClick();
		}
		else if (screenX > (m_Buttons[1]->GetCorner().x - (m_Buttons[1]->GetScale().x / 2)) && screenX < (m_Buttons[1]->GetCorner().x + (m_Buttons[1]->GetScale().x / 2))
			&& screenY < (m_Buttons[1]->GetCorner().y + m_Buttons[1]->GetScale().y) && screenY > m_Buttons[1]->GetCorner().y)
		{
			m_PlayerHP + m_HealValue;
			if (m_PlayerHP > 100)
				m_PlayerHP = 100;
			m_BattleState = ENEMYTURN;
			m_Buttons[1]->OnClick();
		}
	}

	void PokemonGUI::HandleBattle(float screenX, float screenY, GLFWwindow* glfwWindow)
	{
		while (m_BattleCommences) 
		{
			if (m_BattleState == START) 
			{
				gui->RenderText(m_Shader, "Watch out! An enemy approaches: ", m_SCRWIDTH - 950.0f, m_SCRHEIGHT - 550.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
				m_BattleState = PLAYERTURN;
			}

			if (m_BattleState == PLAYERTURN) 
			{
				HandleButtonClick(screenX, screenY, glfwWindow);
			}

			if (m_BattleState == ENEMYTURN) 
			{
				m_PlayerHP - m_EnemyAttackValue;
				if (m_PlayerHP <= 0) 
				{
					m_BattleState = LOST;
				}
			}

			if (m_BattleState == LOST) 
			{
				m_BattleCommences = false;
			}

			if (m_BattleState == WON)
			{
				m_BattleCommences = false;
			}
		}
	}
}