#include <windows.h>
#include <gl/GL.h>
#pragma comment(lib, "opengl32.lib")

static constexpr int width = 100; 
static constexpr int height = 100;
static int rectX = 50;
static int rectY = 50;

HDC hdc{};
HGLRC hglrc{};

void Update()
{

}

void Render()
{
	glClearColor(0.7f,0.1f,0.3f,0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SwapBuffers(hdc);
}

bool InitOpengl(HWND hwnd)
{
	hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;   // 32 бита на цвет
	pfd.cDepthBits = 24;   // буфер глубины
	pfd.cStencilBits = 8;  // трафарет
	pfd.iLayerType = PFD_MAIN_PLANE;

	int format = ChoosePixelFormat(hdc, &pfd);
	if(!format) return false;

	if(!SetPixelFormat(hdc, format, &pfd)) return false;

	hglrc = wglCreateContext(hdc);
	if(!wglMakeCurrent(hdc, hglrc)) return false;

	return true;
}

void CleanupOpenGL(HWND hwnd)
{
	if(hglrc)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(hglrc);
		hglrc = nullptr;
	}
	if(hdc)
	{
		ReleaseDC(hwnd, hdc);
		hdc = nullptr;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/* [+] TODO: Add WM_PAINT to switch logic */
	/* [+] TODO: Add WM_KEYDOWN to switch	  */
	/* [-] TODO: Maybe use WM_SIZE(with static gloabal variables) and GetClientRect for easyer drawing images */
	/* [+] TODO: Make rectangle move just use of keyboard keys { *Use wm_keydown and another methods* }		  */
	/* [-] TODO: Create back-buffering!!! */

	switch(message)
	{
	case WM_CREATE:
		InitOpengl(hwnd);
		break;
	case WM_DESTROY:
		CleanupOpenGL(hwnd);
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN: // [-] TODO: Delete this and make Update function work
		switch (wParam)
		{
		case VK_LEFT: 
		{
			rectX -= 5;
			break;
		}
		case VK_RIGHT: 
		{
			rectX += 5;
			break;
		}
		case VK_UP: 
		{
			rectY -= 5;
			break; 
		}
		case VK_DOWN: 
		{
			rectY += 5;
			break; 
		}
		default: 
			break;
		}
	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}

constexpr wchar_t CLASS_NAME[] = L"Window";

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, 
	LPWSTR cmdLine, int cmdShow)
{
	HWND hwnd{};
	MSG msg{};
	WNDCLASSEX wc{};

	wc.hInstance = hInst;
	wc.lpszClassName = CLASS_NAME;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszMenuName = nullptr;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.cbSize = sizeof(WNDCLASSEX);

	if(!RegisterClassExW(&wc)) return 0;

	if(hwnd = CreateWindowExW(0,CLASS_NAME, L"MyFirstWindow", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, hInst, nullptr); !hwnd)
	{
		MessageBoxW(nullptr, L"Error on window creation", L"Error", MB_OK);
		return 1;
	}

	ShowWindow(hwnd, cmdShow);
	UpdateWindow(hwnd); //use for update window immidiately on start

	while(msg.message != WM_QUIT)
	{
		if(PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
		{	//[+] TODO: Add two methods to render and update game in free time
			Update();
			Render();
		}
	}
	return msg.wParam;
}
