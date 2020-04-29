#pragma once

#include "PhysicsObject.h"
#include <vector>

namespace Clumsy
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine() {}
		void AddObject(const PhysicsObject& object);
		void Simulate(float delta);

		void HandleCollisions();

	private:
		std::vector<PhysicsObject> m_Objects;
	};
}