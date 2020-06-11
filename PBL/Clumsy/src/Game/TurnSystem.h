#pragma once

#include <vector>

#include "TurnClass.h"

namespace Clumsy
{
	class TurnSystem
	{
	public:
		void ResetTurns(); 
		void UpdateTurns();

	private:
		std::vector<TurnClass> players;

	};
}
