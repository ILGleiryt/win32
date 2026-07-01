#include "core/Input.h"
#include <string.h>

void input_init(Input* in)
{
	if (!in) return;

	memset(in->CurrentKeys, 0, sizeof(in->CurrentKeys));
	memset(in->PreviousKeys, 0, sizeof(in->PreviousKeys));
	in->mouse_PosX = 0;
	in->mouse_PosY = 0;
	in->mouseDeltaX = 0;
	in->mouseDeltaY = 0;
}

void input_update(Input* in)
{
	memcpy(in->PreviousKeys, in->CurrentKeys, sizeof(in->CurrentKeys));
	for (int i = 0; i < 256; i++)
	{
		in->CurrentKeys[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
	}

	POINT mouse;
	GetCursorPos(&mouse);
	int newX = mouse.x;
	int newY = mouse.y;
	mouse_delta(in, newX, newY);
	in->mouse_PosX = newX;
	in->mouse_PosY = newY;
	reset_mouse_delta(in);
}

bool input_is_key_pressed(Input* in, int key_code)
{
	if (!in || key_code < 0 || key_code > 256) return false;
	return in->CurrentKeys[key_code] && !in->PreviousKeys[key_code];
}

bool input_is_key_released(Input* in, int key_code)
{
	if (!in || key_code < 0 || key_code > 256) return false;
	return in->PreviousKeys[key_code] && !in->CurrentKeys[key_code];
}

bool input_is_key_down(Input* in, int key_code) {
	if (!in || key_code < 0 || key_code >= 256) return false;
	return in->CurrentKeys[key_code];
}

void mouse_delta(Input* in, int x, int y)
{
	in->mouseDeltaX = x - in->mouse_PosX;
	in->mouseDeltaY = x - in->mouse_PosY;
}

bool is_mouse_keydown(Input* in, char button)
{
	bool swap = GetSystemMetrics(SM_SWAPBUTTON) != 0;
	if (button == VK_LBUTTON)
	{
		return GetAsyncKeyState(swap ? VK_RBUTTON : VK_LBUTTON) & 0x8000;
	}
	else if (VK_RBUTTON)
	{
		return GetAsyncKeyState(swap ? VK_LBUTTON : VK_RBUTTON) & 0x8000;
	}
	return false;
}

void reset_mouse_delta(Input* in)
{
	in->mouseDeltaX = 0;
	in->mouseDeltaY = 0;
}
