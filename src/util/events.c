//
// Created by vitalijbukatkin on 29.05.2020.
//

#include <SDL2/SDL_events.h>
#include "../../include/util/events.h"

EventType Events_GetEventType(SDL_Event event) {
    if (event.type == SDL_JOYAXISMOTION) {
        if (event.jaxis.axis == 4) {
            if (event.jaxis.value > 0)
                return RIGHT_STICK_MOVE_DOWN;
            if (event.jaxis.value < 0)
                return RIGHT_STICK_MOVE_UP;
        }
        if (event.jaxis.axis == 1) {
            if (event.jaxis.value > 0)
                return LEFT_STICK_MOVE_DOWN;
            if (event.jaxis.value < 0)
                return LEFT_STICK_MOVE_UP;
        }
    }
    if (event.jbutton.button == 9)
        return BUTTON_START;
    if (event.type == SDL_QUIT)
        return QUIT;
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE)
            return BUTTON_SPACE;
        if (event.key.keysym.sym == SDLK_ESCAPE)
            return BUTTON_ESC;
        if (event.key.keysym.sym == SDLK_w)
            return BUTTON_W;
        if (event.key.keysym.sym == SDLK_s)
            return BUTTON_S;
        if (event.key.keysym.sym == SDLK_UP)
            return BUTTON_UP;
        if (event.key.keysym.sym == SDLK_DOWN)
            return BUTTON_DOWN;
        return BUTTON_ANY;
    }
    return UNDEFINED;
}