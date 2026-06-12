// use directx instead for easy development
#include <iostream>
#include "Game.h"

int main()
{
	try 
	{
		Game game;
		game.Run();

		return 0;
	}
	catch (const std::exception& e) 
	{
		MessageBoxA(nullptr, e.what(), "Fatal Error", MB_ICONERROR);
		return 1;
	}
}