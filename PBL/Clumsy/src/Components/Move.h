#pragma once
#include "../Core/Input.h"
#include "../Core/EntityComponent.h"

namespace Clumsy {

	class Move : public EntityComponent
	{
	public:
		Move(float speed = 10.0f, int forwardKey = Input::KEY_W, int backKey = Input::KEY_S, int leftKey = Input::KEY_A, int rightKey = Input::KEY_D) :
			m_Speed(speed),
			m_ForwardKey(forwardKey),
			m_BackKey(backKey),
			m_LeftKey(leftKey),
			m_RightKey(rightKey) {}

		virtual void ProcessInput(const Input& input, float delta);

	private:
		void MoveObject(glm::vec3 direction, float amt);
		glm::vec3 CastToVector(glm::quat* test);

		float m_Speed;
		int   m_ForwardKey;
		int   m_BackKey;
		int   m_LeftKey;
		int   m_RightKey;
	};
}