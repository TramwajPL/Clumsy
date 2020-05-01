#include "GameObject.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>


namespace Clumsy {

	Clumsy::GameObject::GameObject(Transform transform) 
		: m_Transform(transform)
	{

	}

	Transform Clumsy::GameObject::GetTransform() {
		return m_Transform;
	}

	glm::mat4 Clumsy::GameObject::TranslateModelMatrix(glm::mat4 modelMatrix)
	{
		return glm::translate(modelMatrix, this->GetTransform().GetPos());
		//std::cout << "modelMatrix: " << glm::to_string(modelMatrix) << std::endl;
	}

	glm::mat4 Clumsy::GameObject::ScaleModelMatrix(glm::mat4 modelMatrix)
	{
		return glm::scale(modelMatrix, glm::vec3(this->GetTransform().GetScale()));
		//std::cout << "Skala: " << this->GetTransform().GetScale();
	}



}