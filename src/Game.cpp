#include "Game.h"
#include <math/math.h>

void Game::Run()
{
	Vector2 a = -Vector2(1.f, 3.f);
	Vector3 b = Vector3(13.f,3.f, 5.f);
	Vector3 c = Vector3(1.f, 1.f, 0.f) + b;
	Vector4 d = Vector4::Zero();
	std::cout << c << "\n" << d;

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

	if (!m_gl.MakeCurrent())
	{
		std::cerr << "MakeCurrent failed!" << std::endl;
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
			std::cout << "left mouse clicked";
		}
		if (m_input.IsMouseKeyDown(MK_RBUTTON))
		{
			std::cout << "right mouse clicked";
		}

		m_renderer.Update(dt);
		m_renderer.Render();
	}
}