#pragma once
#include "Win32Wrapper.h"
#include <stdexcept>
#include "MyTypes.h"
 
class Window
{
public:
	Window(const winByte* wnd_title, const signedInt wnd_width, const signedInt wnd_height);
	~Window() noexcept;
	Window& operator=(const Window& w) = delete;
	Window(const Window&) = delete;
	HWND Get_Handle() const noexcept { return m_hwnd; }
	void Resize(const signedInt width, const signedInt height);
	bool ProcessSystemMessages() noexcept;
	const winByte* GetName() const noexcept { return wnd_name; };
	HINSTANCE GetInstance() const noexcept { return hinstance; };
	signedInt GetWidth() const noexcept { return m_width; };
	signedInt GetHeight() const noexcept { return m_height; };
	float GetDPI_X() noexcept;
	void FullScreen(bool fullscreen, bool borderless);

private:
	bool m_fullscreen{ false };
	int m_windowX, m_windowY, m_windowWidth, m_windowHeight;
	DWORD m_windowStyle, m_windowExStyle;
	float m_wndDPI{};
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