#pragma once

#include "Win32Wrapper.h"
#include "MyTypes.h"

#include <stdexcept>

class Window
{
public:

	Window(const winByte* wnd_title, const signedInt wnd_width, const signedInt wnd_height);
	~Window() noexcept;

	Window& operator=(const Window& w) = delete;
	Window(const Window&) = delete;

	void setFullScreen(bool fullscreen, bool borderless = false) noexcept;
	void Resize(const signedInt width, const signedInt height) noexcept;
	bool ProcessSystemMessages() noexcept;
	float GetDPI_X() noexcept;

	const winByte* GetName() const noexcept { return wnd_name; };
	HINSTANCE GetInstance() const noexcept { return hinstance; };
	signedInt GetHeight() const noexcept { return m_height; };
	signedInt GetWidth() const noexcept { return m_width; };
	HWND Get_Handle() const noexcept { return m_hwnd; };

private:

	signedInt m_windowX, m_windowY, m_windowWidth, m_windowHeight;
	DWORD m_windowStyle, m_windowExStyle; 
	const winByte* wnd_name{ L"Game" };
	bool m_fullscreen{ false };
	float m_wndDPI{}; //m_wndDPI stores current monitor dpi
	HWND m_hwnd{ nullptr };
	HINSTANCE hinstance{};
	signedInt m_width{};
	signedInt m_height{};

	static LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SizeWindow(HWND hwnd, signedInt width, signedInt height, float scale) noexcept;
	void ValidateWindowSize(signedInt wnd_width, signedInt wnd_height) const noexcept;
};