#pragma once

#include "Input.h"
#include "GameObject.h"
#include "../RenderEngine/RenderEngine.h"

namespace Clumsy {
	//class RenderEngine;

	class Game
	{
	public:
		void ProcessInput(const Input& input);

		virtual void Init() {} //Uzywamy do dodania obiektow w grze wlasciwej juz (w main.cpp)

		void Render(RenderEngine* renderingEngine);
		void Update();
		//void Update();
		//void Render();
		void AddToScene(GameObject* child);

		GameObject getRoot() {
			return m_Root;
		}
	private:
		GameObject m_Root;
	};
}