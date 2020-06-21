#pragma once

#include "Game.h"
#include "../RenderEngine/RenderEngine.h"

namespace Clumsy
{
	class CoreEngine
	{
	public:
		CoreEngine(float frameRate, Window* window, Game* game) :
			m_IsRunning(false),
			m_FrameTime(1.0f/frameRate),
			m_Window(window),
			m_Game(game)
		{
			m_Game->Init();
		}
		unsigned int loadCubemap(std::vector<std::string> faces);

		void Start();
		void Stop();

	private:
		bool m_IsRunning;				//Whether or not the engine is running
		float m_FrameTime = 0.0f;		//How long, in seconds, one frame should take
		Window* m_Window;				//Used to display the game
		Game* m_Game;					//The game itself. Stored as pointer so the user can pass in a derived class.


	};
}