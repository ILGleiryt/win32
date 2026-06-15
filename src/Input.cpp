#include "Input.h"


void Input::Update() noexcept
{
	PreviousKeys = CurrentKeys;
	for (signedTinyInt i = 0; i < CurrentKeys.size(); ++i) {
		CurrentKeys[i] = (GetAsyncKeyState(static_cast<signedTinyInt>(i)) & 0x8000) != 0;
	}

	signedInt newX, newY;
	POINT mouse;
	GetCursorPos(&mouse);
	newX = mouse.x;
	newY = mouse.y;

	mouseDeltaX = newX - mouse_PosX;
	mouseDeltaY = newY - mouse_PosY;
	mouse_PosX = newX;
	mouse_PosY = newY;
	MousePosition(mouse_PosX, mouse_PosY);
}

signedInt Input::IsKeyPressed(unsignedByte key_code) const noexcept
{
	return (CurrentKeys[key_code] && !PreviousKeys[key_code]);
}

signedInt Input::IsKeyReleased(unsignedByte key_code) const noexcept
{
	return (!CurrentKeys[key_code] && PreviousKeys[key_code]);
}

signedInt Input::IsKeyDown(unsignedByte key_code) const noexcept
{
	return CurrentKeys[key_code];
}

void Input::MousePosition(signedInt& x, signedInt& y) const noexcept
{
	x = mouseDeltaX;
	y = mouseDeltaY;
}

bool Input::IsMouseKeyDown(signedInt button) const noexcept
{
	if (!GetSystemMetrics(SM_SWAPBUTTON))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			std::cout << "Left mouse";
		}
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			std::cout << "Right mouse";
		}
	}
	else
	{
		if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			std::cout << "Left mouse";
		}
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			std::cout << "Right mouse";
		}
	}
	return false;
}
