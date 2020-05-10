
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "GameObject.h"
#include "EntityComponent.h"
#include "../RenderEngine/RenderEngine.h"

namespace Clumsy 
{
	Clumsy::GameObject::GameObject(Transform transform) 
		: m_Transform(transform) {}

	Transform Clumsy::GameObject::GetTransform() 
	{ 
		return m_Transform; 
	}
	
	//Adding component to game object
	GameObject* GameObject::AddComponent(EntityComponent* component)
	{
		m_Components.push_back(component);
		component->SetParent(*this);
		return this;
	}

	void GameObject::AddChild(GameObject* child)
	{
		m_Children.push_back(child);
		child->GetTransform().SetParent(&m_Transform);
	}

	std::vector<EntityComponent*> GameObject::GetComponents()
	{
		return m_Components;
	}

	std::vector<GameObject*> GameObject::GetAllChildren()
	{
		return m_Children;
	}

	void GameObject::Render(Shader& shader, RenderEngine& renderEngine)
	{
		for (int i = 0; i < m_Components.size(); i++) {
			m_Components[i]->Render(shader,  renderEngine);
		}

	}

	void GameObject::RenderAll(Shader& shader, RenderEngine& renderEngine)
		for (int i = 0; i < m_Components.size(); i++) 
		{
			m_Components[i]->Render(shader);
		}

	}
	
	void GameObject::RenderAll(Shader& shader)
	{
		Render(shader, renderEngine);

		for (int i = 0; i < m_Children.size(); i++) {
			m_Children[i]->RenderAll(shader, renderEngine);
		for (int i = 0; i < m_Children.size(); i++) 
		{
			m_Children[i]->RenderAll(shader);
		}

	}

	void GameObject::Update()
	{
		for (int i = 0; i < m_Components.size(); i++) 
		{
			m_Components[i]->Update();
		}
	}

	void GameObject::UpdateAll()
	{
		Update();
		
		for (int i = 0; i < m_Children.size(); i++) 
		{
			m_Children[i]->UpdateAll();
		}
	}

	void GameObject::ProcessInput(int input)
	{
		m_Transform.Update();

		for (int i = 0; i < m_Components.size(); i++) 
		{
			m_Components[i]->ProcessInput(input);
		}
	}

	void GameObject::ProcessInputAll(int input)
	{
		ProcessInput(input);

		for (int i = 0; i < m_Children.size(); i++) 
		{
			m_Children[i]->ProcessInputAll(input);
		}
	}
}