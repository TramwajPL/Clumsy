#pragma once
#include "../Core/GameObject.h"
#include "../RenderEngine//Model.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <future>

namespace Clumsy {

	class Enemy : public GameObject
	{
	public:
		Enemy(Model* modelInitial, Transform transform, int maxCollectedTrees = 3) :
			m_ModelInitial(modelInitial), m_MaxCollectedTrees(maxCollectedTrees), GameObject(transform)
		{
			enemyModel1 = new Clumsy::Model();
			enemyModel2 = new Clumsy::Model();
			enemyModel1->loadModel("../Clumsy/src/models/enemyModels/Idle/Idle.dae");
			enemyModel2->loadModel("../Clumsy/src/models/enemyModels/Mutant Dying/Mutant Dying.dae");
		}
		Enemy() {}

		void SetM_Tag(std::string tag) override { m_Tag = tag; }
		bool GetRenderEnemy() override { return m_RenderEnemy; }
		void SetRenderEnemy(bool renderEnemy) { m_RenderEnemy = renderEnemy; }

		void checkIfRender(int collectedTrees) override
		{
			if (collectedTrees == m_MaxCollectedTrees)
			{
				SetIsDead(false);
				SetRenderEnemy(true);
				m_IsActive = true;
			}
		}

		void Die(int test)
		{
			if (test == 4)
			{
				SetIsDead(true);
				SetCondition(true);
				m_IsActive = false;
			}

		}

		void chechIfDead(int test)
		{
			if (test == 2)
			{
				SetShouldBeDead(true);

				////z opóŸnieniem
				//auto f = std::async(std::launch::async, [&]() {
				//	// Use sleep_for to wait specified time (or sleep_until).
				//	std::this_thread::sleep_for(std::chrono::seconds{4});
				//	// Do whatever you want.
				//	Die();
				//});
			}
		}

		void SetAnimationModel()
		{
			//m_Model->loadModel("../Clumsy/src/models/enemyModels/Mutant Dying/Mutant Dying.dae");	
			if (m_ShouldBeDead == true)
			{
				m_ModelInitial = enemyModel2;
				std::cout << "WESZLO 1: " << std::endl;
			}
			else if (m_ShouldBeDead == false && isEnemyDead == false)
			{
				m_ModelInitial = enemyModel1;
				std::cout << "WESZLO 2: " << std::endl;
			}
		}

		bool GetIsDead() override { return isEnemyDead; }
		void SetIsDead(bool dead) override { isEnemyDead = dead; }
		bool GetCondition() { return m_Condition; }
		void SetCondition(bool condition) { m_Condition = condition; }
		void SetShouldBeDead(bool test) { m_ShouldBeDead = test; }
		bool GetShouldBeDead() { return m_ShouldBeDead; }

		bool getIfActive() { return m_IsActive;  }
	private:
		int m_MaxCollectedTrees;
		bool m_Condition = false;
		Model* m_ModelInitial;
		Clumsy::Model* enemyModel1;
		Clumsy::Model* enemyModel2;
		bool m_ShouldBeDead = false;
		bool m_IsActive = false;
	};
}