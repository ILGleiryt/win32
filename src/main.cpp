#include "core/Game.h"
// We need to manually create class Game and call its constructor 
// with parameters of window - name and size(width, height) > 0,
// object of Game class have only 1 public method Run() which start game loop

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