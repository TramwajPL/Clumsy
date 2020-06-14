#pragma once

#include "../pch.h"
#include "../Core/GameObject.h"

namespace Clumsy
{
	class Warehouse : public GameObject
	{
	public:
		Warehouse(Transform transform) : GameObject(transform) {}
		~Warehouse() {}
		int GetWoodStored() { return m_WoodStored; }
		void StorePieceOfWood() { m_WoodStored++; }
		void WithdrawPieceOfWood() { m_WoodStored--; }

	private:
		int m_WoodStored = 0;
	};
}
