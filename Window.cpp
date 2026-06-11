#include "Window.h"

void Window::SizeWindow(HWND hwnd, int clientWidth, int clientHeight) {
	ValidateWindowSize(clientWidth, clientHeight);
	RECT rc = { 0, 0, clientWidth, clientHeight };
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	DWORD exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	AdjustWindowRectEx(&rc, style, FALSE, exStyle);
	int fullWidth = rc.right - rc.left;
	int fullHeight = rc.bottom - rc.top;
	SetWindowPos(hwnd, nullptr, 0, 0, fullWidth, fullHeight, SWP_NOMOVE | SWP_NOZORDER);
}

Window::Window(const wchar_t* wnd_title, std::int32_t wnd_width, std::int32_t wnd_height)
	: m_width(wnd_width), m_height(wnd_height)
	{
		ValidateWindowSize(wnd_height, wnd_width);

		WNDCLASSEX wc{};

		wc.hInstance = GetModuleHandleW(nullptr);
		wc.lpszClassName = L"Game";
		wc.lpfnWndProc = MyWndProc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.lpszMenuName = nullptr;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

		if (!RegisterClassExW(&wc)) throw std::runtime_error("Class creation error");

		if (m_hwnd = CreateWindowExW(0, L"Game", wnd_title, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, wnd_width, wnd_height,
			nullptr, nullptr, GetModuleHandleW(nullptr), this); !m_hwnd)
		{
			throw std::runtime_error("Error on window creation");
		}

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);
	}

	Window::~Window() 
	{
		if (m_hwnd) DestroyWindow(m_hwnd);
	};


	std::int32_t Window::GameLoop()
	{
		MSG message;
		while (true)
		{
			while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
					return (int)message.wParam;
				if (GetAsyncKeyState('R') & 1) {
					m_width = 1024;
					m_height = 720;
					m_requestResize = true;
				}
					TranslateMessage(&message);
					DispatchMessageW(&message);
				
			}
				if (m_requestResize) {
					SizeWindow(m_hwnd, m_width, m_height);
					m_requestResize = false;
				}
		}
	}

	std::int32_t Window::GetWidth() const
	{
		return m_width;
	}

	std::int32_t Window::GetHeight() const
	{
		return m_height;
	}

	void Window::ValidateWindowSize(std::int32_t wnd_width, std::int32_t wnd_height) const
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
		{
			pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}
		
		if (pWindow) {
			return pWindow->HandleMessage(hwnd,message, wParam, lParam);
		}
		else {
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}
	}

	LRESULT Window::HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_KEYDOWN:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			//m_width = LOWORD(lParam);
			//m_height = HIWORD(lParam);
			return 0;
		default:
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}
		return 0;
	}
