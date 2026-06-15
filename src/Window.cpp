#include "Window.h"
#include <iostream>

void Window::FullScreen(bool set_fullscreen, bool borderless) 
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
		m_windowStyle = GetWindowLong(Get_Handle(), GWL_STYLE);
		m_windowExStyle = GetWindowLong(Get_Handle(), GWL_EXSTYLE);
		//SetWindowPos(Get_Handle(), nullptr, 0, 0, fullWidth, fullHeight, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		if (borderless)
		{
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			SetWindowLongPtr(Get_Handle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
			SetWindowLongPtr(Get_Handle(), GWL_EXSTYLE, WS_EX_APPWINDOW);
			SetWindowPos(Get_Handle(), HWND_TOP, 0, 0, screenWidth, screenHeight,
				SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			UpdateWindow(Get_Handle());
			ShowWindow(Get_Handle(), SW_SHOW);
		}
		m_fullscreen = true;
	}
	else
	{
		SetWindowLongPtr(m_hwnd, GWL_STYLE, m_windowStyle);
		SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, m_windowExStyle);
		SetWindowPos(m_hwnd, nullptr, m_windowX, m_windowY,
			m_windowWidth, m_windowHeight,
			SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
		m_fullscreen = false;
	}
}

void Window::SizeWindow(HWND hwnd, signedInt clientWidth, signedInt clientHeight, float scale)
{
	signedInt physicWidth{ static_cast<signedInt>(clientWidth * scale) };
	signedInt physicHeight{ static_cast<signedInt>(clientHeight * scale) };
	ValidateWindowSize(physicWidth, physicHeight);
	RECT rc = { 0, 0, physicWidth, physicHeight };
	DWORD style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));
	DWORD exStyle = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_EXSTYLE));
	AdjustWindowRectEx(&rc, style, FALSE, exStyle);
	signedInt fullWidth = rc.right - rc.left;
	signedInt fullHeight = rc.bottom - rc.top;
	SetWindowPos(hwnd, nullptr, 0, 0, fullWidth, fullHeight, SWP_NOMOVE | SWP_NOZORDER);
}

Window::Window(const winByte* wnd_title, signedInt wnd_width, signedInt wnd_height)
	: m_width(wnd_width), m_height(wnd_height), hinstance(GetModuleHandleW(nullptr))
	{
		SetProcessDPIAware();
		ValidateWindowSize(wnd_width, wnd_height);

		WNDCLASSEX wc{ 0 };
		wc.hInstance = GetInstance();
		wc.lpszClassName = GetName();
		wc.lpfnWndProc = MyWndProc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hCursor = nullptr;
		wc.hIcon = nullptr;
		wc.hIconSm = nullptr;
		wc.lpszMenuName = nullptr;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		if (!RegisterClassExW(&wc)) throw std::runtime_error("Class creation error");

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
			nullptr, nullptr, GetInstance(), this); !m_hwnd)
		{
			throw std::runtime_error("Error on window creation");
		}

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);
		//FullScreen(true, true);
	}

	Window::~Window() 
	{
		if (m_hwnd) DestroyWindow(m_hwnd);
		UnregisterClassW(GetName(), GetInstance());
	};

	void Window::ValidateWindowSize(const signedInt wnd_width, const signedInt wnd_height) const
	{
		if (wnd_height <= 0 || wnd_width <= 0)
			throw std::invalid_argument("Bad window size");
	}

	LRESULT Window::MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* pWindow{ nullptr };

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
		case WM_DPICHANGED:
		{
			m_wndDPI = HIWORD(wParam);
			float scale = m_wndDPI / USER_DEFAULT_SCREEN_DPI;
			SizeWindow(hwnd, m_width, m_height, scale);
			break;
		}
		case WM_KEYDOWN:
			// onKeyPressed
			break;
		case WM_KEYUP:
			// onKeyReleased
			break;
		case WM_SYSKEYDOWN:
			break;
		case WM_SYSKEYUP:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
		{
			UINT new_sizeW = LOWORD(lParam);
			UINT new_sizeH = HIWORD(lParam);
			float scale = m_wndDPI / USER_DEFAULT_SCREEN_DPI;
			m_width = static_cast<signedInt>(new_sizeW / scale);
			m_height = static_cast<signedInt>(new_sizeH / scale);
			break;
		}
		case WM_ERASEBKGND:
			return TRUE;
		case WM_CHAR:
			// onKeyChar
			break;
		default:
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}
		return 0;
	}

	void Window::Resize(const signedInt width, const signedInt height)
	{
		if (m_fullscreen == true)
			FullScreen(false, true);

		ValidateWindowSize(width, height);
		SizeWindow(m_hwnd, width, height, m_wndDPI);
		m_width = width;
		m_height = height;
	}

	bool Window::ProcessSystemMessages() noexcept
	{
		MSG message;
		while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
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
		HDC hdc = GetDC(nullptr);
		int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
		ReleaseDC(nullptr, hdc);
		float scaleX = dpiX / static_cast<float>(USER_DEFAULT_SCREEN_DPI);
		return scaleX;
	}
