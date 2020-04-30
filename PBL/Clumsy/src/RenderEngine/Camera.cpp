
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Camera.h"
#include "../Core/Input.h"


namespace Clumsy {

	glm::mat4 Camera::GetViewProjection() const
	{
		//Obczaj t� funkcj� SetRotation bo j� dorobi�am w Trnsform na razie tak na szybko bo on u�ywa� tej swojej matmy jako�do tego 
		glm::mat4 cameraRotation = m_Transform->SetRotation();
		glm::mat4 cameraTranslation = glm::mat4(1.0f);

		glm::vec3 cameraInvert = glm::vec3(-1.0f);			
	    cameraTranslation = glm::translate(cameraTranslation, m_Transform->GetTransformedPos() * cameraInvert);

	   return m_Projection * cameraRotation * cameraTranslation;
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Transform->GetPos()) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Transform->GetRot()), glm::vec3(0, 0, 1)); //for the z axis

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void CameraComponent::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(CLUM_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(CLUM_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(CLUM_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(CLUM_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation) {
			if (Input::IsKeyPressed(CLUM_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(CLUM_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}
}