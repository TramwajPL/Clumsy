#pragma once

#include "GUI.h"
#include "Button.h"
#include "glfw3.h"
#include <vector>

namespace Clumsy {
	class PokemonGUI {
	public:
		enum BattleState { START, PLAYERTURN, ENEMYTURN, WON, LOST };

		PokemonGUI();
		~PokemonGUI();

		void Render(Shader* shader, Shader* shaderButton, Shader* shaderText, int SCR_WIDTH, int SCR_HEIGHT);
		void BackgroundInit();

		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool doopy) { m_Enabled = doopy; }

		void HandleButtonClick(float screenX, float screenY);
		void HandleBattle();

		std::string m_textString;
		bool m_BattleCommences = true;
	private:
		bool m_AttackButtonClickable = false;
		bool m_HealButtonClickable = false;
		int m_PlayerHP = 100, m_EnemyHp = 100, m_AttackValue = 50, m_HealValue = 50, m_EnemyAttackValue = 10;
		int m_SCRWIDTH;
		int m_SCRHEIGHT;
		Shader* m_Shader;
		BattleState m_BattleState = START;
		std::vector<Button*> m_Buttons;
		GUI* gui;
		unsigned int VBO, VAO, EBO;
		int width, height, nrChannels;
		unsigned int texture;
		bool m_Enabled = true;
	};
}