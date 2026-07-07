#include "core/Game.h"
#include "utility/BMP_parser.h"
#include "utility/readFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// We need to manually create class Game and call its constructor 
// with parameters of window - name and size(width, height) > 0,
// object of Game struct have 2  functions gameloop(*game) which start game loop
// and shutdown(*game) which ends run of program

int main()
{


	Game game;
	if (!game_init(&game, L"Game111", 640, 480)) return -1;
	BMPImage image = { 0 };
	if (bmp_load("../flo.bmp", &image) == 0) printf("ok\n");

	ULONGLONG start = GetTickCount64();
	SYSTEMTIME t = { 0 };
	GetLocalTime(&t);
	wprintf(L"Game open: %02d.%02d.%02d %2d:%02d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

	game_gameloop(&game);
	game_shutdown(&game);

	GetLocalTime(&t);
	wprintf(L"Game closed: %02d.%02d.%02d %2d:%02d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

	ULONGLONG end = GetTickCount64();
	ULONGLONG game_duration = end - start;
	printf("Game has been running: %.2f seconds\n", game_duration / 1000.0);
	bmp_free(&image);

	return 0;
}