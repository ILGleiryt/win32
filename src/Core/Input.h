#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include "../utility/Win32Wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Input {
	bool CurrentKeys[256];
	bool PreviousKeys[256];
	int mouse_PosX, mouse_PosY;
	int mouseDeltaX, mouseDeltaY;
} Input;

void input_update(Input* in);
void input_init(Input* in);

bool input_is_key_released(Input* in, int key_code);
bool input_is_key_pressed(Input* in, int key_code);
bool input_is_key_down(Input* in, int key_code);

bool is_mouse_keydown(Input* in, char button);
void mouse_delta(Input* in, int x, int y);
void reset_mouse_delta(Input* in);

#ifdef __cplusplus
}
#endif

#endif // INPUT_H