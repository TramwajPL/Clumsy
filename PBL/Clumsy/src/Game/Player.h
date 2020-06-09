#pragma once

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

	private:
		int maxActions = 10;
		int actionsCount = 0;
		int maxWood = 5;
		int woodCount = 0;
	};
}