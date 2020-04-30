#pragma once
#include "GameObject.h"
#include "../RenderEngine/Model.h"

namespace Clumsy {
	//class Model;

	class EntityComponent {
	
	public:
		EntityComponent(Model* model) : model(model) {}
		EntityComponent(){}
		~EntityComponent() {}

		void SetParent(GameObject parent) 
		{
			m_Parent = parent;
		}

		Model GetModel() {
			return *model;
		}

		Transform GetParentTransform() {
			return m_Parent.GetTransform();
		}

	private:
		GameObject m_Parent; 
		Model* model;
	};
}