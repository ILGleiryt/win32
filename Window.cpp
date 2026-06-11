#include "Window.h"

Window::Window(const std::wstring& wnd_title, std::int32_t wnd_width, std::int32_t wnd_height)
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

		if (m_hwnd = CreateWindowExW(0, L"Game", wnd_title.c_str(), WS_OVERLAPPEDWINDOW,
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
	void Window::ResizeWindow(std::int32_t new_width, std::int32_t new_height)
	{
		if (new_width <= 0 || new_height <= 0)
			throw std::invalid_argument("Bad window size");

		m_width = new_width;
		m_height = new_height;

		SetWindowPos(m_hwnd, nullptr, 0, 0, m_width, m_height, SWP_NOMOVE | SWP_NOZORDER);
	}

	std::int32_t Window::GameLoop()
	{
		MSG message;
		while (true)
		{
			while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
					return (int)message.wParam;
				TranslateMessage(&message);
				DispatchMessageW(&message);
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
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			m_width = LOWORD(lParam);
			m_height = HIWORD(lParam);
			return 0;
		default:
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}
		return 0;
	}
