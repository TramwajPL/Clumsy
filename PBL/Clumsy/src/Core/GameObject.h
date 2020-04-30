#pragma once
#include "Transform.h"
//#include "EntityComponent.h"
//#include "../RenderEngine/Model.h"
#include <vector>

namespace Clumsy {
	class EntityComponent;

	class GameObject {
	public:
		GameObject(Transform transform);
		GameObject() {};
		~GameObject() {};

		
		Transform GetTransform();

		void AddComponent(EntityComponent* component) {
			m_Components.push_back(component);
			//component->SetParent(*this);
		}

		EntityComponent* GetModelComponent() {
			return m_Components[0];
		}
	private:
		Transform m_Transform; 
		std::vector<EntityComponent*> m_Components;
	};

}