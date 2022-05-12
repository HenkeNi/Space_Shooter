#include "pch.h"
#include "Dispatcher.h"
#include "Event.h"
#include "Subscriber.h"


Dispatcher& Dispatcher::GetInstance()
{
	static Dispatcher instance;
	return instance;
}

void Dispatcher::Subscribe(const eEvent aEventType, Subscriber* aSubscriber)
{
	m_subscribers[static_cast<int>(aEventType)].push_back(aSubscriber);
}

void Dispatcher::Unsubscribe(const eEvent aEventType, Subscriber* aSubscriber)
{
	// TODO: assert it exists in array...

	int index = static_cast<int>(aEventType);
	m_subscribers[index].erase(std::remove(m_subscribers[index].begin(), m_subscribers[index].end(), aSubscriber), m_subscribers[index].end());
}

void Dispatcher::SendEvent(const Event& aEvent)
{
	int index = static_cast<int>(aEvent.GetEventType());
	for (int i = 0; i < m_subscribers[index].size(); ++i)
	{
		m_subscribers[index][i]->Recieve(aEvent);
	}
}