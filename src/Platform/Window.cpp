#include "platform/Window.h"

void Window::setFullScreen(bool set_fullscreen, bool borderless) noexcept
{
	if (m_fullscreen == set_fullscreen) return;

	if (set_fullscreen)
	{
		RECT rc;
		GetWindowRect(Get_Handle(), &rc);
		m_windowX = rc.left;
		m_windowY = rc.top;
		m_windowWidth = rc.right - rc.left;
		m_windowHeight = rc.bottom - rc.top;
		m_windowStyle = static_cast<DWORD>(GetWindowLongPtr(Get_Handle(), GWL_STYLE));
		m_windowExStyle = static_cast<DWORD>(GetWindowLongPtr(Get_Handle(), GWL_EXSTYLE));

		if (borderless) //borderless fullscreen
		{
			HMONITOR monitor = MonitorFromWindow(Get_Handle(), MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi{};
			mi.cbSize = sizeof(MONITORINFO);

			if (GetMonitorInfo(monitor, &mi))
			{
				int screenWidth = mi.rcMonitor.right - mi.rcMonitor.left;
				int screenHeight = mi.rcMonitor.bottom - mi.rcMonitor.top;
				int screenX = mi.rcMonitor.left;
				int screenY = mi.rcMonitor.top;

				SetWindowLongPtr(Get_Handle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
				SetWindowLongPtr(Get_Handle(), GWL_EXSTYLE, WS_EX_APPWINDOW);
				SetWindowPos(Get_Handle(), HWND_TOP,
					screenX, screenY, screenWidth, screenHeight,
					SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
				UpdateWindow(Get_Handle());
			}
		}
		else 
		{
			ShowWindow(Get_Handle(), SW_MAXIMIZE);// windowed fullscreen
		}

		m_fullscreen = true;
	}
	else
	{
		SetWindowLongPtr(m_hwnd, GWL_STYLE, m_windowStyle);
		SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, m_windowExStyle);
		SetWindowPos(m_hwnd, NULL, m_windowX, m_windowY,
			m_windowWidth, m_windowHeight,
			SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
		UpdateWindow(Get_Handle());

		m_fullscreen = false;
	}
}

void Window::SizeWindow(HWND hwnd, int clientWidth, int clientHeight, float scale) noexcept
{
	int physicWidth{ static_cast<int>(clientWidth * scale) };
	int physicHeight{ static_cast<int>(clientHeight * scale) };
	ValidateWindowSize(physicWidth, physicHeight);
	RECT rc = { 0, 0, physicWidth, physicHeight };
	DWORD style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));
	DWORD exStyle = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_EXSTYLE));
	AdjustWindowRectEx(&rc, style, FALSE, exStyle);
	int fullWidth = rc.right - rc.left;
	int fullHeight = rc.bottom - rc.top;
	SetWindowPos(hwnd, NULL, 0, 0, fullWidth, fullHeight, SWP_NOMOVE | SWP_NOZORDER);
}

