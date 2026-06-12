#include "Game.h"

void Game::Run()
{
	m_last_time = std::chrono::steady_clock::now();
	while (running)
	{
		auto now = std::chrono::steady_clock::now();
		float dt = std::chrono::duration<float>(now - m_last_time).count();
		m_last_time = now;
		//std::cout << "fps: " << 1000 / dt << "\n";
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
			m_window.Resize(1024, 720);
		}
		m_renderer.Update(dt);
		m_renderer.Render(dt);
		if (dt < 0.002f)
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
