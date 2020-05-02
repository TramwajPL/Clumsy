#pragma once

#include <vector>

#include "Transform.h"

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

		glm::mat4 TranslateModelMatrix(glm::mat4 modelMatrix);
		glm::mat4 ScaleModelMatrix(glm::mat4 modelMatrix);

	
	private:
		Transform m_Transform; 
		std::vector<EntityComponent*> m_Components;

	};

}