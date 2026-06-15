#include "Opengl.h"

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

bool OpenGL::Init(HWND hwnd) noexcept
{
    HDC hdc;
    if (hdc = GetDC(hwnd); !hdc) return false;

    pixel_format = ChoosePixelFormat(hdc, &pfd);
    if (!pixel_format || !SetPixelFormat(hdc, pixel_format, &pfd))
    {
        ReleaseDC(hwnd, hdc);
        return false;
    }

    HGLRC temp_rc = wglCreateContext(hdc);
    if (!temp_rc)
    {
        ReleaseDC(hwnd, hdc);
        return false;
    }
    if (!wglMakeCurrent(hdc, temp_rc)) 
    {
        wglDeleteContext(temp_rc);
        ReleaseDC(hwnd, hdc);
        return false;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (!gladLoaderLoadWGL(hdc) || !gladLoaderLoadGL())
    {
        wglDeleteContext(temp_rc);
        ReleaseDC(hwnd, hdc);
        return false;
    }
    
    signedInt attribs[] = {
       WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
       WGL_CONTEXT_MINOR_VERSION_ARB, 6,
       WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
       0
    };
    HGLRC new_rc = wglCreateContextAttribsARB ?
        wglCreateContextAttribsARB(hdc, nullptr, attribs) : nullptr;
    if (!new_rc)
        new_rc = wglCreateContext(hdc);

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(temp_rc);

    if (!wglMakeCurrent(hdc, new_rc)) 
    {
        wglDeleteContext(new_rc);
        ReleaseDC(hwnd, hdc);
        return false;
    }

    hglrc = new_rc;
    ReleaseDC(hwnd, hdc);
    glEnable(GL_DEPTH_TEST);
    return true;
}

bool OpenGL::MakeCurrent(HWND hwnd) const noexcept
{
    HDC hdc = GetDC(hwnd);
    BOOL result = wglMakeCurrent(hdc, hglrc);
    ReleaseDC(hwnd, hdc);
    return result;
}

void OpenGL::SwapBuffers(HWND hwnd) const noexcept
{
    HDC hdc = GetDC(hwnd);
    ::SwapBuffers(hdc);
    ReleaseDC(hwnd, hdc);
}

void OpenGL::Shutdown() noexcept
{
    if (hglrc)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(hglrc);
        hglrc = nullptr;
    }
}

const PIXELFORMATDESCRIPTOR OpenGL::pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    24,        // depth buffer
    8,         // stencil buffer
    0,
    PFD_MAIN_PLANE, 0, 0, 0, 0
};
