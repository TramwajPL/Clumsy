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

		int GetNumObjects()
		{
			return (unsigned int)m_Objects.size();
		}

		PhysicsObject& GetObject(int index)
		{
			return m_Objects[index];
		}
	private:
		std::vector<PhysicsObject> m_Objects;
	};
}