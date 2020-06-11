//
// Created by vitalijbukatkin on 29.05.2020.
//

#include <SDL2/SDL_events.h>

#ifndef PONG_EVENTS_H
#define PONG_EVENTS_H

typedef enum {
    Events_UNDEFINED,
    Events_QUIT,
    // Keyboard
    Events_BUTTON_SPACE,
    Events_BUTTON_ESC,
    Events_BUTTON_W,
    Events_BUTTON_S,
    Events_BUTTON_UP,
    Events_BUTTON_DOWN,
    Events_BUTTON_ANY,
    // Joystick
    Events_BUTTON_START,
    Events_LEFT_STICK_MOVE_UP,
    Events_LEFT_STICK_MOVE_DOWN,
    Events_RIGHT_STICK_MOVE_UP,
    Events_RIGHT_STICK_MOVE_DOWN,
} Events_EventType;


/**
 * get Events_EventType from keyboards and joystick
 * @param event - SDL_Event
 * @return - result
 */
Events_EventType Events_GetEventType(SDL_Event event);

#endif //PONG_EVENTS_H