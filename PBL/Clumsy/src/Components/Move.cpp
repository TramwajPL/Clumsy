#include "Move.h"

namespace Clumsy {

	void Move::ProcessInput(const Input& input, float delta)
	{
		float movAmt = m_Speed * delta;
		glm::vec3 Front = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 Back =  glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up =    glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Down =  glm::vec3(0.0f, -1.0f, 0.0f);
		glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 Left =  glm::vec3(-1.0f, 0.0f, 0.0f);

		if (input.GetKey(m_ForwardKey))
			MoveObject(CastToVector(GetTransform().GetRot()) + Front, movAmt);
		else if (input.GetKey(m_BackKey))
			MoveObject(CastToVector(GetTransform().GetRot()) + Back, movAmt);
		if (input.GetKey(m_LeftKey))
			MoveObject(CastToVector(GetTransform().GetRot()) + Left, movAmt);
		else if (input.GetKey(m_RightKey))
			MoveObject(CastToVector(GetTransform().GetRot()) + Right, movAmt);
	}

	glm::vec3 Move::CastToVector(glm::quat* test)
	{
		glm::vec3 vector = glm::vec3(test->x,test->y, test->z);
		return vector;
	}

	void Move::MoveObject(glm::vec3 direction, float amt)
	{
		GetTransform().SetPos(GetTransform().GetPos() + (direction * amt));
	}
}