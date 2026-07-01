#include "core/Game.h"
// We need to manually create class Game and call its constructor 
// with parameters of window - name and size(width, height) > 0,
// object of Game class have only 1 public method Run() which start game loop

int main()
{
	Game game;
	if (!game_init(&game, L"Game111", 450, 450)) return -1;
	game_gameloop(&game);
	game_shutdown(&game);

	return 0;
}