#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Clumsy {

	class Transform
	{
	public:
		Transform(const glm::vec3& pos = glm::vec3(0, 0, 0), const glm::quat& rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f), float scale = 1.0f) :
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_parent(0),
			m_parentMatrix(glm::mat4(1.0f)) {}

		glm::mat4 GetTransformation() const;
		bool HasChanged();
		void Update();
		void Rotate(const glm::vec3& axis, float angle);
		void Rotate(const glm::quat& rotation);
		void LookAt(const glm::vec3& point, const glm::vec3& up);

		inline glm::vec3* GetPos() { return &m_pos; }
		inline const glm::vec3& GetPos()       const { return m_pos; }
		inline glm::quat* GetRot() { return &m_rot; }
		inline const glm::quat& GetRot()     const { return m_rot; }
		inline float GetScale()               const { return m_scale; }
		inline glm::vec3 GetTransformedPos(glm::vec3 newVector)   const;
		glm::quat GetTransformedRot()        const;

		inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
		inline void SetRot(const glm::quat& rot) { m_rot = rot; }
		inline void SetScale(float scale) { m_scale = scale; }
		inline void SetParent(Transform* parent) { m_parent = parent; }

		inline glm::vec3 GetTransformedPos() const;

		glm::mat4 SetRotation();
	protected:
	private:
		const glm::mat4& GetParentMatrix() const;

		glm::vec3 m_pos;
		glm::quat m_rot;
		float m_scale;

		Transform* m_parent;
		mutable glm::mat4 m_parentMatrix;

		mutable glm::vec3 m_oldPos;
		mutable glm::quat m_oldRot;
		mutable float m_oldScale;
		mutable bool m_initializedOldStuff;
	};
}