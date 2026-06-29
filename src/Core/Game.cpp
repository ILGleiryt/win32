#include <stdio.h>
#include "core/Game.h"
#include <math/math.h>

Game::Game(const wchar_t* wnd_title, const int wnd_width, const int wnd_height)
	: m_window(wnd_title, wnd_width, wnd_height),
	m_renderer(&m_gl)
{
	if (!gl_init(&m_gl, m_window.Get_Handle()))
	{
		printf("Failed to initialize OpenGL!\n");
		running = false;
		return;
	}
	glViewport(0, 0, wnd_width, wnd_height);
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

		if (!m_window.ProcessSystemMessages()) 
		{
			running = false;
			break;
		}
		m_input.Update();
		if (m_input.IsKeyDown('E')) {
			m_window.Resize(512, 360);   
		}
		if (m_input.IsKeyDown('R')) {
			m_window.setFullScreen(true, true);
		}
		if (m_input.IsMouseKeyDown(MK_LBUTTON))
		{
			printf("left mouse clicked\n");
		}
		if (m_input.IsMouseKeyDown(MK_RBUTTON))
		{
			printf("right mouse clicked\n");
		}

		m_renderer.Update(dt);
		m_renderer.Render();
	}
}

void Game::Shutdown()
{
	running = false;
}
