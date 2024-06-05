//
// Created by vitalijbukatkin on 31.05.2020.
//

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "../../include/util/render.h"

void Render_ApplyTextWithColor(SDL_Renderer *ren, TTF_Font *font, char *text, int x, int y, SDL_Color textColor) {
    SDL_Rect pos = {x, y};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
    SDL_QueryTexture(message, NULL, NULL, &pos.w, &pos.h);
    Render_ApplyTexture(ren, NULL, &pos, message);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}