#pragma once
#include "Input.h"
#include "Window.h"
#include "Renderer.h"

class Game
{
private:
	Input m_input;
	Window m_window{ L"Game", 800, 600 };
	Renderer m_renderer;
	bool running = true;
public:
	void Run();
};
