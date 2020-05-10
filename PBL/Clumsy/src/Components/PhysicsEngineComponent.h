#pragma once

#include "../Core/EntityComponent.h"
#include "../PhysicsEngine/PhysicsEngine.h"

namespace Clumsy 
{
	class PhysicsEngineComponent : public EntityComponent 
	{
	public:
		PhysicsEngineComponent(PhysicsEngine& physicsEngine) : 
			m_PhysicsEngine(physicsEngine) {}

		virtual void Update() 
		{
			m_PhysicsEngine.HandleCollisions();
		}

		PhysicsEngine& GetPhysicsEngine() { return m_PhysicsEngine; }

	private:
		PhysicsEngine m_PhysicsEngine;
	};
}