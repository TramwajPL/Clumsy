#include "GameObject.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "EntityComponent.h"

namespace Clumsy {

	Clumsy::GameObject::GameObject(Transform transform) 
		: m_Transform(transform)
	{

	}

	Transform Clumsy::GameObject::GetTransform() {
		return m_Transform;
	}


	//Adding component to game object
	GameObject* GameObject::AddComponent(EntityComponent* component)
	{
		m_Components.push_back(component);
		component->SetParent(*this);
		return this;
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
		child->GetTransform().SetParent(&m_Transform);
	}

	std::vector<GameObject*> GameObject::GetAllChildren()
	{
		return m_Children;
	}

	void GameObject::Render(Shader& shader)
	{
		for (int i = 0; i < m_Components.size(); i++) {
			m_Components[i]->Render(shader);
		}
	}

	void GameObject::RenderAll(Shader& shader)
	{
		Render(shader);

		for (int i = 0; i < m_Children.size(); i++) {
			m_Children[i]->RenderAll(shader);
		}
	}



}