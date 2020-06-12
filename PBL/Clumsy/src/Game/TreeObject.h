#pragma once
#include "../Core/GameObject.h"

namespace Clumsy {
	
	class TreeObject : public GameObject
	{
	public:
		TreeObject(Transform transform) : GameObject(transform) {}
		TreeObject() {}
		bool GetWasCut() override { return m_WasCut; }
		void SetWasCut(bool bool1) override { m_WasCut = &bool1; }
		void SetM_Tag(std::string tag) { m_Tag = tag; }
	private:
	};
}