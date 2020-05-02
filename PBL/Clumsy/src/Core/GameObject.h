#pragma once

#include "Transform.h"
#include "../pch.h"

namespace Clumsy {
	class EntityComponent;

	class GameObject {
	public:
		GameObject(Transform transform);
		GameObject() {};
		~GameObject() {};

		
		Transform GetTransform();

		void AddComponent(EntityComponent* component);

		EntityComponent* GetModelComponent();

		glm::mat4 TranslateModelMatrix(glm::mat4 modelMatrix);
		glm::mat4 ScaleModelMatrix(glm::mat4 modelMatrix);

		void AddChild(GameObject* child);
		std::vector<GameObject*> GetAllChildren();

	
	private:
		Transform m_Transform; 
		std::vector<EntityComponent*> m_Components;
		std::vector<GameObject*> m_Children;

	};

}