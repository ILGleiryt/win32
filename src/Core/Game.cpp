#include <stdio.h>
#include "core/Game.h"
#include <math/math.h>

Game::Game(const wchar_t* wnd_title, const int wnd_width, const int wnd_height)
	: m_renderer(&m_gl)
{
	window_init(&m_window, wnd_title, wnd_width, wnd_height);
	if (!gl_init(&m_gl, window_get_handle(&m_window)))
	{
		printf("Failed to initialize OpenGL!\n");
		running = false;
		return;
	}
	glViewport(0, 0, wnd_width, wnd_height);
	input_init(&m_input);
	running = true;
}

Game::~Game()
{
	Shutdown();
}

void Game::Run()
{
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));

	if (!gl_make_current(&m_gl))
	{
		printf("MakeCurrent failed!\n");
		return;
	}
	
	m_last_time = std::chrono::steady_clock::now();
	while (running)
	{
		auto now = std::chrono::steady_clock::now();
		float dt = std::chrono::duration<float>(now - m_last_time).count();
		m_last_time = now;

		if (!window_process_system_msg(&m_window)) 
		{
			running = false;
			break;
		}
		input_update(&m_input);
		if (input_is_key_down(&m_input, 'E')) {
			window_resize(&m_window, 512, 360);   
		}
		if (input_is_key_down(&m_input, 'R')) {
			window_set_fullscreen(&m_window, true, true);
		}
		if (input_is_key_down(&m_input, MK_LBUTTON))
		{
			printf("left mouse clicked\n");
		}
		if (input_is_key_down(&m_input, MK_RBUTTON))
		{
			printf("right mouse clicked\n");
		}

		render_update(dt);
		render(&m_gl);
	}
}

void Game::Shutdown()
{
	running = false;
}
