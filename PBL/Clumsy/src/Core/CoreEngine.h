#pragma once

#include "Game.h"
#include "../RenderEngine/RenderEngine.h"
#include "../Game/Enemy.h"

#include "../EventSystem/Listener.h"

namespace Clumsy
{
	class CoreEngine : public Listener
	{
	public:
		CoreEngine(float frameRate, Window* window, Game* game, Game* level2) :
			m_IsRunning(false),
			m_FrameTime(1.0f/frameRate),
			m_Window(window),
			m_Game(game),
			m_Level2(level2)
		{
			m_Game->Init();
		}
		unsigned int loadCubemap(std::vector<std::string> faces);

		void Start();
		void Stop();

		void SetGame(Game* game) {
			RenderEngine::GetInstance()->SetFirstLevel(false);
			RenderEngine::GetInstance()->m_SecondLevelInstruction = true;
			RenderEngine::GetInstance()->SetBurntToZero();
			TurnSystem::GetInstance()->SetTurnCounter(0);
			RenderEngine::GetInstance()->enemy->SetIsDead(true);
			m_Game->getRoot().DeleteAll();
			RenderEngine::GetInstance()->m_Cubes.clear();
			TurnSystem::GetInstance()->DeletePlayers();
			RenderEngine::GetInstance()->boys.clear();
			PhysicsEngine::GetInstance()->m_Objects.clear();
			RenderEngine::GetInstance()->treeTransforms.clear();
			RenderEngine::GetInstance()->cutTreesTransforms.clear();
			RenderEngine::GetInstance()->ground.clear();
			RenderEngine::GetInstance()->groundBurned.clear();
			RenderEngine::GetInstance()->groundSand.clear();
			m_Game = game;
			m_Game->Init();
			RenderEngine::GetInstance()->SetScaleUp(0.0f);
			RenderEngine::GetInstance()->SetXScaleBackgroundDefault(0.0f);

		}

		void HandleEvent(Event* event);


	private:
		
		bool m_IsRunning;				//Whether or not the engine is running
		float m_FrameTime = 0.0f;		//How long, in seconds, one frame should take
		Window* m_Window;				//Used to display the game
		Game* m_Game;					//The game itself. Stored as pointer so the user can pass in a derived class.
		Game* m_Level2;					


	};
}