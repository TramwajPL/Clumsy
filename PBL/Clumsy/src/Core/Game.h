#pragma once

#include "Input.h"
#include "GameObject.h"
#include "../RenderEngine/RenderEngine.h"
#include "../PhysicsEngine/PhysicsEngine.h"

namespace Clumsy 
{
	class Game
	{
	public:
		virtual void Init() {} 
		virtual void Move() {}
		void Render(RenderEngine* renderingEngine);
		void Update();
		void ProcessInput(int input);
		void AddToScene(GameObject* child);

		GameObject getRoot() { return m_Root; }
		void SceneParser(PhysicsEngine* physicsEngine, GameObject* map);

	private:
		GameObject m_Root;
	};
}