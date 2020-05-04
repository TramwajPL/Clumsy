#pragma once

#include "GameObject.h"
//#include "../RenderEngine/Model.h"
//#include "../RenderEngine/RenderEngine.h"

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

		virtual void Render(Shader& shader, RenderEngine& renderEngine) {}

	private:
		GameObject m_Parent; 
		//Model* model;
	};
}