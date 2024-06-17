//
// Created by vitalijbukatkin on 30.05.2020.
//

#include <signal.h>
#include <stdlib.h>

#include "game.h"
#include "pong.h"
#include "support.h"
#include <time.h>

int SCREEN_WIDTH = SCREEN_WIDTH_CONST;
int SCREEN_HEIGHT = SCREEN_HEIGHT_CONST;
int BALL_SPEED = BALL_SPEED_CONST;
SDL_Color TEXT_COLOR = TEXT_COLOR_CONST;

bool FULLSCREEN = true;
char RESOURCES_PATH[150] = RESOURCES_PATH_CONST;

SDL_Window *win;
SDL_Renderer *ren;
SDL_Joystick *joystick;
SDL_Haptic *haptic;

TexturesPack textures;
FontsPack fonts;
SoundsPack sounds;

void show_start_window() {
  SDL_RenderClear(ren);

  apply_texture_to_renderer(ren, 0, 0, textures.board);

  char *text[] = {"Pong!!", "For control use sticks gamepad",
                  "Press START or SPACE for next...", "Or ESC for EXIT.",
                  " 2020"};

  for (int i = 0; i < 4; i++) {
    apply_text_to_renderer(ren, fonts.main, text[i], (SCREEN_WIDTH / 2) - 200,
                           (SCREEN_HEIGHT - 80) / 2 + i * 30, TEXT_COLOR);
  }

  SDL_RenderPresent(ren);
}

void show_end_window() {
  SDL_RenderClear(ren);

  apply_texture_to_renderer(ren, 0, 0, textures.board);

  char *text[] = {"Thank you!", "Vitalij Bukatkin",
                  "(t.me/wbkid, vitaliy.bukatkin@gmail.com)", " 2020"};

  for (int i = 0; i < 3; i++) {
    apply_text_to_renderer(ren, fonts.main, text[i], (SCREEN_WIDTH / 2) - 200,
                           (SCREEN_HEIGHT - 70) / 2 + i * 30, TEXT_COLOR);
  }

  SDL_RenderPresent(ren);
}

void destroy_game() {
  Mix_FreeChunk(sounds.caught);
  SDL_DestroyTexture(textures.board);
  SDL_DestroyTexture(textures.ball);
  TTF_CloseFont(fonts.main);
  SDL_HapticClose(haptic);
  SDL_JoystickClose(joystick);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

bool init_resources() {
  char texture_path_buff[150];
  textures.board = IMG_LoadTexture(
      ren, strconcat(texture_path_buff, RESOURCES_PATH, "/images/board.svg"));
  textures.ball = IMG_LoadTexture(
      ren, strconcat(texture_path_buff, RESOURCES_PATH, "/images/ball.svg"));
  textures.player = IMG_LoadTexture(
      ren, strconcat(texture_path_buff, RESOURCES_PATH, "/images/player.svg"));
  if (textures.board == NULL || textures.ball == NULL ||
      textures.player == NULL) {
    printf("IMG_LoadTexture: %s\n", SDL_GetError());
    return false;
  }

  sounds.caught = Mix_LoadWAV(
      strconcat(texture_path_buff, RESOURCES_PATH, "/sounds/caught.wav"));
  sounds.fall = Mix_LoadWAV(
      strconcat(texture_path_buff, RESOURCES_PATH, "/sounds/fall.wav"));
  if (sounds.caught == NULL || sounds.fall == NULL) {
    printf("Mix_LoadWAV: %s\n", SDL_GetError());
    return false;
  }

  fonts.main = TTF_OpenFont(
      strconcat(texture_path_buff, RESOURCES_PATH, "/fonts/Roboto-Regular.ttf"),
      24);
  if (fonts.main == NULL) {
    printf("TTF_OpenFont: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool init_joystick() {
  if (SDL_NumJoysticks() <= 0) {
    printf("Joystick not found: %s\n", SDL_GetError());
    return false;
  }

  joystick = SDL_JoystickOpen(0); // load first joystick
  if (joystick == NULL || SDL_JoystickNumAxes(joystick) <= 0) {
    printf("Joystick can'be loaded: %s\n", SDL_GetError());
    return false;
  }

  haptic = SDL_HapticOpenFromJoystick(joystick);
  if (haptic == NULL || SDL_HapticRumbleInit(haptic) < 0) {
    printf("SDL_HapticOpenFromJoystick: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool init_libraries() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC |
               SDL_INIT_AUDIO) == -1) {
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

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                    MIX_DEFAULT_CHANNELS, 2048) < 0) {
    printf("IMG_Init Error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

bool init_game() {
  srand(time(NULL));

  if (!init_libraries()) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Can't load!",
                             "Init SDL libraries is fail. See output", NULL);
    return false;
  }

  win = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                         FULLSCREEN ? SDL_WINDOW_FULLSCREEN
                                    : SDL_WINDOW_SKIP_TASKBAR);
  if (win == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Can't load!",
                             "Init SDL window is fail. See output", NULL);
    return false;
  }

  ren = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == NULL) {
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Can't load!",
                             "Init SDL render is fail. See output", NULL);
    return false;
  }

  if (!init_resources()) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Can't load!",
                             "Init game resources is fail. See output", NULL);
    return false;
  }

  init_joystick();
  return true;
}

