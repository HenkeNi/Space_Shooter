#pragma once
#include "eEvent.h"

class Event;
class Subscriber;

class Dispatcher
{
public:
	using Subscribers_t = std::array<std::vector<Subscriber*>, static_cast<int>(eEvent::Count)>; // TODO: replace array with Binary Search Tree Set or AVL or SPlay Tree?

	static Dispatcher& GetInstance();

	Dispatcher(const Dispatcher&)				= delete;
	Dispatcher& operator=(const Dispatcher&)	= delete;

	void Subscribe(const eEvent aEventType, Subscriber* aSubscriber);
	void Unsubscribe(const eEvent aEventType, Subscriber* aSubscriber);
	void SendEvent(const Event& aEvent);

private:
	Dispatcher() = default;

	Subscribers_t m_subscribers;
};