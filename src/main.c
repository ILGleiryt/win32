#include "core/Game.h"
#include "utility/BMP_parser.h"
#include "utility/readFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <utility/Win32Timer.h> 
// We need to manually create class Game and call its constructor 
// with parameters of window - name and size(width, height) > 0,
// object of Game struct have 2  functions gameloop(*game) which start game loop
// and shutdown(*game) which ends run of program

int main()
{
	timer_init();
	Game game;
	if (!game_init(&game, L"Game111", 640, 480)) return -1;
	BMPImage image = { 0 };
	if (bmp_load("img/flo.bmp", &image) == 0) printf("ok\n");

	SYSTEMTIME t = { 0 };
	GetLocalTime(&t);
	wprintf(L"Game open: %02d.%02d.%02d %2d:%02d:%02d\n",
		t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

	double start = timer_get_totaltime();
	game_gameloop(&game);
	game_shutdown(&game);
	double end = timer_get_totaltime();
	double duration = end - start;

	GetLocalTime(&t);
	wprintf(L"Game closed: %02d.%02d.%02d %2d:%02d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

	printf("Game has been running: %.3f seconds\n", duration);
	bmp_free(&image);

	return 0;
}