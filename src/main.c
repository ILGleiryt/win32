#include "../dependencies/miniaudio.h"
#include "utility/BMP_parser.h"
#include <utility/Win32Timer.h>
#include "utility/readFile.h"
#include "core/Game.h"
#include <stdlib.h>
#include <stdio.h>
// We need to manually create class Game and call its constructor 
// with parameters of window - name and size(width, height) > 0,
// object of Game struct have 2  functions gameloop(*game) which start game loop
// and shutdown(*game) which ends run of program

void virt_console_init()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(handle, &mode);
	mode = ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
	if (!SetConsoleMode(handle, mode))
	{
		DWORD errorCode = GetLastError();

		char buffer[256];
		if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorCode,
			0, buffer, sizeof(buffer), NULL)) 
		{
			printf("unable set console mode: %s", buffer);
		}
		return;
	}
}

int main()
{
	virt_console_init();

	printf("\033[31mКрасный\033[0m\n");
	printf("\033[1;33mЖирный жёлтый\033[0m\n");
	printf("\033[41mЧёрный на красном фоне\033[0m\n");
	printf("\033[38;5;196m256-цветов\033[0m\n");
	printf("\033[38;2;255;128;0mTrue Color\033[0m\n");

	ma_result result;
	ma_engine engine;
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		return result; 
	}
	ma_engine_play_sound(&engine, "../../money.wav", NULL);

	timer_init();
	Game game;
	if (!game_init(&game, L"Game111", 640, 480)) return -1;
	BMPImage image = { 0 };
	if (bmp_load("img/flo.bmp", &image) == 0) printf("ok\n");

	SYSTEMTIME t = { 0 };
	GetLocalTime(&t);
	printf("Game open: %02d.%02d.%02d %2d:%02d:%02d, line %d, file %s\n",
		t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond,
		__LINE__, __FILE__);

	double start = timer_get_totaltime();
	game_gameloop(&game);
	game_shutdown(&game);
	double end = timer_get_totaltime();
	double duration = end - start;

	GetLocalTime(&t);
	printf("Game closed: %02d.%02d.%02d %2d:%02d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

	printf("Game has been running: %.3f seconds\n", duration);
	bmp_free(&image);
	ma_engine_uninit(&engine);
	return 0;
}