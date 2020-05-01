#include "GameObject.h"
#include "EntityComponent.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>


namespace Clumsy {

	GameObject::GameObject(Transform transform) 
		: m_Transform(transform)
	{

	}

	Transform GameObject::GetTransform() {
		return m_Transform;
	}

	glm::mat4 GameObject::TranslateModelMatrix(glm::mat4 modelMatrix)
	{
		return glm::translate(modelMatrix, this->GetTransform().GetPos());
		//std::cout << "modelMatrix: " << glm::to_string(modelMatrix) << std::endl;
	}

	glm::mat4 GameObject::ScaleModelMatrix(glm::mat4 modelMatrix)
	{
		return glm::scale(modelMatrix, glm::vec3(this->GetTransform().GetScale()));
		//std::cout << "Skala: " << this->GetTransform().GetScale();
	}

	void GameObject::SetEngine(RenderEngine* engine)
	{
		if (m_CoreEngine != engine)
		{
			m_CoreEngine = engine;

			for (unsigned int i = 0; i < m_Components.size(); i++)
			{
				m_Components[i]->AddToEngine(engine);
			}
			for (unsigned int i = 0; i < m_Children.size(); i++)
			{
				m_Children[i]->SetEngine(engine);
			}
		}
	}

	GameObject* GameObject::AddChild(GameObject* child)
	{
		m_Children.push_back(child);
		child->GetTransform().SetParent(&m_Transform);
		child->SetEngine(m_CoreEngine);
		return this;
	}

}