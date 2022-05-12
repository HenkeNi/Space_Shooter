#include "pch.h"
#include "Game.h"


int main()
{
	try
	{
		Game game;
		game.Run();
	}
	catch (...)
	{
		std::cerr << "[Error] Unexpected termination... [/Error]\n";
	}
	return 0;
}