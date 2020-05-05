#pragma once

#include <vector>

#include "Transform.h"
#include "../pch.h"
//#include "EntityComponent.h"

namespace Clumsy {
	class EntityComponent;
	class Shader;

	class GameObject {
	public:
		GameObject(Transform transform);
		GameObject() {};
		~GameObject() {};

		
		Transform GetTransform();
		void SetTranfsorm();

		GameObject* AddComponent(EntityComponent* component);
		void AddChild(GameObject* child);


		std::vector<EntityComponent*> GetComponents();
		//EntityComponent* GetModelComponent();

		//glm::mat4 TranslateModelMatrix(glm::mat4 modelMatrix);
		//glm::mat4 ScaleModelMatrix(glm::mat4 modelMatrix);

		std::vector<GameObject*> GetAllChildren();


		//These guys may need some arguments
		void Render(Shader& shader); //probably can be private
		void RenderAll(Shader& shader);  

		void Update();
		void UpdateAll();

	
	private:
		Transform m_Transform; 
		std::vector<EntityComponent*> m_Components;
		std::vector<GameObject*> m_Children;

	};

}