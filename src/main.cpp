#include "core/Game.h"
#include <math/Vectors/Vector2.h>
// We need to manually create class Game and call its constructor 
// with parameters of window - name and size(width, height) > 0,
// object of Game class have only 1 public method Run() which start game loop

int main()
{
	constexpr Vector2 a(Vector2::One());
	const Vector2 b = a;
	std::cout << a << "\n" << b;
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