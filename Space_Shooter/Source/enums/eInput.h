#pragma once


namespace Input
{
	enum class eInputEvent
	{
		Fire, 
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		Pause,
		Exit,
		Count
	};


	enum class eInputState
	{
		Pressed, Down, Up
	};
}