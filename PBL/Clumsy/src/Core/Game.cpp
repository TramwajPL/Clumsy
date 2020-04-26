#include "Game.h"
#include "Input.h"
#include "KeyCodes.h"
#include <iostream>

namespace Clumsy {
	
	void Game::Input()
	{
		if (Input::IsKeyPressed(CLUM_KEY_UP))
		{
			std::cout << "We've just pressed up !";
		}
	}
}