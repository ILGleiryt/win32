#include "Window.h"

void Window::SizeWindow(HWND hwnd, signedInt clientWidth, signedInt clientHeight) 
{
	ValidateWindowSize(clientWidth, clientHeight);
	RECT rc = { 0, 0, clientWidth, clientHeight };
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	DWORD exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	AdjustWindowRectEx(&rc, style, FALSE, exStyle);
	signedInt fullWidth = rc.right - rc.left;
	signedInt fullHeight = rc.bottom - rc.top;
	SetWindowPos(hwnd, nullptr, 0, 0, fullWidth, fullHeight, SWP_NOMOVE | SWP_NOZORDER);
}

Window::Window(const winByte* wnd_title, signedInt wnd_width, signedInt wnd_height)
	: m_width(wnd_width), m_height(wnd_height), hinstance(GetModuleHandleW(nullptr))
	{
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

		if (m_hwnd = CreateWindowExW(0, GetName(), wnd_title, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			CW_USEDEFAULT, CW_USEDEFAULT, wnd_width, wnd_height,
			nullptr, nullptr, GetInstance(), this); !m_hwnd)
		{
			throw std::runtime_error("Error on window creation");
		}

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);
	}

	Window::~Window() 
	{
		if (m_hwnd) DestroyWindow(m_hwnd);
		UnregisterClassW(GetName(), GetInstance());
	};

	HINSTANCE Window::GetInstance() const noexcept
	{
		return hinstance;
	}

	std::int32_t Window::GetWidth() const noexcept { return m_width; }
	std::int32_t Window::GetHeight() const noexcept { return m_height; }

	void Window::ValidateWindowSize(signedInt wnd_width, signedInt wnd_height) const
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
			m_width = LOWORD(lParam);
			m_height = HIWORD(lParam);
			break;
		case WM_CHAR:
			// onKeyChar
			break;
		case WM_KILLFOCUS:
			// when winidow lost focus block keyboard input
			break;
		default:
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}
		return 0;
	}

	void Window::Resize(signedInt width, signedInt height)
	{
		ValidateWindowSize(width, height);
		SizeWindow(m_hwnd, width, height);
		m_width = width;
		m_height = height;
	}

	bool Window::ProcessSystemMessages()
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

	const winByte* Window::GetName() const noexcept
	{
		return wnd_name;
	}
