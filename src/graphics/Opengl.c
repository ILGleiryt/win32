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
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);

//PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
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

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =// load wglCreateContextAttrib
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) // load wglSwapInterval
        wglGetProcAddress("wglSwapIntervalEXT");

    HGLRC new_rc = NULL;

    if (wglCreateContextAttribsARB) {
        static const int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 6,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        new_rc = wglCreateContextAttribsARB(gl->dc, NULL, attribs);
    }

    if (!new_rc) {
        if (wglCreateContextAttribsARB) {
            static const int attribs_fallback[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                0
            };
            new_rc = wglCreateContextAttribsARB(gl->dc, NULL, attribs_fallback);
        }
    }

    if (!new_rc) 
    {
        new_rc = wglCreateContext(gl->dc);
    }

    if (!new_rc) 
    {
        wglDeleteContext(temp_rc);
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
        return false;
    }

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

    if (!gladLoaderLoadWGL(gl->dc) || !gladLoaderLoadGL()) 
    {
        wglDeleteContext(new_rc);
        ReleaseDC(gl->hwnd, gl->dc);
        gl->dc = NULL;
        return false;
    }
    wglSwapIntervalEXT(-1); // this line cotrol vsync on opengl side 0 - off, 1 - on, -1 - automatic, -2 - render every 2 frame
    //glEnable(GL_DEPTH_TEST); // i dont need it on here i manually call it in gameloop
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
    if (!gl) return;

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