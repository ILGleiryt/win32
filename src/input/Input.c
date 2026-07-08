#include "input/Input.h"
#include <string.h>

#define KEY_COUNT 256
#define MOUSE_BUTTON_COUNT 3
#define MOUSE_LEFT_INDEX 0
#define MOUSE_RIGHT_INDEX 1
#define MOUSE_MIDDLE_INDEX 2

static bool is_window_active(Input* in)
{
	if (!in) return false;
	return GetForegroundWindow() == in->hwnd;
}

static bool query_mouse_button(int vk_button)
{
	bool swap = GetSystemMetrics(SM_SWAPBUTTON) != 0;

	if (vk_button == VK_LBUTTON)
		return GetAsyncKeyState(swap ? VK_RBUTTON : VK_LBUTTON) & 0x8000;
	else if (vk_button == VK_RBUTTON)
		return GetAsyncKeyState(swap ? VK_LBUTTON : VK_RBUTTON) & 0x8000;
	else if (vk_button == VK_MBUTTON)
		return (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

	return false;
}

static int mouse_index_to_vkcode(int index)
{
	switch (index)
	{
	case MOUSE_LEFT_INDEX:   return VK_LBUTTON;
	case MOUSE_RIGHT_INDEX:  return VK_RBUTTON;
	case MOUSE_MIDDLE_INDEX: return VK_MBUTTON;
	default: return 0;
	}
}

static bool is_mouse_keydown(Input* in, int index)
{
	if (!in || index < 0 || index >= MOUSE_BUTTON_COUNT) return false;
	if (!is_window_active(in)) return false;

	int vk = mouse_index_to_vkcode(index);
	return query_mouse_button(vk);
}

static bool is_mouse_justpress(Input* in, int index)
{
	if (!in || index < 0 || index >= MOUSE_BUTTON_COUNT) return false;
	return in->CurrentMouse[index] && !in->PreviousMouse[index];
}

static bool is_mouse_hold(Input* in, int index)
{
	if (!in || index < 0 || index >= MOUSE_BUTTON_COUNT) return false;
	return in->CurrentMouse[index];
}

static bool is_mouse_released(Input* in, int index)
{
	if (!in || index < 0 || index >= MOUSE_BUTTON_COUNT) return false;
	return in->PreviousMouse[index] && !in->CurrentMouse[index];
}

static bool input_is_key_pressed(Input* in, int key_code)
{
	if (!in || key_code < 0 || key_code >= KEY_COUNT) return false;
	return in->CurrentKeys[key_code] && !in->PreviousKeys[key_code];
}

static bool input_is_key_released(Input* in, int key_code)
{
	if (!in || key_code < 0 || key_code >= KEY_COUNT) return false;
	return in->PreviousKeys[key_code] && !in->CurrentKeys[key_code];
}

static bool input_is_key_down(Input* in, int key_code) {
	if (!in || key_code < 0 || key_code >= KEY_COUNT) return false;
	return in->CurrentKeys[key_code];
}

static int translate_to_virtualcode(MapCode code)
{
	switch (code)
	{
	case KEY_SPACE:  return VK_SPACE;
	case KEY_ESCAPE: return VK_ESCAPE;
	case KEY_ENTER: return VK_RETURN;
	case KEY_TAB: return VK_TAB;
	case KEY_SHIFT: return VK_SHIFT;
	case KEY_CTRL: return VK_CONTROL;
	case KEY_ALT: return VK_MENU;
	case KEY_BACKSPACE: return VK_BACK;
	case KEY_DELETE: return VK_DELETE;
	case KEY_LEFT: return VK_LEFT;
	case KEY_RIGHT: return VK_RIGHT;
	case KEY_UP: return VK_UP;
	case KEY_DOWN: return VK_DOWN;
	case KEY_F1: return VK_F1;
	case KEY_F2: return VK_F2;
	case KEY_F3: return VK_F3;
	case KEY_F4: return VK_F4;
	case KEY_F5: return VK_F5;
	case KEY_F6: return VK_F6;
	case KEY_F7: return VK_F7;
	case KEY_F8: return VK_F8;
	case KEY_F9: return VK_F9;
	case KEY_F10: return VK_F10;
	case KEY_F11: return VK_F11;
	case KEY_F12: return VK_F12;
	default: return 0;
	}
}

void input_init(Input* in)
{
	if (!in) return;

	memset(in->CurrentKeys, 0, sizeof(in->CurrentKeys));
	memset(in->CurrentMouse, 0, sizeof(in->CurrentMouse));
	memset(in->PreviousKeys, 0, sizeof(in->PreviousKeys));
	memset(in->PreviousMouse, 0, sizeof(in->PreviousMouse));
	in->mouse_PosX = 0;
	in->mouse_PosY = 0;
	in->mouseDeltaX = 0;
	in->mouseDeltaY = 0;
}

void input_update(Input* in)
{
	if (!in) return;
	if (!is_window_active(in))
	{
		memset(in->CurrentKeys, 0, sizeof(in->CurrentKeys));
		memset(in->PreviousKeys, 0, sizeof(in->PreviousKeys));
		memset(in->CurrentMouse, 0, sizeof(in->CurrentMouse));
		memset(in->PreviousMouse, 0, sizeof(in->PreviousMouse));
		return;
	}

	memcpy(in->PreviousKeys, in->CurrentKeys, sizeof(in->CurrentKeys));
	memcpy(in->PreviousMouse, in->CurrentMouse, sizeof(in->CurrentMouse));

	BYTE keyboardState[KEY_COUNT];
	if (GetKeyboardState(keyboardState) == 0) return;

	for (int i = 0; i < KEY_COUNT; i++)
	{
		in->CurrentKeys[i] = (keyboardState[i] & 0x80) != 0;
	}

	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(in->hwnd, &mouse);
	int newX = mouse.x;
	int newY = mouse.y;
	mouse_delta(in, newX, newY);
	in->mouse_PosX = newX;
	in->mouse_PosY = newY;

	for (int i = 0; i < MOUSE_BUTTON_COUNT; i++)
	{
		in->CurrentMouse[i] = is_mouse_keydown(in, i);
	}
	//reset_mouse_delta(in);
}

void mouse_delta(Input* in, int x, int y)
{
	in->mouseDeltaX = x - in->mouse_PosX;
	in->mouseDeltaY = y - in->mouse_PosY;
}

void reset_mouse_delta(Input* in)
{
	if (!in) return;
	in->mouseDeltaX = 0;
	in->mouseDeltaY = 0;
}

bool input_justpress(Input* in, MapCode code)
{
	if (!in) return false;

	if (code == MOUSE_LEFT) return is_mouse_justpress(in, MOUSE_LEFT_INDEX);
	if (code == MOUSE_RIGHT) return is_mouse_justpress(in, MOUSE_RIGHT_INDEX);
	if (code == MOUSE_MIDDLE) return is_mouse_justpress(in, MOUSE_MIDDLE_INDEX);

	int vk = (code >= 256 && code < 512) ? translate_to_virtualcode(code) : (int)code;
	return input_is_key_pressed(in, vk);
}

bool input_justrelease(Input* in, MapCode code)
{
	if (!in) return false;


	if (code == MOUSE_LEFT) return is_mouse_released(in, MOUSE_LEFT_INDEX);
	if (code == MOUSE_RIGHT) return is_mouse_released(in, MOUSE_RIGHT_INDEX);
	if (code == MOUSE_MIDDLE) return is_mouse_released(in, MOUSE_MIDDLE_INDEX);

	int vk = (code >= 256 && code < 512) ? translate_to_virtualcode(code) : (int)code;
	return input_is_key_released(in, vk);
}

bool input_justhold(Input* in, MapCode code)
{
	if (!in) return false;

	if (code == MOUSE_LEFT) return in->CurrentMouse[MOUSE_LEFT_INDEX];
	if (code == MOUSE_RIGHT) return in->CurrentMouse[MOUSE_RIGHT_INDEX];
	if (code == MOUSE_MIDDLE) return in->CurrentMouse[MOUSE_MIDDLE_INDEX];

	int vk = (code >= 256 && code < 512) ? translate_to_virtualcode(code) : (int)code;
	return input_is_key_down(in, vk);
}
