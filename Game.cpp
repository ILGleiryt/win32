#include "Game.h"ererer

void Game::Run()
{
	while (running)
	{
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
		m_renderer.Update();
		m_renderer.Render();
	}
}
