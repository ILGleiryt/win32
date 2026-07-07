#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include "utility/Win32Wrapper.h"
#include <stdbool.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Window {
	HWND hwnd;
	HINSTANCE hinstance;
	const wchar_t* wnd_title;
	const wchar_t* class_name;

	int width; // width and height window * dpi
	int height;
	float dpi_scale; // store current dpi for monitor
	bool fullscreen;
	bool borderless;

	DWORD windowStyle;
	DWORD windowExStyle;
	int window_x; // left border of window
	int window_y; // upper border of window
	int window_width; // store actual window width(without scale pdi)
	int window_height; // store actual window height(without scale dpi)

} Window;

bool window_init(Window* win, const wchar_t* name, int width, int height);
void window_shutdown(Window* win);

void window_set_fullscreen(Window* win, bool set_fullscreen, bool borderless);
void window_resize(Window* win, int width, int height);
bool window_process_system_msg(Window* win);

const wchar_t* window_get_classname(const Window* win);
const wchar_t* window_get_wndtitle(const Window* win);
HINSTANCE window_get_hinstance(const Window* win);
int window_get_height(const Window* win);
int window_get_width(const Window* win);
HWND window_get_handle(const Window* win);

// these functions also maybe need be static
LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//LRESULT window_handle_message(Window* win, HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
}
#endif

#endif // WIN32_WINDOW_H