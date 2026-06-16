#pragma once
#include "MyTypes.h"

#include <glad/gl.h>
#include <glad/wgl.h>
#pragma comment(lib, "opengl32.lib")
class OpenGL
{
public:
    OpenGL() : hglrc(nullptr), pixel_format(0) {};
    ~OpenGL() { Shutdown(); };
    bool Init(HWND hwnd) noexcept;
    bool MakeCurrent(HWND hwnd) const noexcept;
    void SwapBuffers(HWND hwnd) const noexcept;
    void Shutdown() noexcept;
private:
    HGLRC hglrc{};
    signedInt pixel_format{};
    static const PIXELFORMATDESCRIPTOR pfd;
};