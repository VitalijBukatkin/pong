//
// Created by vitalijbukatkin on 03.06.2020.
//

#ifndef PONG_COMMON_H
#define PONG_COMMON_H

/**
 * play sound on speaker
 */
#define Common_PlaySound(sound) Mix_PlayChannel(-1, sound, 0);

/**
 * play rumble on joystick if exist
 */
#define Common_PlayRumble(haptic) SDL_HapticRumblePlay(haptic, HAPTIC_STRENGTH, HAPTIC_LONG)

/**
 * get random integer of min on max
 */
#define Common_GetRandomInt(min, max) (rand() % (max - min + 1) + min)

/**
 * Create string on buffer of concat
 *
 * @param buff - output
 * @param str1 - first string
 * @param str2 - second string
 * @return - buff
 */
char *Common_StringConcat(char *buff, char *str1, char *str2);

#endif //PONG_COMMON_H
