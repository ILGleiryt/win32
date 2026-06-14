#include "Game.h"

void Game::Run()
{
	const char* version = (const char*)glGetString(GL_VERSION);
	const char* renderer = (const char*)glGetString(GL_RENDERER);
	const char* vendor = (const char*)glGetString(GL_VENDOR);

	std::cout << "OpenGL version: " << version << std::endl;
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "Vendor: " << vendor << std::endl;

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
			m_window.Resize(1024, 720);
		}

		if (!gl.MakeCurrent(m_window.Get_Handle()))
		{
			std::cerr << "MakeCurrent failed!" << std::endl;
			break;
		}
			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render here

		gl.SwapBuffers(m_window.Get_Handle());
		m_renderer.Update(dt);
		m_renderer.Render(dt);
		if (dt < 0.002f)
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
