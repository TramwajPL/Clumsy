#pragma once

#include "../pch.h"
#include "../Game/TurnClass.h"
#include "../Core/GameObject.h"

namespace Clumsy
{
	class Player : public GameObject
	{
	public:
		Player(Transform transform) : GameObject(transform) {}
		~Player() {}

		int GetMaxActions() { return maxActions; }
		int GetActionsCount() { return actionsCount; }
		int GetAvailableActions() { return maxActions - actionsCount; }
		int GetMaxWood() { return maxWood; }
		int GetWoodCount() { return woodCount; }
		
		void UseAllActions() { actionsCount = maxActions; }
		void IncrementMaxActions() { maxActions++; }
		void IncrementActionCount() { actionsCount++; }
		void IncrementMaxWood() { maxWood++; }
		void IncrementWoodCount() { woodCount++; }

		bool IsIncrementingWoodCountPossible() 
		{ 
			return (woodCount < maxWood);
		}

		void SetTurnClass(TurnClass* tc) { m_TurnClass = tc; }

		void UpdateTurn()
		{
			isTurn = m_TurnClass->isTurn;
			if (isTurn)
			{
				if (GetAvailableActions() <= 0)
				{
					isTurn = false;
					m_TurnClass->isTurn = isTurn;
					m_TurnClass->wasTurnPrev = true;
					this->actionsCount = 0;
				}
			}
		}

	private:
		int maxActions = 3;
		int actionsCount = 0;
		int maxWood = 5;
		int woodCount = 0;

		bool isTurn = false;
		TurnClass* m_TurnClass = nullptr;
	};
}