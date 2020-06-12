#pragma once
#include "../Core/GameObject.h"

namespace Clumsy {

	class Enemy : public GameObject
	{
	public:
		Enemy(Transform transform, int maxCollectedTrees = 3) : m_MaxCollectedTrees(maxCollectedTrees), GameObject(transform) {}
		Enemy() {}

		void SetM_Tag(std::string tag) override { m_Tag = tag; }
		bool GetRenderEnemy() override { return m_RenderEnemy; }
		void SetRenderEnemy(bool renderEnemy) { m_RenderEnemy = renderEnemy; }
		void checkIfRender(int collectedTrees) override
		{
			if (collectedTrees == m_MaxCollectedTrees)
			{
				SetRenderEnemy(true);
			}
		}
	private:
		int m_MaxCollectedTrees;
	};
}