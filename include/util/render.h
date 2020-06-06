//
// Created by vitalijbukatkin on 31.05.2020.
//

#ifndef PONG_RENDER_H
#define PONG_RENDER_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

/**
 * Apply layer on screen
 */
void Render_ApplyTexture(SDL_Renderer *ren, int x, int y, SDL_Texture *tex);

/**
 * Apply text on screen
 */
void Render_ApplyTextWithColor(SDL_Renderer *ren, TTF_Font *font, char *text, int x, int y, SDL_Color textColor);

#endif //PONG_RENDER_H
