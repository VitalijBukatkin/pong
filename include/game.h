//
// Created by vitalijbukatkin on 30.05.2020.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "pong.h"

typedef struct {
    SDL_Texture *texture;
    int x, y;
    int w, h;
    int speed_x, speed_y;
    bool active;
} Ball;

typedef struct {
    SDL_Texture *texture;
    int x, y;
    int w, h;
    int score;
    int speed;
} Player;

extern int BALL_SPEED;

void Game_Loop(SDL_Renderer *ren);

#endif //PONG_GAME_H
