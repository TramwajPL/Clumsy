#pragma once

#include <vector>

#include "Input.h"
#include "Transform.h"

namespace Clumsy 
{
	class EntityComponent;
	class Shader;
	class RenderEngine;
	class PhysicsObjectComponent;
	class RenderModelComponent;

	class GameObject 
	{
	public:
		GameObject(Transform transform);
		GameObject() {}
		~GameObject() {}

		
		Transform GetTransform();
		void SetPos(glm::vec3 vect) { m_Transform.SetPos(vect); }
		glm::vec3 GetPos() { m_Transform.GetPos(); }

		GameObject* AddComponent(EntityComponent* component);
		void AddChild(GameObject* child);

		std::vector<EntityComponent*> GetComponents();
		std::vector<GameObject*> GetAllChildren();

		//These guys may need some arguments
		void Render(Shader& shader); //probably can be private
		void RenderAll(Shader& shader);  
		bool SetupAabb();

		void Update();
		void UpdateAll();

		void ProcessInput(int input);
		void ProcessInputAll(int input);
		std::string GetM_Tag() { return m_Tag; }
		virtual void SetM_Tag(std::string tag) { m_Tag = tag; }
	
		/*bool GetWasCut() { return m_WasCut; }
		void SetWasCut(bool bool1) { m_WasCut = &bool1; }*/
		virtual bool GetWasCut() { return m_WasCut; }
		virtual void SetWasCut(bool bool1) { }

		RenderModelComponent* m_Rmc;

	protected:
		bool m_WasCut = false;
		Transform m_Transform; 
		std::string m_Tag = "";
	private:
		
		std::vector<glm::vec3> points;
		std::vector<EntityComponent*> m_Components;
		std::vector<GameObject*> m_Children;
	};

}