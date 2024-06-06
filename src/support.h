//
// Created by vitalijbukatkin on 03.06.2020.
//

#ifndef PONG_SUPPORT_H
#define PONG_SUPPORT_H

#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_ttf.h"

typedef enum {
  Events_UNDEFINED,
  Events_QUIT,
  // Keyboard
  Events_BUTTON_SPACE,
  Events_BUTTON_ESC,
  Events_BUTTON_W,
  Events_BUTTON_S,
  Events_BUTTON_UP,
  Events_BUTTON_DOWN,
  Events_BUTTON_ANY,
  // Joystick
  Events_BUTTON_START,
  Events_LEFT_STICK_MOVE_UP,
  Events_LEFT_STICK_MOVE_DOWN,
  Events_RIGHT_STICK_MOVE_UP,
  Events_RIGHT_STICK_MOVE_DOWN,
} EventType;

/**
 * get EventType from keyboards and joystick
 * @param event - SDL_Event
 * @return - result
 */
EventType get_event_type_from_raw(SDL_Event event);

/**
 * play sound on speaker
 */
#define play_sound(sound) Mix_PlayChannel(-1, sound, 0)

/**
 * play rumble on joystick if exist
 */
#define play_haptic_rumble(haptic)                                             \
  SDL_HapticRumblePlay(haptic, HAPTIC_STRENGTH, HAPTIC_LONG)

/**
 * Apply layer on screen
 */
#define apply_texture_to_renderer(ren, dstrect, srcrect, tex)                  \
  SDL_RenderCopy(ren, tex, dstrect, srcrect);

/**
 * Apply text on screen
 */
void apply_text_to_renderer(SDL_Renderer *ren, TTF_Font *font, char *text,
                            int x, int y, SDL_Color textColor);

/**
 * get random integer of min on max
 */
#define randint(min, max) (rand() % (max - min + 1) + min)

/**
 * Create string on buffer of concat
 *
 * @param buff - output
 * @param str1 - first string
 * @param str2 - second string
 * @return - buff
 */
char *strconcat(char *buff, char *str1, char *str2);

#endif // PONG_SUPPORT_H
