#pragma once

#include <vector>
#include "PhysicsObject.h"

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