//
// Created by vitalijbukatkin on 30.05.2020.
//

#include <time.h>
#include "../include/pong.h"
#include "../include/game.h"
#include "../include/diagnostics.h"
#include "../include/util/loader.h"
#include "../include/util/common.h"

bool FULLSCREEN = true;
char RESOURCES_PATH[150] = RESOURCES_PATH_CONST;
char THEME[100] = "space";

SDL_Window *win;
SDL_Renderer *ren;
SDL_Joystick *joystick;
SDL_Haptic *haptic;

TexturesPack textures;
FontsPack fonts;
SoundsPack sounds;

bool init_resources() {
    textures.background = Loader_LoadTexture(ren,
                                             Common_StringConcat(text_buff, RESOURCES_PATH, "/images/background.png"));
    textures.ball = Loader_LoadTexture(ren, Common_StringConcat(text_buff, RESOURCES_PATH, "/images/ball.png"));
    textures.ball_active = Loader_LoadTexture(ren, Common_StringConcat(text_buff, RESOURCES_PATH,
                                                                       "/images/ball-active.png"));
    textures.deck = Loader_LoadTexture(ren, Common_StringConcat(text_buff, RESOURCES_PATH, "/images/deck.png"));
    if (textures.background == NULL ||
        textures.ball == NULL ||
        textures.deck == NULL) {
        printf("Loader_LoadTexture: %s\n", SDL_GetError());
        return false;
    }

    sounds.beep = Loader_LoadAudio(Common_StringConcat(text_buff, RESOURCES_PATH, "/sounds/beep.wav"));
    if (sounds.beep == NULL) {
        printf("Loader_LoadAudio: %s\n", SDL_GetError());
        return false;
    }

    fonts.main = Loader_LoadFont(Common_StringConcat(text_buff, RESOURCES_PATH, "/fonts/Fonts-Online.ttf"), 24);
    if (fonts.main == NULL) {
        printf("Loader_LoadFont: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool init_joystick() {
    joystick = Loader_LoadJoystick();
    if (joystick == NULL) {
        printf("Joystick not found: %s\n", SDL_GetError());
        return false;
    }

    haptic = Loader_LoadHaptic(joystick);
    if (haptic == NULL) {
        printf("SDL_HapticOpenFromJoystick: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool init_libraries() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_AUDIO) == -1) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("IMG_Init Error: %s\n", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
        printf("IMG_Init Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool init_game() {
    strcat(RESOURCES_PATH, THEME);
    srand(time(NULL));

    if (!init_libraries()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Can't load!",
                                 "Init SDL libraries is fail. See output", NULL);
        return false;
    }

    win = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                           SCREEN_WIDTH, SCREEN_HEIGHT,
                           FULLSCREEN ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SKIP_TASKBAR);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Can't load!",
                                 "Init SDL window is fail. See output", NULL);
        return false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Can't load!",
                                 "Init SDL render is fail. See output", NULL);
        return false;
    }

    if (!init_joystick()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Can't load!",
                                 "Init Joystick is fail. See output", NULL);
        return false;
    }

    if (!init_resources()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Can't load!",
                                 "Init game resources is fail. See output", NULL);
        return false;
    }

    return true;
}

/**
 * Free memory
 */
void destroy_game() {
    Loader_UnloadAudio(sounds.beep);
    Loader_UnloadTexture(textures.background);
    Loader_UnloadTexture(textures.ball);
    Loader_UnloadFont(fonts.main);
    Loader_UnloadHaptic(haptic);
    Loader_UnloadJoystick(joystick);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void show_start_window() {
    SDL_RenderClear(ren);

    Render_ApplyTexture(ren, 0, 0, textures.background);

    char *text[] = {
            "Pong!!",
            "For control use sticks gamepad",
            "Press START for next...",
            "Or ESC for EXIT.",
            " 2020"};

    for (int i = 0; i < 4; i++) {
        Render_ApplyTextWithColor(ren, fonts.main, text[i],
                                  (SCREEN_WIDTH / 2) - 200,
                                  (SCREEN_HEIGHT - 80) / 2 + i * 30, TEXT_COLOR);
    }

    SDL_RenderPresent(ren);
}

void show_end_window() {
    SDL_RenderClear(ren);

    Render_ApplyTexture(ren, 0, 0, textures.background);

    char *text[] = {
            "Thank you!",
            "Developer: Vitalij Bukatkin",
            "(t.me/wbkid, vitaliy.bukatkin@gmail.com)",
            " 2020"};

    for (int i = 0; i < 3; i++) {
        Render_ApplyTextWithColor(ren, fonts.main, text[i],
                                  (SCREEN_WIDTH / 2) - 200,
                                  (SCREEN_HEIGHT - 70) / 2 + i * 30, TEXT_COLOR);
    }

    SDL_RenderPresent(ren);
}

void print_help() {
    printf("Pong!!\n"
           " Help: \n"
           " --d - diagnostic mode\n"
           " --h - this help\n"
           " -w 1024 - display width\n"
           " -h 768 - display height\n"
           " -f true/false - fullscreen\n"
           " -s 35 - ball speed\n"
           " -t space - set game theme\n"
           " -c 255 255 255 - set text color (0 - 255)\n"
           " Developer: Vitalij Bukatkin\n"
           " (t.me/wbkid, vitaliy.bukatkin@gmail.com)\n"
           " 2020\n");
}

int prepare_arguments(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--d") == 0) {
            if (init_libraries() && init_joystick()) {
                Diagnostics_Loop(joystick);
            }
            return 1;
        } else if (strcmp(argv[i], "--h") == 0) {
            print_help();
            return 1;
        } else if (strcmp(argv[i], "-w") == 0 && argc > i + 1) {
            int width = atoi(argv[++i]);
            if (width > 0)
                SCREEN_WIDTH = width;
        } else if (strcmp(argv[i], "-h") == 0 && argc > i + 1) {
            int height = atoi(argv[++i]);
            if (height > 0)
                SCREEN_HEIGHT = height;
        } else if (strcmp(argv[i], "-s") == 0 && argc > i + 1) {
            int speed = atoi(argv[++i]);
            if (speed > 0)
                BALL_SPEED = speed;
        } else if (strcmp(argv[i], "-f") == 0 && argc > i + 1) {
            FULLSCREEN = strcmp(argv[++i], "true") == 0;
        } else if (strcmp(argv[i], "-t") == 0 && argc > i + 1) {
            strcpy(THEME, argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0 && argc > i + 3) {
            int r = atoi(argv[++i]);
            int g = atoi(argv[++i]);
            int b = atoi(argv[++i]);
            if (r >= 0 && g >= 0 && b >= 0
                && r <= 255 && g <= 255 && b <= 255) {
                SDL_Color new_color = {r, g, b};
                TEXT_COLOR = new_color;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (prepare_arguments(argc, argv) != 0) {
        return 0;
    }

    printf("Add '--h' in arguments for getting help\n");

    if (!init_game()) {
        printf("Game is not init!\n");
        destroy_game();
        return -1;
    }

    bool run = true;
    SDL_Event event;

    while (run) {
        show_start_window();
        while (SDL_PollEvent(&event) != 0) {
            EventType type = Events_GetEventType(event);
            if (type == BUTTON_ESC || type == QUIT) {
                run = false;
                break;
            } else if (type == BUTTON_START) {
                Game_Loop(ren);
                break;
            }
        }
    }
    show_end_window();
    SDL_Delay(1000);

    destroy_game();
}