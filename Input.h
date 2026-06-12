#pragma once
#include "Win32Wrapper.h"
#include <cstdint>
#include <array>
#include <iostream>

struct KeyboardState {};
enum ButtonState {};

class Input
{
public:
	void Update();

	std::int32_t IsKeyPressed(std::int32_t key_code) const;
	std::int32_t IsKeyReleased(std::int32_t key_code) const;
	std::int32_t IsKeyDown(std::int32_t key_code) const;
	void MousePosition(std::int32_t& x, std::int32_t& y);
	bool IsMouseKeyDown(std::int32_t button) const;

private:
	std::array<bool, 256> CurrentKeys{};
	std::array<bool, 256> PreviousKeys{};
	int mouse_PosX{}, mouse_PosY{};
	int mouseDeltaX{}, mouseDeltaY{};
};
