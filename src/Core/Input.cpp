#include "core/Input.h"


void Input::Update() noexcept
{
	PreviousKeys = CurrentKeys;
	for (signedTinyInt i = 0; i < CurrentKeys.size(); ++i) {
		CurrentKeys[i] = (GetAsyncKeyState(static_cast<signedTinyInt>(i)) & 0x8000) != 0; // delete async code
	}

	signedInt newX, newY; //local variables for mouse pos
	POINT mouse;
	GetCursorPos(&mouse);
	newX = mouse.x;
	newY = mouse.y;

	MouseDelta(newX, newY);
	mouse_PosX = newX; // mb use class member for store mouse pos
	mouse_PosY = newY;
	ResetDelta();

}

signedInt Input::IsKeyPressed(unsignedByte key_code) const noexcept // delete
{
	return (CurrentKeys[key_code] && !PreviousKeys[key_code]);
}

signedInt Input::IsKeyReleased(unsignedByte key_code) const noexcept // delete
{
	return (!CurrentKeys[key_code] && PreviousKeys[key_code]);
}

signedInt Input::IsKeyDown(unsignedByte key_code) const noexcept //delete
{
	return CurrentKeys[key_code];
}

void Input::ResetDelta() noexcept
{
	mouseDeltaX = 0;
	mouseDeltaY = 0;
}

void Input::MouseDelta(signedInt& x, signedInt& y) noexcept
{
	mouseDeltaX = x - mouse_PosX;
	mouseDeltaY = y - mouse_PosY;
}

bool Input::IsMouseKeyDown(signedInt button) const noexcept // delete?
{
	bool swap = GetSystemMetrics(SM_SWAPBUTTON) != 0;
	if (VK_LBUTTON)
	{
		return GetAsyncKeyState(swap ? VK_RBUTTON : VK_LBUTTON) & 0x8000;
	}
	else if(VK_RBUTTON)
	{
		return GetAsyncKeyState(swap ? VK_LBUTTON : VK_RBUTTON) & 0x8000;
	}
	return false;
}
