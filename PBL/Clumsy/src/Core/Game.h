#pragma once

#include "Input.h"
#include "GameObject.h"
#include "../RenderEngine/RenderEngine.h"
#include "../PhysicsEngine/PhysicsEngine.h"

namespace Clumsy {
	//class RenderEngine;

	class Game
	{
	public:
		//void ProcessInput(const Input& input);

		virtual void Init() {} //Uzywamy do dodania obiektow w grze wlasciwej juz (w main.cpp)
		virtual void Move() {}
		void Render(RenderEngine* renderingEngine);
		void Update();
		void ProcessInput(int input);
		//void Update();
		//void Render();
		void AddToScene(GameObject* child);

		GameObject getRoot() {
			return m_Root;
		}
		void SceneParser(PhysicsEngine* physicsEngine, GameObject* map);
	private:
		GameObject m_Root;
	};
}