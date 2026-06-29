#include "core/Input.h"


void Input::Update() noexcept
{
	PreviousKeys = CurrentKeys;
	for (int i = 0; i < CurrentKeys.size(); ++i) {
		CurrentKeys[i] = (GetAsyncKeyState(static_cast<int>(i)) & 0x8000) != 0; // delete async code
	}

	int newX, newY; //local variables for mouse pos
	POINT mouse;
	GetCursorPos(&mouse);
	newX = mouse.x;
	newY = mouse.y;

	MouseDelta(newX, newY);
	mouse_PosX = newX; // mb use class member for store mouse pos
	mouse_PosY = newY;
	ResetDelta();

}

int Input::IsKeyPressed(int key_code) const noexcept // delete
{
	return (CurrentKeys[key_code] && !PreviousKeys[key_code]);
}

int Input::IsKeyReleased(int key_code) const noexcept // delete
{
	return (!CurrentKeys[key_code] && PreviousKeys[key_code]);
}

int Input::IsKeyDown(int key_code) const noexcept //delete
{
	return CurrentKeys[key_code];
}

void Input::ResetDelta() noexcept
{
	mouseDeltaX = 0;
	mouseDeltaY = 0;
}

void Input::MouseDelta(int& x, int& y) noexcept
{
	mouseDeltaX = x - mouse_PosX;
	mouseDeltaY = y - mouse_PosY;
}

bool Input::IsMouseKeyDown(char button) const noexcept // delete?
{
	bool swap = GetSystemMetrics(SM_SWAPBUTTON) != 0;
	if (button == VK_LBUTTON)
	{
		return GetAsyncKeyState(swap ? VK_RBUTTON : VK_LBUTTON) & 0x8000;
	}
	else if(VK_RBUTTON)
	{
		return GetAsyncKeyState(swap ? VK_LBUTTON : VK_RBUTTON) & 0x8000;
	}
	return false;
}
