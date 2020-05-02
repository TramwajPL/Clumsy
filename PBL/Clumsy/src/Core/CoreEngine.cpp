
#include "../pch.h"

#include "CoreEngine.h"

namespace Clumsy
{
	void CoreEngine::Start()
	{
		if (m_IsRunning)
		{
			return;
		}

		m_IsRunning = true;



		while (m_IsRunning)
		{

		}
	}

	void CoreEngine::Stop()
	{
		m_IsRunning = false;
	}
}