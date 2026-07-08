#include "ActionMapper.h"
#include <string.h>

typedef struct {
    MapCode key;
} ActionBind;

static struct {
    bool  pressed;
    bool  released;
    bool  hold;
} actionStates[ACTION_COUNT];

static ActionBind bindings[ACTION_COUNT];

static void ActionLoadDefault()
{
    bindings[ACTION_MOVE_FORWARD] = (ActionBind){ KEY_W };
    bindings[ACTION_MOVE_BACKWARD] = (ActionBind){ KEY_S };
    bindings[ACTION_MOVE_LEFT] = (ActionBind){ KEY_A };
    bindings[ACTION_MOVE_RIGHT] = (ActionBind){ KEY_D };

    bindings[ACTION_JUMP] = (ActionBind){ KEY_SPACE };
    bindings[ACTION_SHOOT] = (ActionBind){ MOUSE_LEFT };
    bindings[ACTION_AIM] = (ActionBind){ MOUSE_RIGHT };
    bindings[ACTION_PAUSE] = (ActionBind){ KEY_ESCAPE };
}

void ActionInputInit()
{
	memset(bindings, 0, sizeof(bindings));
	memset(actionStates, 0, sizeof(actionStates));
	ActionLoadDefault();
}

void ActionsUpdate(Input* in) {
    if (!in) return;

    for (int i = 0; i < ACTION_COUNT; i++) {
        actionStates[i].pressed = false;
        actionStates[i].released = false;
        actionStates[i].hold = false;
    }

    for (int i = 0; i < ACTION_COUNT; i++) {
        ActionBind* b = &bindings[i];
        if (b->key == 0) continue;

        if (input_justpress(in, b->key)) {
            actionStates[i].pressed = true;
        }
        if (input_justrelease(in, b->key)) {
            actionStates[i].released = true;
        }
        if (input_justhold(in, b->key)) {
            actionStates[i].hold = true;
        }
    }
}

bool  Action_Pressed(int a) { return actionStates[a].pressed; }
bool  Action_Released(int a) { return actionStates[a].released; }
bool  Action_Hold(int a) { return actionStates[a].hold; }