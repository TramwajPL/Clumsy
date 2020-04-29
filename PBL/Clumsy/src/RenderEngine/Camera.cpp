#include "Camera.h"


namespace Clumsy {

	glm::mat4 Camera::GetViewProjection() const
	{
		//Obczaj t¹ funkcjê SetRotation bo j¹ dorobi³am w Trnsform na razie tak na szybko bo on u¿ywa³ tej swojej matmy jakoœdo tego 
		glm::mat4 cameraRotation = m_Transform->SetRotation();
		glm::mat4 cameraTranslation = glm::mat4(1.0f);

		glm::vec3 cameraInvert = glm::vec3(-1.0f);			
	    cameraTranslation = glm::translate(cameraTranslation, m_Transform->GetTransformedPos() * cameraInvert);

	   return m_Projection * cameraRotation * cameraTranslation;
	}
}