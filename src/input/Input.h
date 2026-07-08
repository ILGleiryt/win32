#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include "utility/Win32Wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	// Letters
	KEY_A = 'A', KEY_B = 'B', KEY_C = 'C', KEY_D = 'D', KEY_E = 'E',
	KEY_F = 'F', KEY_G = 'G', KEY_H = 'H', KEY_I = 'I', KEY_J = 'J',
	KEY_K = 'K', KEY_L = 'L', KEY_M = 'M', KEY_N = 'N', KEY_O = 'O',
	KEY_P = 'P', KEY_Q = 'Q', KEY_R = 'R', KEY_S = 'S', KEY_T = 'T',
	KEY_U = 'U', KEY_V = 'V', KEY_W = 'W', KEY_X = 'X', KEY_Y = 'Y', KEY_Z = 'Z',
	// Numbers 
	EY_0 = '0', KEY_1 = '1', EY_2 = '2', EY_3 = '3', EY_4 = '4', 
	EY_5 = '5', EY_6 = '6', EY_7 = '7', EY_8 = '8', EY_9 = '9', 

	// special keys
	KEY_SPACE = 256,
	KEY_ESCAPE,
	KEY_ENTER,
	KEY_TAB,
	KEY_SHIFT,
	KEY_CTRL,
	KEY_ALT,
	KEY_BACKSPACE,
	KEY_DELETE,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_F1, KEY_F2, KEY_F3, KEY_F4,
	KEY_F5, KEY_F6, KEY_F7, KEY_F8,
	KEY_F9, KEY_F10, KEY_F11, KEY_F12,

	MOUSE_LEFT = 512, MOUSE_RIGHT, MOUSE_MIDDLE, MOUSE_WHEEL_UP, MOUSE_WHEEL_DOWN,

} MapCode;

typedef struct Input {
	int mouseDeltaX, mouseDeltaY;
	int mouse_PosX, mouse_PosY;
	bool CurrentKeys[256];
	bool PreviousKeys[256];
	bool CurrentMouse[3];
	bool PreviousMouse[3];
	HWND hwnd;
} Input;

void input_update(Input* in);
void input_init(Input* in);

void mouse_delta(Input* in, int x, int y);
void reset_mouse_delta(Input* in);

bool input_justpress(Input* in, MapCode code);
bool input_justrelease(Input* in, MapCode code);
bool input_justhold(Input* in, MapCode code);

#ifdef __cplusplus
}
#endif

#endif // INPUT_H