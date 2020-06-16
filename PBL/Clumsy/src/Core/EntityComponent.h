#pragma once

#include "GameObject.h"

namespace Clumsy 
{
	class EntityComponent 
	{	
	public:
		EntityComponent() {}
		~EntityComponent() {}


		virtual void Render(Shader& shader, RenderEngine& renderEngine) {}
		void SetParent(GameObject* parent) { m_Parent = parent; }
		
		GameObject* GetParent() { return m_Parent; }
		Transform* GetParentTransform() { return &m_Parent->GetTransform(); }
		
		virtual void Render(Shader& shader) {}
		virtual void Update() {}
		virtual void ProcessInput(int input) {}

	private:
		GameObject* m_Parent; 
	};
}