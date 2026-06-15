#pragma once
#include "MyTypes.h"

#include "Win32Wrapper.h"
#include <array>
#include <iostream>

struct KeyboardState {};
enum ButtonState {};

class Input
{
public:
	void Update() noexcept;

	signedInt IsKeyPressed(unsignedByte key_code) const noexcept;
	signedInt IsKeyReleased(unsignedByte key_code) const noexcept;
	signedInt IsKeyDown(unsignedByte key_code) const noexcept;
	void MousePosition(signedInt& x, signedInt& y) const noexcept;
	bool IsMouseKeyDown(signedInt button) const noexcept;

private:
	std::array<bool, 256> CurrentKeys{};
	std::array<bool, 256> PreviousKeys{};
	signedInt mouse_PosX{}, mouse_PosY{};
	signedInt mouseDeltaX{}, mouseDeltaY{};
};
