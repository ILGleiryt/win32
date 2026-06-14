#pragma once
#include <glad/gl.h>
#include <glad/wgl.h>
#pragma comment(lib, "opengl32.lib")

class OpenGL
{
public:
    OpenGL() : hglrc(nullptr), pixel_format(0) {};
    ~OpenGL() { Shutdown(); };
    bool Init(HWND hwnd);
    bool MakeCurrent(HWND hwnd) const;
    void SwapBuffers(HWND hwnd) const;
    void Shutdown();
    void* GetAnyGLFuncAddress(const char* name);
private:
    HDC hdc{ nullptr };
    HGLRC hglrc{};
    int pixel_format{};
    static const PIXELFORMATDESCRIPTOR pfd;
};