void print_help() {
  printf("Pong!!\n"
         " Help: \n"
         " --h - this help\n"
         " -w 1024 - display width\n"
         " -h 768 - display height\n"
         " -f true/false - fullscreen\n"
         " -s 35 - ball speed\n"
         " -c 255 255 255 - set text color (0 - 255)\n"
         " Vitalij Bukatkin\n"
         " (t.me/wbkid, vitaliy.bukatkin@gmail.com)\n"
         " 2020\n");
}

bool prepare_arguments(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--h") == 0) {
      print_help();
      return false;
    } else if (strcmp(argv[i], "-w") == 0 && argc > i + 1) {
      int width = atoi(argv[++i]);
      if (width > 0)
        SCREEN_WIDTH = width;
      else
        printf("-w is out of range, ignore\n");
    } else if (strcmp(argv[i], "-h") == 0 && argc > i + 1) {
      int height = atoi(argv[++i]);
      if (height > 0)
        SCREEN_HEIGHT = height;
      else
        printf("-h is out of range, ignore\n");
    } else if (strcmp(argv[i], "-s") == 0 && argc > i + 1) {
      int speed = atoi(argv[++i]);
      if (speed > 0)
        BALL_SPEED = speed;
      else
        printf("-s is out of range, ignore\n");
    } else if (strcmp(argv[i], "-f") == 0 && argc > i + 1) {
      FULLSCREEN = strcmp(argv[++i], "true") == 0;
    } else if (strcmp(argv[i], "-c") == 0 && argc > i + 3) {
      int r = atoi(argv[++i]);
      int g = atoi(argv[++i]);
      int b = atoi(argv[++i]);
      if (r >= 0 && g >= 0 && b >= 0 && r <= 255 && g <= 255 && b <= 255) {
        SDL_Color new_color = {r, g, b};
        TEXT_COLOR = new_color;
      } else
        printf("-c is out of range, ignore\n");
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (!prepare_arguments(argc, argv)) {
    return 0;
  }

#ifdef DEBUG
  printf("DEBUG VERSION\n"
         "For build release, deactivate DEBUG in pong.h\n"
         "\n");
#endif

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
      EventType type = get_event_type_from_raw(event);
      if (type == Events_BUTTON_ESC || type == Events_QUIT) {
        run = false;
        break;
      } else if (type == Events_BUTTON_START || type == Events_BUTTON_SPACE) {
        game_loop(ren);
        break;
      }
    }
  }
  show_end_window();
  SDL_Delay(1000);
  destroy_game();
  return 0;
}
