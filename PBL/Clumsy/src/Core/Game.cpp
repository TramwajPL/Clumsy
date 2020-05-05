
#include "../pch.h"
#include "Game.h"

namespace Clumsy {
	//Input* Input::s_Instance = nullptr;

	//void Game::ProcessInput(const Input& input)
	//{
		/*if (m_Input->GetKeyDown(Input::KEY_UP))
		{
			std::cout << "WE PRESSED UP!";
		}*/
	//}
	
	void Game::Render(RenderEngine* renderingEngine)
	{
		renderingEngine->Render(m_Root); 
	}

	void Game::Update()
	{
		m_Root.UpdateAll();
	}

	void Game::AddToScene(GameObject* child)
	{
		m_Root.AddChild(child);
	}

	void Game::ProcessInput(int input) {
		m_Root.ProcessInputAll(input);
	}
}