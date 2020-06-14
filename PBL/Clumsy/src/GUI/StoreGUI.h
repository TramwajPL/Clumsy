#pragma once

#include "GUI.h"
#include "Button.h"

#include "../Game/Player.h"

namespace Clumsy
{
	class StoreGUI
	{
	public:
		StoreGUI();
		~StoreGUI();
		void Render(Shader* shader, Shader* shaderText, int SCR_WIDTH, int SCR_HEIGHT);
		void BackgroundInit();
		void SetActiveStore(GameObject* store) { m_Store = store; }
		void SetActivePlayer(Player* player) { m_Player = player; }
		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool doopy) { m_Enabled = doopy; }

		void HandleButtonClick(float screenX, float screenY);

	private:
		std::vector<Button*> m_Buttons;
		GUI* gui;
		unsigned int VBO, VAO;
		bool m_Enabled = false;

		GameObject* m_Store;
		Player* m_Player;
	};
}
