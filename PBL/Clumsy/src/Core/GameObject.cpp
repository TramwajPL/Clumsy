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


	//Adding component to game object
	void GameObject::AddComponent(EntityComponent* component)
	{
		m_Components.push_back(component);
	}

	//Getting model component (probably for now)
	EntityComponent* GameObject::GetModelComponent()
	{
		return m_Components[0];
	}

	//Used to render model at certain position
	glm::mat4 Clumsy::GameObject::TranslateModelMatrix(glm::mat4 modelMatrix)
	{
		return glm::translate(modelMatrix, this->GetTransform().GetPos());
		//std::cout << "modelMatrix: " << glm::to_string(modelMatrix) << std::endl;
	}

	//Used to render model in certain scale
	glm::mat4 Clumsy::GameObject::ScaleModelMatrix(glm::mat4 modelMatrix)
	{
		return glm::scale(modelMatrix, glm::vec3(this->GetTransform().GetScale()));
		//std::cout << "Skala: " << this->GetTransform().GetScale();
	}

	void GameObject::AddChild(GameObject* child)
	{
		m_Children.push_back(child);
	}

	std::vector<GameObject*> GameObject::GetAllChildren()
	{
		return m_Children;
	}



}