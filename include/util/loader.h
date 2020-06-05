//
// Created by vitalijbukatkin on 29.05.2020.
//

#ifndef PONG_LOADER_H
#define PONG_LOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Joystick *Loader_LoadJoystick();

SDL_Haptic *Loader_LoadHaptic(SDL_Joystick *joystick);

#define Loader_LoadTexture(ren, file) IMG_LoadTexture(ren, file)
#define Loader_LoadFont(file, ptsize) TTF_OpenFont(file, ptsize)
#define Loader_LoadAudio(file) Mix_LoadWAV(file)

#define Loader_UnloadJoystick(joystick) SDL_JoystickClose(joystick)
#define Loader_UnloadHaptic(haptic) SDL_HapticClose(haptic)
#define Loader_UnloadTexture(texture) SDL_DestroyTexture(texture)
#define Loader_UnloadFont(font) TTF_CloseFont(font)
#define Loader_UnloadAudio(chunk) Mix_FreeChunk(chunk)

#endif //PONG_LOADER_H