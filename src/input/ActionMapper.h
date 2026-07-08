#ifndef ACTIONMAPPER_H 
#define ACTIONMAPPER_H

#include "input/Input.h"

typedef enum {
    ACTION_MOVE_FORWARD,
    ACTION_MOVE_BACKWARD,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_JUMP,
    ACTION_SHOOT,
    ACTION_AIM,
    ACTION_RELOAD,
    ACTION_USE,
    ACTION_PAUSE,

    ACTION_COUNT
} InputAction;

void ActionInputInit();
void ActionsUpdate(Input* in);

bool Action_Hold(int action);
bool Action_Released(int action);
bool Action_Pressed(int action);

#endif // ACTIONMAPPER_H

