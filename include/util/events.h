//
// Created by vitalijbukatkin on 29.05.2020.
//

#include <SDL2/SDL_events.h>

#ifndef PONG_EVENTS_H
#define PONG_EVENTS_H

typedef enum {
    UNDEFINED,
    QUIT,
    BUTTON_START,
    BUTTON_SPACE,
    BUTTON_ANY,
    BUTTON_ESC,
    LEFT_STICK_MOVE_UP,
    LEFT_STICK_MOVE_DOWN,
    RIGHT_STICK_MOVE_UP,
    RIGHT_STICK_MOVE_DOWN,
} EventType;

EventType Events_GetEventType(SDL_Event event);

#endif //PONG_EVENTS_H
