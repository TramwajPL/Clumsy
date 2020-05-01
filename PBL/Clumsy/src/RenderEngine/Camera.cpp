//
//#include <glm/glm.hpp>
//#include <glm/gtx/quaternion.hpp>
//
//#include "Camera.h"
//#include "../Core/Input.h"
//#include <glfw3.h>
//
//
//namespace Clumsy {
//
//	glm::mat4 Camera::GetViewProjection() const
//	{
//		//Obczaj t¹ funkcjê SetRotation bo j¹ dorobi³am w Trnsform na razie tak na szybko bo on u¿ywa³ tej swojej matmy jakoœdo tego 
//		glm::mat4 cameraRotation = m_Transform->SetRotation();
//		glm::mat4 cameraTranslation = glm::mat4(1.0f);
//
//		glm::vec3 cameraInvert = glm::vec3(-1.0f);			
//	    cameraTranslation = glm::translate(cameraTranslation, m_Transform->GetTransformedPos() * cameraInvert);
//
//	   return m_Projection * cameraRotation * cameraTranslation;
//	}
//
//	void Camera::RecalculateViewMatrix()
//	{
//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Transform->GetPos()) *
//			glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1)); //for the z axis
//
//		glm::mat4 m_ViewMatrix = glm::inverse(transform);
//		m_Projection = m_Projection * m_ViewMatrix;
//	}
//
//	void CameraComponent::OnUpdate(Timestep ts)
//	{
//		/*if (Input::IsKeyPressed(GLFW_KEY_A))
//			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
//		else if (Input::IsKeyPressed(GLFW_KEY_D))
//			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
//
//		if (Input::IsKeyPressed(GLFW_KEY_W))
//			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
//		else if (Input::IsKeyPressed(GLFW_KEY_S))
//			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;*/
//
//		/*if (m_Rotation) {
//			if (Input::IsKeyPressed(GLFW_KEY_Q))
//				m_CameraRotation += m_CameraRotationSpeed * ts;
//			else if (Input::IsKeyPressed(GLFW_KEY_E))
//				m_CameraRotation -= m_CameraRotationSpeed * ts;
//
//			m_Camera.SetRotation(m_CameraRotation);
//		}*/
//
//		m_Camera.GetTransform()->SetPos(m_CameraPosition);
//		m_Camera.RecalculateViewMatrix();
//		//m_Camera.SetPosition(m_CameraPosition);
//	}
//}