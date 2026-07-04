#include "core/Game.h"
#include "utility/BMP_parser.h"
// We need to manually create class Game and call its constructor 
// with parameters of window - name and size(width, height) > 0,
// object of Game class have only 1 public method Run() which start game loop

int main()
{
	Game game;
	if (!game_init(&game, L"Game111", 640, 480)) return -1;
	BMPImage image = { 0 };
	if (bmp_load("../flo.bmp", &image)) puts("ok");
	game_gameloop(&game);
	game_shutdown(&game);
	bmp_free(&image);
	return 0;
}