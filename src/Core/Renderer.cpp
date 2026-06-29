#include "core/Renderer.h"

Renderer::Renderer(OpenGL* opengl)
	: m_opengl(opengl) {
}

void Renderer::onResize(int width, int height)
{
	if (!m_opengl) return;
	gl_make_current(m_opengl);
	glViewport(0, 0, width, height);
}

void Renderer::Render()
{
	if (!m_opengl) return;
	gl_make_current(m_opengl);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render here
	gl_swap_buffers(m_opengl);
}

void Renderer::Update(float dt)
{
}
