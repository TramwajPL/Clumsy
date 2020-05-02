#pragma once

#include "Input.h"
#include "GameObject.h"

namespace Clumsy {

	class Game
	{
	public:
		void ProcessInput(const Input& input);
		//void Update();
		//void Render();
		void AddToScene(GameObject* child);
	private:
		GameObject m_Root;
	};
}