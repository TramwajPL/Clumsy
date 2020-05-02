#pragma once

#include <glm/glm.hpp>
#include "BoundingSphere.h"

namespace Clumsy
{
	class PhysicsObject
	{
	public:
		PhysicsObject(Collider* collider, const glm::vec3& velocity) :
			m_Position(collider->GetCenter()), 
			m_OldPosition(collider->GetCenter()),
			m_Velocity(velocity), 
			m_Collider(collider) {}

		PhysicsObject(const PhysicsObject& other);
		void operator=(PhysicsObject other);
		virtual ~PhysicsObject();

		void Integrate(float delta);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetVelocity() const { return m_Velocity; }

		inline const Collider& GetCollider()
		{
			glm::vec3 translation = m_Position - m_OldPosition;
			m_OldPosition = m_Position;
			m_Collider->Transform(translation);

			return *m_Collider;
		}

		inline void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }

	private:
		glm::vec3 m_Position;
		glm::vec3 m_OldPosition;
		glm::vec3 m_Velocity;

		Collider* m_Collider;
	};
}
