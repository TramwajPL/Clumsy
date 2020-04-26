#include "Game.h"

#include "KeyCodes.h"
#include <iostream>

namespace Clumsy {
	//Input* Input::s_Instance = nullptr;

	void Game::input()
	{
		if (m_Input->getKeytest(Input::KEY_UP))
		{
			std::cout << "WE PRESSED UP!";
		}
	}
}