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

		void SetShakeTime(float time) { m_ShakeTime = time; }
		PostProcessor* GetEffects() { return Effects; }

		GameObject getRoot() { return m_Root; }
		void SceneParser(GameObject* map);

	private:
		GameObject m_Root;
		float m_ShakeTime = 0.0f;

	protected:
		PostProcessor* Effects;
	};
}