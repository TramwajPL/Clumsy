#pragma once

#include <vector>

#include "Player.h"
#include "TurnClass.h"

namespace Clumsy
{
	class TurnSystem
	{
	public:
		void ResetTurns(); 
		void Update();
		void UpdateTurns();
		GameObject* GetActivePlayer();
		void AddPlayer(GameObject* player);
		void DeletePlayer(GameObject* player);

		static TurnSystem* GetInstance();

	private:
		std::vector<TurnClass> players;
		GameObject* m_ActivePlayer;
		int m_TurnCounter = 0;
		static TurnSystem* m_Instance;

		TurnSystem();

	};
}
