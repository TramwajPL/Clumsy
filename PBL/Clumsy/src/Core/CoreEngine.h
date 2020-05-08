#pragma once

#include "Game.h"
#include "../RenderEngine/RenderEngine.h"
#include "../PhysicsEngine/PhysicsEngine.h"

namespace Clumsy
{
	class CoreEngine
	{
	public:
		CoreEngine(float frameRate, Window* window, RenderEngine* renderEngine, Game* game, PhysicsEngine* physicsEngine) :
			m_IsRunning(false),
			m_FrameTime(1.0f/frameRate),
			m_Window(window),
			m_RenderEngine(renderEngine),
			m_Game(game) ,
			m_PhysicsEngine(physicsEngine)
		{
			m_Game->Init();
		
		}

		void Start();
		void Stop();

		inline RenderEngine* GetRenderEngine() { return m_RenderEngine; }

	private:
		bool m_IsRunning;				//Whether or not the engine is running
		float m_FrameTime;				//How long, in seconds, one frame should take
		Window* m_Window;				//Used to display the game
		RenderEngine* m_RenderEngine;	//Used to render the game. Stored as pointer so the user can pass in a derived class.
		PhysicsEngine* m_PhysicsEngine;
		Game* m_Game;					//The game itself. Stored as pointer so the user can pass in a derived class.
	};
}