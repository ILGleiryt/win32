#ifndef RENDERER_H
#define RENDERER_H
#include "../graphics/Opengl.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct Renderer {
	OpenGL* opengl;
} Renderer;

void render_on_resize(OpenGL* gl, int width, int height);
void render_update(float dt);
void render(OpenGL* gl);

#ifdef __cplusplus
}
#endif

#endif // RENDERER_H