
#include "../pch.h"

#include "EventSystem.h"

namespace Clumsy
{
	EventSystem* EventSystem::GetInstance()
	{
		if (!m_Instance)
			m_Instance = new EventSystem;
		return m_Instance;
	}

	bool AlreadySubscribed(EVENT_ID eventId, Listener* listener)
	{
		bool alreadySubbed = false;
		return alreadySubbed;
	}

	void DispatchEvent(Event* event)
	{

	}

	void EventSystem::SubscribeListener(EVENT_ID eventId, Listener* listener)
	{

	}

	void UnsubscribeListener(EVENT_ID eventId, Listener* listener)
	{

	}

	void UnsubscribeAll(Listener* listener)
	{

	} 

	void SendEvent(EVENT_ID eventId)
	{

	}

	void ProcessEvents()
	{

	}

	void ClearEvents()
	{

	}

	void ShutDown()
	{

	}
}