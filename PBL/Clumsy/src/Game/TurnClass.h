#pragma once

#include "Player.h"

namespace Clumsy
{
	class TurnClass
	{
	public:
		TurnClass(GameObject* go) : 
			m_GameObject(go) {}

		GameObject* GetGameObject() { return m_GameObject; }

	private:
		GameObject* m_GameObject;
		bool isTurn = false;
		bool wasTurnPrev = false;
	};
}