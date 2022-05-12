#pragma once
#include "Dispatcher.h"
#include "eInput.h"
#include "InputSubscriber.h"


class InputMapper
{
public:
	static InputMapper& GetInstance();

	InputMapper(const InputMapper&)				= delete;
	InputMapper& operator=(const InputMapper&)	= delete;

	void Update();
	void AddObserver();
	void RemoveObserver();


private:
	InputMapper() = default;

	/* - Methods - */
	void UpdateMouseInput();
	void UpdateKeyboardInput();
	void UpdateJoystickInput();
	void SendEvent(Input::eInputEvent aEvent);

	/* - Members - */
	std::array<std::vector<InputSubscriber*>, static_cast<int>(Input::eInputEvent::Count)> m_observers;
};

