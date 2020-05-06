#pragma once

#include "GameObject.h"
#include "../RenderEngine/Model.h"

namespace Clumsy {

	class EntityComponent {
	
	public:
		//EntityComponent(Model* model) : model(model) {}
		EntityComponent() {}
		~EntityComponent() {}

		void SetParent(GameObject parent) 
		{
			m_Parent = parent;
		}

		//GameObject GetParent() {
		//	return m_Parent;
		//}

		//Model GetModel() {
		//	return *model;
		//}
		//inline Transform* GetTransform() { return m_Parent->GetTransform(); }
		//inline const Transform& GetTransform() const { return *m_Parent->GetTransform(); }

		Transform GetParentTransform() {
			return m_Parent.GetTransform();
		}
		
		
		//void SetPosition(glm::vec3 vector) {
		//	m_Parent.GetTransform().SetPos(m_Parent.GetTransform().GetPos() + vector);
		//}


		virtual void Render(Shader& shader) {}
		virtual void Update() {}
		virtual void ProcessInput(int input) {}
		//virtual Collider GetCollider(){}

	private:
		GameObject m_Parent; 
		//Model* model;
	};
}