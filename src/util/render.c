//
// Created by vitalijbukatkin on 31.05.2020.
//

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

void Render_ApplyTexture(SDL_Renderer *ren, int x, int y, SDL_Texture *tex) {
    SDL_Rect pos = {x, y};
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(ren, tex, NULL, &pos);
}

void Render_ApplyTextWithColor(SDL_Renderer *ren, TTF_Font *font, char *text, int x, int y, int r, int g, int b) {
    SDL_Color textColor = {r, g, b};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
    Render_ApplyTexture(ren, x, y, message);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}