#pragma once

#include <string>
#define EVENT_ID std::string

namespace Clumsy
{
    class Event
    {
    public:
        Event(EVENT_ID eventId) :
            m_EventId(eventId) {}
        ~Event() {}
        EVENT_ID GetEventId() { return m_EventId; }

    private:
        EVENT_ID m_EventId;
    };

}
