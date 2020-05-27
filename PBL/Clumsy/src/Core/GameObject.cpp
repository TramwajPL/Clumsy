
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "GameObject.h"
#include "EntityComponent.h"
#include "../RenderEngine/RenderEngine.h"
#include "../Components/PhysicsObjectComponent.h"

namespace Clumsy
{
	Clumsy::GameObject::GameObject(Transform transform)//, PhysicsObjectComponent* poc) 
		: m_Transform(transform) {}
	//m_POC(poc) {}

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

	void GameObject::Render(Shader& shader)
	{
		for (int i = 0; i < m_Components.size(); i++)
		{
			m_Components[i]->Render(shader);
		}
	}

	bool GameObject::SetupAabb() {
		glm::vec3 point0 = this->GetTransform().GetPos();
		glm::vec3 min = point0 - 2.0f;
		glm::vec3 max = point0 + 2.0f;

		points.push_back(min);
		points.push_back(max);

		glm::vec3 p;
		p.x = points[1].x;
		p.y = points[0].y;
		p.z = points[0].z;
		points.push_back(p);

		p.x = points[1].x;
		p.y = points[1].y;
		p.z = points[0].z;
		points.push_back(p);

		p.x = points[0].x;
		p.y = points[1].y;
		p.z = points[0].z;
		points.push_back(p);

		p.x = points[0].x;
		p.y = points[0].y;
		p.z = points[1].z;
		points.push_back(p);

		p.x = points[0].x;
		p.y = points[1].y;
		p.z = points[1].z;
		points.push_back(p);

		p.x = points[1].x;
		p.y = points[0].y;
		p.z = points[1].z;
		points.push_back(p);

		for (int i = 0; i < points.size(); i++)
		{
			for (int j = 0; j < RenderEngine::GetInstance()->GetPl().size(); j++)
			{
				if (!RenderEngine::GetInstance()->pointInPlane(RenderEngine::GetInstance()->GetPl()[j], points[i]))
					return false;
			}
		}
		return true;

	}

	void GameObject::RenderAll(Shader& shader)
	{
		if (GetComponents().size() <= 1)
		{
			Render(shader);
		}
		else
		{
			PhysicsObjectComponent* poc = (PhysicsObjectComponent*)GetComponents()[1];
			if (SetupAabb())
			{
				RenderEngine::GetInstance()->m_Counter++;
				//std::cout << "KURWA" << RenderEngine::GetInstance()->m_Counter << std::endl;
				Render(shader);
			}
			else
			{
				std::cout << "KUPSKO #########" << std::endl;
			}
		}

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