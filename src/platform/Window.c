#include "platform/Window.h"
#include <stdlib.h>
#include <stdio.h>

static const wchar_t* WINDOW_CLASS_NAME = L"GameClass";
static const float DEFAULT_DPI = 96.0f;

static bool window_validate_size(int width, int height)
{
	if (width <= 0 || height <= 0)
	{
		MessageBoxExW(NULL, L"Wrong window size", L"Window size error", MB_OK | MB_ICONERROR, 0);
		return false;
	}
	return true;
}

static float get_dpi()
{
	HDC hdc = GetDC(NULL);
	int dpi_x = GetDeviceCaps(hdc, LOGPIXELSX);
	ReleaseDC(NULL, hdc);
	return dpi_x / DEFAULT_DPI;
}

static void size_window(HWND hwnd, int client_width, int client_height, float scale)
{
	int physic_width = (int)(client_width * scale);
	int physic_height = (int)(client_height * scale);

	if (!window_validate_size(physic_width, physic_height)) return;

	RECT rc = { 0, 0, physic_width, physic_height };
	DWORD style = (DWORD)GetWindowLongPtrW(hwnd, GWL_STYLE);
	DWORD ex_style = (DWORD)GetWindowLongPtrW(hwnd, GWL_EXSTYLE);

	AdjustWindowRectEx(&rc, style, FALSE, ex_style);

	int full_width = rc.right - rc.left;
	int full_height = rc.bottom - rc.top;

	SetWindowPos(hwnd, NULL, 0, 0, full_width, full_height, SWP_NOMOVE | SWP_NOZORDER);
}


bool window_init(Window* win, const wchar_t* name, int width, int height)
{
	SetProcessDPIAware();
	if (!win) return false;
	if (!window_validate_size(width, height)) return false;

	win->wnd_title = name;
	win->class_name = WINDOW_CLASS_NAME;
	win->width = width;
	win->height = height;
	win->hinstance = GetModuleHandleW(NULL);
	win->hwnd = NULL;
	win->fullscreen = false;
	win->dpi_scale = get_dpi();
	win->window_x = 0;
	win->window_y = 0;
	win->window_width = 0;
	win->window_height = 0;
	win->windowStyle = 0;
	win->windowExStyle = 0;

	WNDCLASSEX wc = { 0 };
	wc.hInstance = window_get_hinstance(win);
	wc.lpszClassName = window_get_classname(win);
	wc.lpfnWndProc = window_proc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // cs_owndc maybe dont needed, but before windows nt windows use 1 dc for all user windows, is not problem today
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	if (!RegisterClassExW(&wc))
	{
		MessageBoxExW(window_get_handle(win), L"Window doesnt create", L"Window create error", MB_OKCANCEL, 0);
		return false;
	}
	win->dpi_scale = get_dpi();
	int physicWidth = (int)(width * win->dpi_scale);
	int physicHeight = (int)(height * win->dpi_scale);

	RECT rc = { 0, 0, physicWidth, physicHeight };
	win->windowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	AdjustWindowRectEx(&rc, win->windowStyle, FALSE, 0);
	int windowWidth = rc.right - rc.left;
	int windowHeight = rc.bottom - rc.top;

	win->hwnd = CreateWindowExW(0, win->class_name, name, win->windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
		NULL, NULL, window_get_hinstance(win), win);

	if (!win->hwnd)
	{
		MessageBoxExW(window_get_handle(win), L"Window doesnt create", L"Window create error", MB_OKCANCEL, 0);
		return false;
	}

	ShowWindow(window_get_handle(win), SW_SHOW);
	UpdateWindow(window_get_handle(win));

	return true;
}


void window_shutdown(Window* win)
{
	if (!win) return;

	if (win->hwnd)
	{
		DestroyWindow(win->hwnd);
		win->hwnd = NULL;
	}

	UnregisterClassW(WINDOW_CLASS_NAME, win->hinstance);
}

