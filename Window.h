#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <stdexcept>

class Window
{
public:
	Window(const std::wstring& wnd_title, std::int32_t wnd_width, std::int32_t wnd_height);

	~Window();

	Window& operator=(const Window& w) = delete;
	Window(const Window&) = delete;

	void ResizeWindow(std::int32_t new_width, std::int32_t new_height);

	HWND Get_Handle() const { return m_hwnd; }

	std::int32_t GameLoop();
	std::int32_t GetWidth() const;
	std::int32_t GetHeight() const;

private:
	HWND m_hwnd{ nullptr };
	std::int32_t m_width{};
	std::int32_t m_height{};

	void ValidateWindowSize(std::int32_t wnd_width, std::int32_t wnd_height) const;

	static LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};