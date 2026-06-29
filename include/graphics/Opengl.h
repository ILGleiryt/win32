#ifndef OPENGL_H
#define OPENGL_H

#include <Windows.h>
#include <stdbool.h>

#include "glad/gl.h"
#include "glad/wgl.h"
#pragma comment(lib, "opengl32.lib")

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenGL {
    HWND hwnd;
    HDC dc;
    HGLRC hglrc;
    int pixel_format;
} OpenGL;

bool gl_init(OpenGL* gl, HWND hwnd);
bool gl_make_current(OpenGL* gl);
void gl_exit(OpenGL* gl);
void gl_swap_buffers(OpenGL* gl);
HDC get_HDC(OpenGL* gl);

#ifdef __cplusplus
}
#endif

#endif // OPENGL_H