void window_set_fullscreen(Window* win, bool set_fullscreen, bool borderless)
{
	if (!win) return;
	if (win->fullscreen == set_fullscreen) return;

	HWND hwnd = win->hwnd;

	if (set_fullscreen)
	{
		RECT rc;
		GetWindowRect(hwnd, &rc);
		win->window_x = rc.left;
		win->window_y = rc.top;
		win->window_width = rc.right - rc.left;
		win->window_height = rc.bottom - rc.top;
		win->windowStyle = (DWORD)GetWindowLongPtr(hwnd, GWL_STYLE);;
		win->windowExStyle = (DWORD)GetWindowLongPtr(hwnd, GWL_EXSTYLE);

		if (borderless)
		{
			HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi;
			mi.cbSize = sizeof(MONITORINFO);
			
			if (GetMonitorInfo(monitor, &mi))
			{
				int screenWidth = mi.rcMonitor.right - mi.rcMonitor.left;
				int screenHeight = mi.rcMonitor.bottom - mi.rcMonitor.top;
				int screenX = mi.rcMonitor.left;
				int screenY = mi.rcMonitor.top;
			
				SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
				SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW);
				SetWindowPos(hwnd, HWND_TOP,
					screenX, screenY, screenWidth, screenHeight,
					SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
				UpdateWindow(hwnd);
			}
		}
		else {
			ShowWindow(hwnd, SW_MAXIMIZE);// windowed fullscreen
		}

		win->fullscreen = true;
	}
	else
	{
		SetWindowLongPtr(hwnd, GWL_STYLE, win->windowStyle);
		SetWindowLongPtr(hwnd, GWL_EXSTYLE, win->windowExStyle);
		SetWindowPos(hwnd, NULL, win->window_x, win->window_y,
			win->window_width, win->window_height,
			SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
		UpdateWindow(hwnd);

		win->fullscreen = false;
	}
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	Window* win = NULL;

	if (message == WM_NCCREATE) {
		CREATESTRUCTW* create = (CREATESTRUCTW*)lParam;
		win = (Window*)create->lpCreateParams;
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)win);
	}
	else {
		win = (Window*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
	}

	if (!win) {
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}

	// Обработка сообщений
	switch (message) {
	case WM_KILLFOCUS:
		// Когда окно теряет фокус
		break;

	case WM_ACTIVATE:
		// Когда окно активируется/деактивируется
		break;

	case WM_ACTIVATEAPP:
		// При переключении между приложениями
		break;

	case WM_DPICHANGED: {
		win->dpi_scale = HIWORD(wParam) / DEFAULT_DPI;
		size_window(hwnd, win->width, win->height, win->dpi_scale);
		break;
	}

	case WM_KEYDOWN:
		// Обработка нажатия клавиш
		break;

	case WM_KEYUP:
		// Обработка отпускания клавиш
		break;

	case WM_SYSKEYDOWN:
		// Системные клавиши
		break;

	case WM_SYSKEYUP:
		// Отпускание системных клавиш
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE: {
		UINT new_width = LOWORD(lParam);
		UINT new_height = HIWORD(lParam);
		float scale = win->dpi_scale;

		win->width = (int)(new_width / scale);
		win->height = (int)(new_height / scale);
		break;
	}

	case WM_ERASEBKGND:
		// Предотвращаем мерцание при ресайзе
		return TRUE;

	case WM_CHAR:
		// Ввод символов
		break;

	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}

	return 0;
}

bool window_process_system_msg(Window* win) {
	(void)win;

	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return true;
}

void window_resize(Window* win, int width, int height) {
	if (!win) return;

	if (win->fullscreen) {
		window_set_fullscreen(win, false, false);
	}

	if (!window_validate_size(width, height)) return;

	win->width = width;
	win->height = height;

	size_window(win->hwnd, width, height, win->dpi_scale);
}

const wchar_t* window_get_classname(const Window* win)
{
	return win ? win->class_name : L"";
}
const wchar_t* window_get_wndtitle(const Window* win)
{
	return win ? win->wnd_title : L"";
}
HINSTANCE window_get_hinstance(const Window* win)
{
	return win ? win->hinstance : NULL;
}
int window_get_height(const Window* win)
{
	return win ? win->height : 0;
}
int window_get_width(const Window* win)
{
	return win ? win->width : 0;
}
HWND window_get_handle(const Window* win)
{
	return win ? win->hwnd : NULL;
}