Window::Window(const wchar_t* wnd_title, int wnd_width, int wnd_height)
	: m_width(wnd_width), m_height(wnd_height), hinstance(GetModuleHandleW(NULL))
	{
		SetProcessDPIAware();
		ValidateWindowSize(wnd_width, wnd_height);

		WNDCLASSEX wc = {0};
		wc.hInstance = GetInstance();
		wc.lpszClassName = GetName();
		wc.lpfnWndProc = MyWndProc;
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
			MessageBoxExW(m_hwnd, L"Window doesnt create", L"Window create error", MB_OKCANCEL, 0);
			exit(-1);
		}

		m_wndDPI = GetDPI_X();
		int physicWidth = static_cast<int>(wnd_width * m_wndDPI);
		int physicHeight = static_cast<int>(wnd_height * m_wndDPI);
		RECT rc = { 0, 0, physicWidth, physicHeight };
		m_windowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
		AdjustWindowRectEx(&rc, m_windowStyle, FALSE, 0);
		int windowWidth = rc.right - rc.left;
		int windowHeight = rc.bottom - rc.top;

		if (m_hwnd = CreateWindowExW(0, GetName(), wnd_title, m_windowStyle,
			CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
			NULL, NULL, GetInstance(), this); !m_hwnd)
		{ 
			MessageBoxExW(m_hwnd, L"Window doesnt create", L"Window create error", MB_OKCANCEL, 0);
			exit(-1);
		}

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);
	}

	Window::~Window() 
	{
		if (m_hwnd) DestroyWindow(m_hwnd);
		UnregisterClassW(GetName(), GetInstance());
	};

	void Window::ValidateWindowSize(const int wnd_width, const int wnd_height) const noexcept
	{
		if (wnd_height <= 0 || wnd_width <= 0)
			MessageBoxExW(m_hwnd, L"Wrong window size", L"window size error", MB_OKCANCEL, 0);
	}

	LRESULT Window::MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* pWindow{ NULL };

		if (message == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			pWindow = static_cast<Window*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		}
		else 
			pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		
		if (pWindow) 
			return pWindow->HandleMessage(hwnd,message, wParam, lParam);
		else 
			return DefWindowProcW(hwnd, message, wParam, lParam);
	}

	LRESULT Window::HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_KILLFOCUS:
			// when winidow lost focus block keyboard input
			break;
		case WM_ACTIVATE:
			// if game active get 100% to render it, otherwise only minimal fps 
			break;
		case WM_ACTIVATEAPP:
			// same as activate, but need check documentation
			break;
		case WM_DPICHANGED:
		{
			m_wndDPI = HIWORD(wParam); 
			float scale = m_wndDPI / USER_DEFAULT_SCREEN_DPI;
			SizeWindow(hwnd, m_width, m_height, scale);
			// maybe properly code this 
			break;
		}
		case WM_KEYDOWN:
			// onKeyPressed
			// wparam - vk_code, lparam - previous state, 0 The previous key state. The value is 1 if the key is down before the message is sent, or it is zero if the key is up.
			break;
		case WM_KEYUP:
			// onKeyReleased
			break;
		case WM_SYSKEYDOWN:
			// command keys such as alt, shift, F1-12?
			break;
		case WM_SYSKEYUP:
			// on syskey up
			break;
		case WM_DESTROY:
			// WM_CLOSE doesnt need because app have only 0 window and after quit delete yourself
			PostQuitMessage(0);
			break;
		case WM_SIZE:
		{
			// maybe add wm_sizing case? documentation on it so bad
			UINT new_width = LOWORD(lParam);
			UINT new_height = HIWORD(lParam);
			float scale = m_wndDPI / USER_DEFAULT_SCREEN_DPI;
			m_width = static_cast<int>(new_width / scale);
			m_height = static_cast<int>(new_height / scale);
			break;
		}
		case WM_ERASEBKGND:
			// background repaint on sizing
			return TRUE;
		case WM_CHAR:
			// onKeyChar
			break;
		case WM_CLOSE: //send when app is should destroy, before hwnd and dc deleted for properly closing
			//mb put here callback for delete opengl context
			break;
		default:
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}
		return 0;
	}

	void Window::Resize(const int width, const int height) noexcept
	{
		if (m_fullscreen == true)
			setFullScreen(false, true);

		ValidateWindowSize(width, height);
		SizeWindow(m_hwnd, width, height, m_wndDPI);
		m_width = width;
		m_height = height;
	}

	bool Window::ProcessSystemMessages() noexcept
	{
		MSG message;
		while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				return false;

			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
		return true;
	}

	float Window::GetDPI_X() noexcept
	{
		HDC hdc = GetDC(NULL);
		int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
		ReleaseDC(NULL, hdc);
		float scaleX = dpiX / static_cast<float>(USER_DEFAULT_SCREEN_DPI);
		return scaleX;
	}
