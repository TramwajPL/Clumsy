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

		//Model GetModel() {
		//	return *model;
		//}

		Transform GetParentTransform() {
			return m_Parent.GetTransform();
		}
		void SetPosition(glm::vec3 vector) {
			m_Parent.GetTransform().SetPos(m_Parent.GetTransform().GetPos() + vector);
		}


		virtual void Render(Shader& shader) {}
		virtual void Update() {}
		virtual void ProcessInput(int input) {}

	private:
		GameObject m_Parent; 
		//Model* model;
	};
}