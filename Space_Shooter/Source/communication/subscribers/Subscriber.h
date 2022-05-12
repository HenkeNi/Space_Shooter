#pragma once
#include "Event.h"

class Subscriber
{
public:
	virtual void Recieve(const Event& aEvent) = 0;
};