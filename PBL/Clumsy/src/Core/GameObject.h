#pragma once
#include "Transform.h"
#include "../RenderEngine/RenderEngine.h"
#include <vector>


namespace Clumsy {
	class EntityComponent;

	class GameObject {
	public:
		GameObject(Transform transform);
		GameObject() {};
		~GameObject() {};

		
		Transform GetTransform();

		GameObject* AddChild(GameObject* child);
		void AddComponent(EntityComponent* component) {
			m_Components.push_back(component);
			//component->SetParent(*this);
		}

		EntityComponent* GetModelComponent() {
			return m_Components[0];
		}

		glm::mat4 TranslateModelMatrix(glm::mat4 modelMatrix);
		glm::mat4 ScaleModelMatrix(glm::mat4 modelMatrix);
		void SetEngine(RenderEngine* engine);
	
	private:
		Transform m_Transform; 
		std::vector<EntityComponent*> m_Components;
		std::vector<GameObject*>  m_Children;
		RenderEngine* m_CoreEngine;
	};

}