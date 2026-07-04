#ifndef RENDERER_H
#define RENDERER_H
#include "graphics/Opengl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Renderer {
	OpenGL* opengl;
} Renderer;

// TODO: this function should be call when window is resizing (unsupported yet)
void render_on_resize(OpenGL* gl, int width, int height);

// i dont know if its function needed i can render with interpolate time, maybe dt need for physics calls
void render_update(double dt);

// makes window current, pain and swap buffers, maybe its possiblt to divide into 2 functions
void render(OpenGL* gl);

#ifdef __cplusplus
}
#endif

#endif // RENDERER_H