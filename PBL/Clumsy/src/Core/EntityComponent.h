#pragma once

#include "GameObject.h"
#include "../RenderEngine/Model.h"

namespace Clumsy 
{
	class EntityComponent 
	{	
	public:
		EntityComponent() {}
		~EntityComponent() {}

		void SetParent(GameObject parent) { m_Parent = parent; }
		
		Transform GetParentTransform() { return m_Parent.GetTransform(); }
		
		virtual void Render(Shader& shader) {}
		virtual void Update() {}
		virtual void ProcessInput(int input) {}

	private:
		GameObject m_Parent; 
	};
}