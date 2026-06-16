#pragma once
#include "Window.h"
#include "Opengl.h"

class Renderer
{
private:
	Window* m_window{};
	OpenGL* m_opengl{};
public:
	Renderer(OpenGL* opengl, Window* window) : m_opengl(opengl), m_window(window)
	{
		if (m_opengl && m_window) {
			m_opengl->Init(m_window->Get_Handle());
			m_opengl->MakeCurrent(m_window->Get_Handle());
		}
	};
	~Renderer()
	{
		if (m_opengl)
			m_opengl->Shutdown();
	};
	void onResize(int width, int height) { glViewport(0, 0, width, height); }
	void Render();
	void Update(float dt);
};
