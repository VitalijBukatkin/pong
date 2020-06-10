//
// Created by vitalijbukatkin on 29.05.2020.
//

#include <SDL2/SDL_events.h>

#ifndef PONG_EVENTS_H
#define PONG_EVENTS_H

typedef enum {
    UNDEFINED,
    QUIT,
    // Keyboard
    BUTTON_SPACE,
    BUTTON_ESC,
    BUTTON_W,
    BUTTON_S,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_ANY,
    // Joystick
    BUTTON_START,
    LEFT_STICK_MOVE_UP,
    LEFT_STICK_MOVE_DOWN,
    RIGHT_STICK_MOVE_UP,
    RIGHT_STICK_MOVE_DOWN,
} EventType;

EventType Events_GetEventType(SDL_Event event);

#endif //PONG_EVENTS_H
