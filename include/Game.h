#pragma once
#include "Opengl.h"
#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

#include <chrono>
#include <thread>

// - TODO OpenglRender, GUI, Physics(aabb and windows corner), mouse movement with GetKeyPos and getclientrect
// - TODO Window -> windows_abs.h && Window -> linux_abs.h
// - TODO  X11 linux api, xlib | xcb(async new)
// - TODO Create Opengl abstarction for create windows/linux context
// - INPUT.h TODO >> Delete all GetAsyncKey and catch user input in window procedure in Windod.cpp
// WM_KEYDOWN e.g Input singleton??
 
enum struct GameState
{
	INTRO, MAIN_MENU, GAME, PAUSE, WIN, LOSE, ENDING, // 	syntax to use [logic condition([expression] [operator]  
	//(this true type is int by default )GameState::GAME)];
};

class Game
{
private:
	OpenGL m_gl;
	Window m_window;
	Renderer m_renderer;
	Input m_input;

	bool running = true;
	std::chrono::steady_clock::time_point m_last_time;

public:

	Game(const winByte* wnd_title, const signedInt wnd_width, const signedInt wnd_height)
		: m_gl(), m_window(wnd_title, wnd_width, wnd_height), m_renderer(&m_gl)
	{
		m_gl.Init(m_window.Get_Handle());
		glViewport(0, 0, wnd_width, wnd_height);
	};
	~Game() = default;
	void Run();
};
