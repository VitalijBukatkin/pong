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

#ifdef DEBUG
static char RESOURCES_PATH[100] = "../share/pong-0.1/themes/";
#else
static char RESOURCES_PATH[150] = "/usr/local/share/pong-0.1/themes/";
#endif

#define HAPTIC_STRENGTH 0.7f
#define HAPTIC_LONG 500

static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 800;
static int BALL_SPEED = 35;
static SDL_Color TEXT_COLOR = {255, 255, 255};

static char text_buff[100];

extern SDL_Joystick *joystick;
extern SDL_Haptic *haptic;

typedef struct {
    SDL_Texture *background;
    SDL_Texture *ball;
    SDL_Texture *ball_active;
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
