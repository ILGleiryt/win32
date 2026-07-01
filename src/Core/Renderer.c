#include "core/Renderer.h"

void render_on_resize(OpenGL* gl, int width, int height)
{
	if (!gl) return;
	gl_make_current(gl);
	glViewport(0, 0, width, height);
}

void render(OpenGL* gl)
{
	if (!gl) return;
	gl_make_current(gl);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render here
	gl_swap_buffers(gl);
}

void render_update(float dt)
{
}
