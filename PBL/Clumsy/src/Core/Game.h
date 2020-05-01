#pragma once
#include "Input.h"
#include "GameObject.h"

namespace Clumsy {

	class Game
	{
	public:
		void ProcessInput(const Input& input, float delta);
		void Update(float delta);
		void Render();
		void AddToScene(GameObject* m_Child) { m_Root.AddChild(m_Child); }
	private:
		GameObject m_Root;
	};
}