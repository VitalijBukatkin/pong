//
// Created by vitalijbukatkin on 03.06.2020.
//

#ifndef PONG_COMMON_H
#define PONG_COMMON_H

#define Common_PlaySound(sound) Mix_PlayChannel(-1, sound, 0);
#define Common_PlayRumble(haptic) SDL_HapticRumblePlay(haptic, HAPTIC_STRENGTH, HAPTIC_LONG)

#define Common_GetRandom(min, max) min + rand() % (max - min + 1)

#endif //PONG_COMMON_H