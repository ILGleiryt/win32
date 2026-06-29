#pragma once
#include "utility/MyTypes.h"
#include "utility/Win32Wrapper.h"

#include <array>


struct KeyboardState {};
enum ButtonState {};

class Input
{
public:
	void Update() noexcept;

	int IsKeyPressed(int key_code) const noexcept;
	int IsKeyReleased(int key_code) const noexcept;
	int IsKeyDown(int key_code) const noexcept;
	void MouseDelta(int& x, int& y) noexcept;
	bool IsMouseKeyDown(char button) const noexcept;
	void ResetDelta() noexcept;

private:
	std::array<bool, 256> CurrentKeys{};
	std::array<bool, 256> PreviousKeys{};
	int mouse_PosX{}, mouse_PosY{};
	int mouseDeltaX{}, mouseDeltaY{};
};
