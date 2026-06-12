#pragma once
#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

#include <chrono>
#include <thread>

class Game
{
private:
	Input m_input;
	Window m_window{ L"Game", 800, 600 };
	Renderer m_renderer;
	bool running = true;
	std::chrono::steady_clock::time_point m_last_time;
public:
	void Run();
};
