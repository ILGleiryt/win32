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

	//render here
	gl_swap_buffers(gl);
}

void render_update(double dt)
{
}
