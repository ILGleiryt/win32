#include "Game.h"

int main()
{
	try 
	{
		Game game(L"Game111", 300, 300);
		game.Run();

		return 0;
	}
	catch (const std::exception& e) 
	{
		MessageBoxA(nullptr, e.what(), "Fatal Error", MB_ICONERROR);
		return 1;
	}
}