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
	class TurnClass;

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
	
		/*bool GetWasCut() { return m_WasCut; }
		void SetWasCut(bool bool1) { m_WasCut = &bool1; }*/
		virtual int GetCollectedTreesCount() { return m_CountCollectedTrees; }
		virtual bool GetRenderEnemy() { return m_RenderEnemy; }
		virtual bool GetWasCut() { return m_WasCut; }
		virtual void SetM_Tag(std::string tag) { m_Tag = tag; }


		virtual void SetWasCut(bool bool1) { }
		//virtual void SetCollectedTreesCount(int newCount) { m_CountCollectedTrees = newCount; }
		virtual void SetRenderEnemy(bool renderEnemy) { m_RenderEnemy = renderEnemy; }
		virtual void checkIfRender(int collectedTrees) { } //enemy
		
		//virtual std::vector<Transform> getTreeTransform() { return m_TreeTransforms; }
		//virtual void setTreeTransform(std::vector<Transform> newTransform) {}
		virtual void UpdateTurn() {}
		virtual void SetTurnClass(TurnClass* tc) {}
		RenderModelComponent* m_Rmc;

	protected:
		int m_CountCollectedTrees;
		bool m_WasCut = false;
		bool m_RenderEnemy = false;
		Transform m_Transform; 
		std::string m_Tag = "";
		//std::vector<Transform> m_TreeTransforms;
	private:
		
		std::vector<glm::vec3> points;
		std::vector<EntityComponent*> m_Components;
		std::vector<GameObject*> m_Children;
	};

}