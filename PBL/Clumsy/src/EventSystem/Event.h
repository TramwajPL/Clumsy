#pragma once

#include <string>
#define EVENT_ID std::string

namespace Clumsy
{
    class Event
    {
    public:
        virtual ~Event() {}
        EVENT_ID GetEventId() { return m_EventId; }

    private:
        EVENT_ID m_EventId;
    };

}
