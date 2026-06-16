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
    m_dc = GetDC(hwnd);
    m_hwnd = hwnd;
    if (!m_dc) return false;

    pixel_format = ChoosePixelFormat(m_dc, &pfd);
    if (!pixel_format || !SetPixelFormat(m_dc, pixel_format, &pfd))
    {
        ReleaseDC(m_hwnd, m_dc);
        m_dc = nullptr;
        return false;
    }

    HGLRC temp_rc = wglCreateContext(m_dc);
    if (!temp_rc)
    {
        ReleaseDC(m_hwnd, m_dc);
        m_dc = nullptr;
        return false;
    }
    if (!wglMakeCurrent(m_dc, temp_rc))
    {
        wglDeleteContext(temp_rc);
        ReleaseDC(m_hwnd, m_dc);
        m_dc = nullptr;
        return false;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (!gladLoaderLoadWGL(m_dc) || !gladLoaderLoadGL())
    {
        wglDeleteContext(temp_rc);
        ReleaseDC(m_hwnd, m_dc);
        m_dc = nullptr;
        return false;
    }
    
    signedInt attribs[] = {
       WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
       WGL_CONTEXT_MINOR_VERSION_ARB, 6,
       WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
       0
    };
    HGLRC new_rc = wglCreateContextAttribsARB ?
        wglCreateContextAttribsARB(m_dc, nullptr, attribs) : nullptr;
    if (!new_rc)
        new_rc = wglCreateContext(m_dc);

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(temp_rc);

    if (!wglMakeCurrent(m_dc, new_rc))
    {
        wglDeleteContext(new_rc);
        ReleaseDC(m_hwnd, m_dc);
        m_dc = nullptr;
        return false;
    }

    m_hglrc = new_rc;
    glEnable(GL_DEPTH_TEST);
    return true;
}

bool OpenGL::MakeCurrent() const noexcept
{
    if (!m_dc || !m_hglrc) return false;
    return wglMakeCurrent(m_dc, m_hglrc) == TRUE;
}
void OpenGL::SwapBuffers() const noexcept
{
    ::SwapBuffers(m_dc);
}
void OpenGL::Shutdown() noexcept
{
    if (m_hglrc)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_hglrc);
        m_hglrc = nullptr;
    }
    if (m_dc && m_hwnd)
    {
        ReleaseDC(m_hwnd, m_dc);
        m_dc = nullptr;
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
