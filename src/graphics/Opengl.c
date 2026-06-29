#include "graphics/Opengl.h"

//Glad doesnt load these 
#ifndef WGL_CONTEXT_MAJOR_VERSION_ARB
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB   0x2093
#define WGL_CONTEXT_FLAGS_ARB         0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB  0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB              0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB       0x0001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x0002
#endif

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);

static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 24, 8, 0,PFD_MAIN_PLANE, 0, 0, 0, 0 
};

bool gl_init(OpenGL* gl, HWND hwnd)
{
    if (!gl || !hwnd) return false;
    gl->dc = GetDC(hwnd);
    gl->hwnd = hwnd;

    gl->pixel_format = ChoosePixelFormat(gl->dc, &pfd);
    if (!gl->pixel_format || !SetPixelFormat(gl->dc, gl->pixel_format, &pfd))
    {
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
        return false;
    }

    HGLRC temp_rc = wglCreateContext(gl->dc);
    if (!temp_rc)
    {
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
        return false;
    }
    if (!wglMakeCurrent(gl->dc, temp_rc))
    {
        wglDeleteContext(temp_rc);
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
        return false;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (!gladLoaderLoadWGL(gl->dc) || !gladLoaderLoadGL())
    {
        wglDeleteContext(temp_rc);
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
        return false;
    }
    
    static const int attribs[] = {
       WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
       WGL_CONTEXT_MINOR_VERSION_ARB, 6,
       WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
       0
    };
    HGLRC new_rc = wglCreateContextAttribsARB ?
        wglCreateContextAttribsARB(gl->dc, NULL, attribs) : NULL;
    if (!new_rc)
        new_rc = wglCreateContext(gl->dc);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(temp_rc);

    if (!wglMakeCurrent(gl->dc, new_rc))
    {
        wglDeleteContext(new_rc);
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
        return false;
    }

    gl->hglrc = new_rc;
    glEnable(GL_DEPTH_TEST);
    return true;
}

bool gl_make_current(OpenGL* gl)
{
    if (!gl || !gl->dc || !gl->hglrc) return false;
    return wglMakeCurrent(gl->dc, gl->hglrc) == TRUE;
}
void gl_swap_buffers(OpenGL* gl)
{
    if (gl && gl->dc)
        SwapBuffers(gl->dc);
}
HDC get_HDC(OpenGL* gl)
{
    return gl ? gl->dc : NULL;
}
void gl_exit(OpenGL* gl)
{
    if (gl->hglrc)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(gl->hglrc);
        gl->hglrc = NULL;
    }
    if (gl->dc && gl->hwnd)
    {
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
    }
}