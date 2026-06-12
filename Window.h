#pragma once

#include "Win32Wrapper.h"
#include <string>
#include <stdexcept>

// Maybe add xaudio for sound and direct2d for gui 

class Window
{
public:
	Window(const wchar_t* wnd_title, std::int32_t wnd_width, std::int32_t wnd_height);
	~Window();
	Window& operator=(const Window& w) = delete;
	Window(const Window&) = delete;
	HWND Get_Handle() const { return m_hwnd; }
	void Resize(int width, int height);
	bool ProcessSystemMessages();
	const wchar_t* GetName() const noexcept;
	HINSTANCE GetInstance() const noexcept;
	std::int32_t GetWidth() const noexcept;
	std::int32_t GetHeight() const noexcept;

private:
	const wchar_t* wnd_name{ L"Game" };
	HINSTANCE hinstance;
	HWND m_hwnd{ nullptr };
	std::int32_t m_width{};
	std::int32_t m_height{};

	void SizeWindow(HWND hwnd, int width, int height);
	void ValidateWindowSize(std::int32_t wnd_width, std::int32_t wnd_height) const;
	static LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};