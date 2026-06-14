#pragma once

#include "Win32Wrapper.h"
#include <stdexcept>
#include "MyTypes.h"

// Maybe add xaudio for sound and direct2d for gui 

class Window
{
public:
	Window(const winByte* wnd_title, signedInt wnd_width, signedInt wnd_height);
	~Window();
	Window& operator=(const Window& w) = delete;
	Window(const Window&) = delete;
	HWND Get_Handle() const { return m_hwnd; }
	void Resize(signedInt width, signedInt height);
	bool ProcessSystemMessages();
	const winByte* GetName() const noexcept;
	HINSTANCE GetInstance() const noexcept;
	std::int32_t GetWidth() const noexcept;
	std::int32_t GetHeight() const noexcept;

private:
	const winByte* wnd_name{ L"Game" };
	HINSTANCE hinstance;
	HWND m_hwnd{ nullptr };
	signedInt m_width{};
	signedInt m_height{};

	void SizeWindow(HWND hwnd, signedInt width, signedInt height);
	void ValidateWindowSize(signedInt wnd_width, signedInt wnd_height) const;
	static LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};