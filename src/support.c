//
// Created by vitalijbukatkin on 29.05.2020.
//

#include "support.h"

EventType get_event_type_from_raw(SDL_Event event) {
  if (event.type == SDL_JOYAXISMOTION) {
    if (event.jaxis.axis == 4) {
      if (event.jaxis.value > 0)
        return Events_RIGHT_STICK_MOVE_DOWN;
      if (event.jaxis.value < 0)
        return Events_RIGHT_STICK_MOVE_UP;
    }
    if (event.jaxis.axis == 1) {
      if (event.jaxis.value > 0)
        return Events_LEFT_STICK_MOVE_DOWN;
      if (event.jaxis.value < 0)
        return Events_LEFT_STICK_MOVE_UP;
    }
  }
  if (event.jbutton.button == 9)
    return Events_BUTTON_START;
  if (event.type == SDL_QUIT)
    return Events_QUIT;
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_SPACE)
      return Events_BUTTON_SPACE;
    if (event.key.keysym.sym == SDLK_ESCAPE)
      return Events_BUTTON_ESC;
    if (event.key.keysym.sym == SDLK_w)
      return Events_BUTTON_W;
    if (event.key.keysym.sym == SDLK_s)
      return Events_BUTTON_S;
    if (event.key.keysym.sym == SDLK_UP)
      return Events_BUTTON_UP;
    if (event.key.keysym.sym == SDLK_DOWN)
      return Events_BUTTON_DOWN;
    return Events_BUTTON_ANY;
  }
  return Events_UNDEFINED;
}

void apply_text_to_renderer(SDL_Renderer *ren, TTF_Font *font, char *text,
                            int x, int y, SDL_Color textColor) {
  SDL_Rect pos = {x, y};
  SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text, textColor);
  SDL_Texture *message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
  SDL_QueryTexture(message, NULL, NULL, &pos.w, &pos.h);
  apply_texture_to_renderer(ren, NULL, &pos, message);
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(message);
}

char *strconcat(char *buff, char *str1, char *str2) {
  sprintf(buff, "%s%s", str1, str2);
  return buff;
}
