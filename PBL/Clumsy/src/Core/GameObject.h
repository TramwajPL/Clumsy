#pragma once

#include "../pch.h"

#include <vector>

#include "Input.h"
#include "Transform.h"

namespace Clumsy 
{
	class EntityComponent;
	class Shader;

	class GameObject 
	{
	public:
		GameObject(Transform transform);
		GameObject() {};
		~GameObject() {};

		
		Transform GetTransform();
		void SetPos(glm::vec3 vect) { m_Transform.SetPos(vect); }

		GameObject* AddComponent(EntityComponent* component);
		void AddChild(GameObject* child);

		std::vector<EntityComponent*> GetComponents();
		std::vector<GameObject*> GetAllChildren();

		void Render(Shader& shader); //probably can be private
		void RenderAll(Shader& shader);  

		void Update();
		void UpdateAll();

		void ProcessInput(int input);
		void ProcessInputAll(int input);
	
	private:
		Transform m_Transform; 
		std::vector<EntityComponent*> m_Components;
		std::vector<GameObject*> m_Children;

	};

}