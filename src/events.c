//
// Created by vitalijbukatkin on 29.05.2020.
//

#include "SDL_events.h"
#include "events.h"

Events_EventType Events_GetEventType(SDL_Event event) {
    if (event.type == SDL_JOYAXISMOTION) {
        if (event.jaxis.axis == 4) {
            if (event.jaxis.value > 0)
                return Events_RIGHT_STICK_MOVE_DOWN;
            if (event.jaxis.value < 0)
                return Events_RIGHT_STICK_MOVE_UP;
        }
        if (event.jaxis.axis == 1) {
            if (event.jaxis.value > 0)
                return Events_LEFT_STICK_MOVE_DOWN;
            if (event.jaxis.value < 0)
                return Events_LEFT_STICK_MOVE_UP;
        }
    }
    if (event.jbutton.button == 9)
        return Events_BUTTON_START;
    if (event.type == SDL_QUIT)
        return Events_QUIT;
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE)
            return Events_BUTTON_SPACE;
        if (event.key.keysym.sym == SDLK_ESCAPE)
            return Events_BUTTON_ESC;
        if (event.key.keysym.sym == SDLK_w)
            return Events_BUTTON_W;
        if (event.key.keysym.sym == SDLK_s)
            return Events_BUTTON_S;
        if (event.key.keysym.sym == SDLK_UP)
            return Events_BUTTON_UP;
        if (event.key.keysym.sym == SDLK_DOWN)
            return Events_BUTTON_DOWN;
        return Events_BUTTON_ANY;
    }
    return Events_UNDEFINED;
}