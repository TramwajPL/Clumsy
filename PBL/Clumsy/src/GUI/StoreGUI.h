#pragma once

#include "GUI.h"
#include "Button.h"

namespace Clumsy
{
	class StoreGUI
	{
	public:
		StoreGUI();
		~StoreGUI();
		void Render(Shader* shader, Shader* shaderText, int SCR_WIDTH, int SCR_HEIGHT);
		void BackgroundInit();

		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool doopy) { m_Enabled = doopy; }

	private:
		std::vector<Button*> m_Buttons;
		GUI* gui;
		unsigned int VBO, VAO;
		bool m_Enabled = false;
	};
}
