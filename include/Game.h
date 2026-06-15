#pragma once
#include "Opengl.h"
#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

#include <chrono>
#include <thread>

class Game
{
private:
	OpenGL gl;
	Input m_input;
	Window m_window;
	Renderer m_renderer;

	bool running = true;
	std::chrono::steady_clock::time_point m_last_time;

public:
	Game(const winByte* wnd_title, const signedInt wnd_width, const signedInt wnd_height)
		: m_window(wnd_title, wnd_width, wnd_height)
	{
		m_renderer.Render();
		gl.Init(m_window.Get_Handle());
	};
	~Game()
	{
		gl.Shutdown();
		m_window.~Window();
	};
	void Run();
};
