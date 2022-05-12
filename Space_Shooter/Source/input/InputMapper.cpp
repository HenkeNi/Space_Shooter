#include "pch.h"
#include "InputMapper.h"



InputMapper& InputMapper::GetInstance()
{
	static InputMapper instance;
	return instance;
}

void InputMapper::Update()
{
	UpdateMouseInput();
	UpdateKeyboardInput();
	UpdateJoystickInput();
}

void InputMapper::AddObserver()
{

}

void InputMapper::RemoveObserver()
{

}



void InputMapper::UpdateMouseInput()
{

}

void InputMapper::UpdateKeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
	}
}

void InputMapper::UpdateJoystickInput()
{

}


void InputMapper::SendEvent(Input::eInputEvent aEvent)
{
	for (auto observer : m_observers[static_cast<int>(aEvent)])
	{
		//observer->RecieveInputEvent(aEvent, 1.f); // FIX: 1,,,
	}
}