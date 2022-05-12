#pragma once
#include "eInput.h"


class InputSubscriber
{
public:
	virtual void RecieveInputEvent(const Input::eInputEvent aInputEvent, const Input::eInputState, const float aValue) = 0;
};