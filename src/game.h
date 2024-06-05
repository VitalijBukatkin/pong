//
// Created by vitalijbukatkin on 30.05.2020.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "pong.h"

typedef struct {
    SDL_Texture *texture;
    SDL_Rect pos;
    int speed_x, speed_y;
    bool active;
} Ball;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect pos;
    int score;
    int speed;
} Player;

typedef enum {
    GAME_FALL_PLAYER_1,
    GAME_FALL_PLAYER_2,
    GAME_CAUGHT,
    GAME_OUT_OF
} PlayerStatus;

extern int BALL_SPEED;

void game_loop(SDL_Renderer *ren);

#endif //PONG_GAME_H