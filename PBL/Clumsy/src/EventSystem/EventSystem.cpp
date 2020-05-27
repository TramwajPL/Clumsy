
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

	bool EventSystem::AlreadySubscribed(EVENT_ID eventId, Listener* listener)
	{
		bool alreadySubbed = false;

		/*std::map<EVENT_ID, std::vector<Listener*>>::iterator it = m_Observers.find(eventId);
		if (it != m_Observers.end())
		{
			for (int i = 0; i < m_Observers[eventId].size(); i++)
			{
				if (m_Observers[eventId][i] == listener)
				{
					alreadySubbed = true;
					break;
				}
			}
		}*/
		return alreadySubbed;
	}

	void EventSystem::DispatchEvent(Event* event)
	{
		/*for (int i = 0; i < m_Observers[event->GetEventId()].size(); i++)
		{
			m_Observers[event->GetEventId()][i]->HandleEvent(event);
		}*/
	}

	void EventSystem::SubscribeListener(EVENT_ID eventId, Listener* listener)
	{
		/*if (!listener || AlreadySubscribed(eventId, listener))
			return;

		m_Observers[eventId].push_back(listener);*/
	}

	void EventSystem::UnsubscribeListener(EVENT_ID eventId, Listener* listener)
	{

	}

	void EventSystem::UnsubscribeAll(Listener* listener)
	{

	} 

	void EventSystem::SendEvent(EVENT_ID eventId)
	{

	}

	void EventSystem::ProcessEvents()
	{

	}

	void EventSystem::ClearEvents()
	{

	}

	void EventSystem::ShutDown()
	{

	}
}