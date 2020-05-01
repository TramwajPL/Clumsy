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

		virtual void AddToEngine(RenderEngine* engine) const { }

		Transform GetTransform() { return m_Parent.GetTransform(); }
		//inline const Transform GetTransform() const { return m_Parent.GetTransform(); }
		virtual void ProcessInput(const Input& input, float delta) {}
	private:
		GameObject m_Parent; 
		Model* model;
	};
}