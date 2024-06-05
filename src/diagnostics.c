//
// Created by vitalijbukatkin on 29.05.2020.
//

#include <stdbool.h>
#include "SDL_joystick.h"
#include "SDL_events.h"
#include "../include/util/events.h"

void print_joystick_info(SDL_Joystick *joystick) {
    printf(" ---- JOYSTICK ---- \n");
    printf(" Controller name: %s\n", SDL_JoystickName(joystick));
    printf(" Num Axes: %d\n", SDL_JoystickNumAxes(joystick));
    printf(" Num Buttons: %d\n", SDL_JoystickNumButtons(joystick));
    printf(" Num Balls: %d\n", SDL_JoystickNumBalls(joystick));
    printf(" Num Hats: %d\n", SDL_JoystickNumHats(joystick));
    printf(" ---_-------------- \n");
}

void Diagnostics_Loop(SDL_Joystick *joystick) {
    printf(" ---- Diagnostics ----\n");

    if (joystick != NULL) {
        print_joystick_info(joystick);
    }

    printf(" ---- Press any key ----\n");
    printf(" ---- Ctrl-C for EXIT ----\n");
    printf(" ---- Or ESC ----\n");

    bool run = true;
    SDL_Event event;

    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            Events_EventType type = Events_GetEventType(event);
            if (type == Events_BUTTON_ESC || type == Events_QUIT) {
                run = false;
                printf("EXIT\n");
                break;
            }
            switch (type) {
                // Joystick
                case Events_BUTTON_START:
                    printf("Events_BUTTON_START\n");
                    break;
                case Events_LEFT_STICK_MOVE_UP:
                    printf("Events_LEFT_STICK_MOVE_UP\n");
                    break;
                case Events_LEFT_STICK_MOVE_DOWN:
                    printf("Events_LEFT_STICK_MOVE_DOWN\n");
                    break;
                case Events_RIGHT_STICK_MOVE_UP:
                    printf("Events_RIGHT_STICK_MOVE_UP\n");
                    break;
                case Events_RIGHT_STICK_MOVE_DOWN:
                    printf("Events_RIGHT_STICK_MOVE_DOWN\n");
                    break;
                    // Keyboard
                case Events_BUTTON_SPACE:
                    printf("Events_BUTTON_SPACE\n");
                    break;
                case Events_BUTTON_W:
                    printf("Events_BUTTON_W\n");
                    break;
                case Events_BUTTON_S:
                    printf("Events_BUTTON_S\n");
                    break;
                case Events_BUTTON_UP:
                    printf("Events_BUTTON_UP\n");
                    break;
                case Events_BUTTON_DOWN:
                    printf("Events_BUTTON_DOWN\n");
                    break;
                case Events_BUTTON_ANY:
                    printf("Events_BUTTON_ANY\n");
                    break;
                default:
                    break;
            }
        }
    }
}