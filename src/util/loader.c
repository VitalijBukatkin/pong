//
// Created by vitalijbukatkin on 29.05.2020.
//

#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_haptic.h>

SDL_Joystick *Loader_LoadJoystick() {
    if (SDL_NumJoysticks() > 0) {
        SDL_Joystick *joystick = SDL_JoystickOpen(0);
        if (SDL_JoystickNumAxes(joystick) > 0) {
            return joystick;
        }
    }
    return NULL;
}

SDL_Haptic *Loader_LoadHaptic(SDL_Joystick *joystick) {
    SDL_Haptic *haptic = SDL_HapticOpenFromJoystick(joystick);
    if (haptic == NULL || SDL_HapticRumbleInit(haptic) < 0) {
        return NULL;
    }
    return haptic;
}