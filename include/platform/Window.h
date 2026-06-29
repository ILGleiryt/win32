#pragma once

#include "utility/Win32Wrapper.h"
#include "utility/MyTypes.h"

#include <stdexcept>
#include <wchar.h>

class Window
{
public:
	Window(const wchar_t* wnd_title, const int wnd_width, const int wnd_height);
	~Window() noexcept;

	Window& operator=(const Window& w) = delete;
	Window(const Window&) = delete;

	void setFullScreen(bool fullscreen, bool borderless = false) noexcept;
	void Resize(const int width, const int height) noexcept;
	bool ProcessSystemMessages() noexcept;
	float GetDPI_X() noexcept;

	const wchar_t* GetName() const noexcept { return wnd_name; };
	HINSTANCE GetInstance() const noexcept { return hinstance; };
	int GetHeight() const noexcept { return m_height; };
	int GetWidth() const noexcept { return m_width; };
	HWND Get_Handle() const noexcept { return m_hwnd; };

private:

	int m_windowX, m_windowY, m_windowWidth, m_windowHeight;
	DWORD m_windowStyle, m_windowExStyle; 
	const wchar_t* wnd_name = L"Game" ;
	bool m_fullscreen{ false };
	float m_wndDPI{}; //m_wndDPI stores current monitor dpi
	HWND m_hwnd{ nullptr };
	HINSTANCE hinstance{};
	int m_width{};
	int m_height{};

	static LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SizeWindow(HWND hwnd, int width, int height, float scale) noexcept;
	void ValidateWindowSize(int wnd_width, int wnd_height) const noexcept;
};