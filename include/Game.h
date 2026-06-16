#pragma once
#include "Opengl.h"
#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

#include <chrono>
#include <thread>

// OpenglRender, GUI, Physics(aabb and windows corner),
// Input singleton?? Window -> windows_abs.h && window -> linux_abs.h


// - TODO  X11 linux api, xlib | xcb(async new)
// - TODO Create Opengl abstarction for create windows/linux context

enum struct GameState
{
	INTRO, MAIN_MENU, GAME, PAUSE, WIN, LOSE, ENDING, // 	syntax to use [logic condition([expression] [operator] GameState::GAME)];
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
		: m_gl(), m_window(wnd_title, wnd_width, wnd_height), m_renderer(&m_gl, &m_window)
	{
		//gl.Init(m_window.Get_Handle());
	};
	~Game() = default;
	void Run();
};
