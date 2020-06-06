#pragma once

#include "Input.h"
#include "GameObject.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/PostProcessor.h"
#include "../PhysicsEngine/PhysicsEngine.h"

namespace Clumsy 
{
	class Game
	{
	public:
		virtual void Init() {} 
		virtual void Move() {}
		void Render();
		void Update(float deltaTime);
		void ProcessInput(int input);
		void AddToScene(GameObject* child);

		GameObject getRoot() { return m_Root; }
		void SceneParser(GameObject* map);

	private:
		GameObject m_Root;
	};
}