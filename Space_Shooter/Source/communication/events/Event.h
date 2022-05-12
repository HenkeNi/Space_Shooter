#pragma once
#include "eEvent.h"


class Event
{
public:
	using EventData_t = std::variant<int, float, std::any>;

	Event(eEvent aEventType, const EventData_t& someData);
	virtual	~Event() = default;

	eEvent				GetEventType()	const;
	const EventData_t&	GetData()		const;
	EventData_t			GetData();

private:
	EventData_t			m_data;
	eEvent				m_type; 

};

