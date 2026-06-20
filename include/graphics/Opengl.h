#pragma once
#include "utility/MyTypes.h"

#include "glad/gl.h"
#include "glad/wgl.h"
#pragma comment(lib, "opengl32.lib")
class OpenGL
{
public:
    OpenGL() : m_hglrc(nullptr), m_dc(nullptr), m_hwnd(nullptr) {};
    ~OpenGL() { Shutdown(); };
    bool Init(HWND hwnd) noexcept;
    bool MakeCurrent() const noexcept;
    void Shutdown() noexcept;
    void SwapBuffers() const noexcept;
    HDC GetHDC() const noexcept{ return m_dc; }
private:
    HWND m_hwnd;
    HDC m_dc{};
    HGLRC m_hglrc{};
    signedInt pixel_format{};
    static const PIXELFORMATDESCRIPTOR pfd;
};