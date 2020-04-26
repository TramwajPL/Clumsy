#pragma once
#include "Input.h"

namespace Clumsy {

	class Game
	{
	public:
		void input();
		//void Update();
		//void Render();
	private:
		Input* m_Input;
	};
}