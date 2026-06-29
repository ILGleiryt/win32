#ifndef GAME_H
#define GAME_H

#include "graphics/Opengl.h"
#include "core/Input.h"
#include "core/Renderer.h"
#include "platform/Window.h"
#include <iostream> //<stdio>?

#include <chrono>
#include <stdbool.h>
#include <time.h> // <time>?

// - TODO OpenglRender, GUI, Physics(aabb and windows corner), mouse movement with GetKeyPos and getclientrect
// - TODO Window -> windows_abs.h && Window -> linux_abs.h
// - TODO  X11 linux api, xlib | xcb(async new)
// - TODO Create Opengl abstarction for create windows/linux context
// - INPUT.h TODO >> Delete all GetAsyncKey and catch user input in window procedure in Windod.cpp
// WM_KEYDOWN etc Input singleton??
// Possibly create option to create custom cursor and animation for him
typedef enum GameState // struct or class type added in c++11 and provide namespace for enum usage -> int a = GameState::INTRO;
{
	INTRO, MAIN_MENU, GAME, PAUSE, WIN, LOSE, ENDING, // 	syntax to use [logic condition([expression] [operator]  
	//(this true type is int by default )GameState::GAME)];
} GameState;

class Game
{
private:
	OpenGL m_gl;
	Window m_window;
	Renderer m_renderer;
	Input m_input;

	bool running;
	std::chrono::steady_clock::time_point m_last_time;

public:

	Game(const wchar_t* wnd_title, const int wnd_width, const int wnd_height);
	~Game();

	void Run();
	void Shutdown();
};
#endif // GAME_H