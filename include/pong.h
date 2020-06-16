//
// Created by vitalijbukatkin on 31.05.2020.
//

#ifndef PONG_PONG_H
#define PONG_PONG_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "util/events.h"
#include "util/render.h"

#define GAME_TITLE "Pong"
#define MAX_SCORE 10

//activate for local start
//#define DEBUG

#ifdef DEBUG
#define RESOURCES_PATH_CONST "../themes/"
#else
#define RESOURCES_PATH_CONST "/usr/local/share/pong-0.1/themes/"
#endif

#define SCREEN_WIDTH_CONST 1280
#define SCREEN_HEIGHT_CONST 800
#define BALL_SPEED_CONST 35
#define TEXT_COLOR_CONST {255, 255, 255}

#define THEME_CONST "space"

#define HAPTIC_STRENGTH 0.7f
#define HAPTIC_LONG 500

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int BALL_SPEED;
extern SDL_Color TEXT_COLOR;

extern SDL_Joystick *joystick;
extern SDL_Haptic *haptic;

typedef struct {
    SDL_Texture *background;
    SDL_Texture *ball;
    SDL_Texture *deck;
} TexturesPack;

typedef struct {
    Mix_Chunk *beep;
} SoundsPack;

typedef struct {
    TTF_Font *main;
} FontsPack;

extern TexturesPack textures;
extern FontsPack fonts;
extern SoundsPack sounds;

#endif //PONG_PONG_H
