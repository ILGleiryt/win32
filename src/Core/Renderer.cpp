#include "Renderer.h"

void Renderer::onResize(int width, int height)
{
	m_opengl->MakeCurrent();
	glViewport(0, 0, width, height);
}

void Renderer::Render()
{
	if (!m_opengl->MakeCurrent()) return;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render here
	m_opengl->SwapBuffers();
}

void Renderer::Update(float dt)
{
}
