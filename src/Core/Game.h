#ifndef GAME_H
#define GAME_H

#include "graphics/Opengl.h"
#include "Input.h"
#include "Renderer.h"
#include "platform/win32/Win32Window.h"

#include <stdbool.h>
#include <time.h>

// - TODO OpenglRender, GUI, Physics(aabb and windows corner), mouse movement with GetKeyPos and getclientrect
// - TODO Window -> windows_abs.h && Window -> linux_abs.h
// - TODO  X11 linux api, xlib | xcb(async new)
// - TODO Create Opengl abstarction for create windows/linux context
// - INPUT.h TODO >> Delete all GetAsyncKey and catch user input in window procedure in Windod.cpp
// Possibly create option to create custom cursor and animation for him
// TODO: Create helper structure to initialize user window width, height and properly find apsect ratio of usr monitor

#ifdef __cplusplus
extern "C" {
#endif

typedef enum GameState
{
	STATE_INTRO, STATE_MAIN_MENU, STATE_SETTINGS, STATE_GAME, STATE_PAUSE, STATE_WIN, STATE_LOSE, STATE_CLOSE,
} GameState;

typedef struct Game {
	Renderer renderer;
	OpenGL opengl;
	Window window;
	Input input;
	bool running;
} Game;

bool game_init(Game* game,  const wchar_t* wnd_title, const int wnd_width, const int wnd_height);
void game_shutdown(Game* game);
void game_gameloop(Game* game);

#ifdef __cplusplus
}
#endif

#endif // GAME_H