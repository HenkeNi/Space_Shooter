#include "pch.h"
#include "Event.h"


Event::Event(eEvent aEventType, const EventData_t& someData)
	: m_type{ aEventType }, m_data{ someData }
{
}

eEvent Event::GetEventType()				const
{
	return m_type;
}

const Event::EventData_t& Event::GetData()	const
{
	return m_data;
}

Event::EventData_t	Event::GetData()
{
	return m_data;
}
