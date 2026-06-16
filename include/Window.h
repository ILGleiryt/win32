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
	void Resize(const signedInt width, const signedInt height);
	bool ProcessSystemMessages() noexcept;
	float GetDPI_X() noexcept;
	void setFullScreen(bool fullscreen, bool borderless = false);

	HWND Get_Handle() const noexcept { return m_hwnd; };
	const winByte* GetName() const noexcept { return wnd_name; };
	HINSTANCE GetInstance() const noexcept { return hinstance; };
	signedInt GetWidth() const noexcept { return m_width; };
	signedInt GetHeight() const noexcept { return m_height; };

private:

	bool m_fullscreen{ false };
	signedInt m_windowX, m_windowY, m_windowWidth, m_windowHeight;
	DWORD m_windowStyle, m_windowExStyle; 
	float m_wndDPI{}; //m_wndDPI stores current monitor dpi
	const winByte* wnd_name{ L"Game" };
	HINSTANCE hinstance{};
	HWND m_hwnd{ nullptr };
	signedInt m_width{};
	signedInt m_height{};

	void SizeWindow(HWND hwnd, signedInt width, signedInt height, float scale);
	void ValidateWindowSize(signedInt wnd_width, signedInt wnd_height) const;
	static LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};