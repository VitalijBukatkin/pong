//
// Created by vitalijbukatkin on 29.05.2020.
//

#include <stdbool.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_events.h>
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
    print_joystick_info(joystick);

    printf(" ---- Press any key ----\n");
    printf(" ---- Ctrl-C for EXIT ----\n");

    bool run = true;
    SDL_Event event;

    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            EventType type = Events_GetEventType(event);
            if (type == BUTTON_ESC || type == QUIT) {
                run = false;
                printf("EXIT\n");
                break;
            }
            switch (type) {
                case BUTTON_START:
                    printf("BUTTON_START\n");
                    break;
                case BUTTON_SPACE:
                    printf("BUTTON_SPACE\n");
                    break;
                case BUTTON_ANY:
                    printf("BUTTON_ANY\n");
                    break;
                case LEFT_STICK_MOVE_UP:
                    printf("LEFT_STICK_MOVE_UP\n");
                    break;
                case LEFT_STICK_MOVE_DOWN:
                    printf("LEFT_STICK_MOVE_DOWN\n");
                    break;
                case RIGHT_STICK_MOVE_UP:
                    printf("RIGHT_STICK_MOVE_UP\n");
                    break;
                case RIGHT_STICK_MOVE_DOWN:
                    printf("RIGHT_STICK_MOVE_DOWN\n");
                    break;
                default:
                    break;
            }
        }
    }

}