#pragma once

#include <vector>

#include "PhysicsObject.h"

namespace Clumsy
{
	class PhysicsEngine
	{
	public:
		static PhysicsEngine* GetInstance();

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
		PhysicsEngine() {}
		static PhysicsEngine* m_Instance;
		std::vector<PhysicsObject> m_Objects;
	};
}