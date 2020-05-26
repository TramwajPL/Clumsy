#pragma once

#include "../pch.h"

#include <vector>

#include "Input.h"
#include "Transform.h"
#include "../Components/PhysicsObjectComponent.h"

namespace Clumsy 
{
	class EntityComponent;
	class Shader;
	class RenderEngine;

	class GameObject 
	{
	public:
		GameObject(Transform transform, PhysicsObjectComponent physics = NULL);
		GameObject() {};
		~GameObject() {};

		
		Transform GetTransform();
		void SetPos(glm::vec3 vect) { m_Transform.SetPos(vect); }

		GameObject* AddComponent(EntityComponent* component);
		void AddChild(GameObject* child);

		std::vector<EntityComponent*> GetComponents();
		std::vector<GameObject*> GetAllChildren();

		//These guys may need some arguments
		void Render(Shader& shader); //probably can be private
		void RenderAll(Shader& shader);  


		void Update();
		void UpdateAll();

		void ProcessInput(int input);
		void ProcessInputAll(int input);

		void setPhysics(PhysicsObjectComponent physics2) { physics = physics2; }

	private:
		PhysicsObjectComponent physics = NULL;
		std::string m_Tag;
		Transform m_Transform; 
		std::vector<EntityComponent*> m_Components;
		std::vector<GameObject*> m_Children;

	};

}