#include "Input.h"


void Input::Update()
{
	PreviousKeys = CurrentKeys;
	for (size_t i = 0; i < CurrentKeys.size(); ++i) {
		CurrentKeys[i] = (GetAsyncKeyState(static_cast<int>(i)) & 0x8000) != 0;
	}

	int newX, newY;
	POINT mouse;
	GetCursorPos(&mouse);
	newX = mouse.x;
	newY = mouse.y;

	mouseDeltaX = newX - mouse_PosX;
	mouseDeltaY = newY - mouse_PosY;
	mouse_PosX = newX;
	mouse_PosY = newY;
	//IsMouseKeyDown();
	MousePosition(mouse_PosX, mouse_PosY);
}

std::int32_t Input::IsKeyPressed(std::int32_t key_code) const
{
	return (CurrentKeys[key_code] && !PreviousKeys[key_code]);
}

std::int32_t Input::IsKeyReleased(std::int32_t key_code) const
{
	return (!CurrentKeys[key_code] && PreviousKeys[key_code]);
}

std::int32_t Input::IsKeyDown(std::int32_t key_code) const
{
	return CurrentKeys[key_code];
}

void Input::MousePosition(std::int32_t& x, std::int32_t& y)
{
	x = mouseDeltaX;
	y = mouseDeltaY;
	std::cout << "Mouse X = " << x << "\nMouse Y = " << y << std::endl;
}

bool Input::IsMouseKeyDown(std::int32_t button) const
{
	// VK_LBUTTON	0x01	Left mouse button
	//VK_RBUTTON	0x02	Right mouse button
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
