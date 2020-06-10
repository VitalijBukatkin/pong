//
// Created by vitalijbukatkin on 29.05.2020.
//

#include "../include/pong.h"
#include "../include/game.h"
#include "../include/util/common.h"

void init_game_elements(Ball *ball, Player *pl1, Player *pl2) {
    ball->x = (SCREEN_WIDTH - ball->w) / 2;
    ball->y = (SCREEN_HEIGHT - ball->h) / 2;
    ball->speed_x = Common_GetRandomInt(0, 1) == 0 ? BALL_SPEED : -BALL_SPEED;
    ball->speed_y = Common_GetRandomInt(0, 1) == 0 ? BALL_SPEED : -BALL_SPEED;

    pl1->x = 0;
    pl1->y = (SCREEN_HEIGHT - pl1->h) / 2;

    pl2->x = SCREEN_WIDTH - pl2->w;
    pl2->y = (SCREEN_HEIGHT - pl2->h) / 2;
}

/**
 * 1. Check borders for ball and revert direction
 * 2. Move ball
 */
void ball_move(Ball *ball, int checkFall) {
    if (checkFall == 2) {
        ball->speed_x = -ball->speed_x;
    } else if (ball->y + ball->h + ball->speed_y > SCREEN_HEIGHT
               || ball->y + ball->speed_y < 0) {
        ball->speed_y = -ball->speed_y;
    }

    ball->y += ball->speed_y;
    ball->x += ball->speed_x;
}

/**
 * Check falls ball for players
 */
int check_fall(Ball ball, Player pl1, Player pl2) {
    if (ball.x + ball.speed_x <= pl1.x + pl1.w) {
        if (ball.y < pl1.y || ball.y > pl1.y + pl1.h)
            return Game_FALLPLAYER1;
        return Game_CAUGHT;
    }
    if (ball.x + ball.w + ball.speed_x > pl2.x) {
        if (ball.y < pl2.y || ball.y > pl2.y + pl2.h)
            return Game_FALLPLAYER2;
        return Game_CAUGHT;
    }
    return Game_OUTOF;
}

/**
 * Start new game
 */
void start_new_game(Ball *ball, Player *pl1, Player *pl2) {
    SDL_QueryTexture(textures.ball, NULL, NULL, &ball->w, &ball->h);
    SDL_QueryTexture(textures.deck, NULL, NULL, &pl1->w, &pl1->h);
    SDL_QueryTexture(textures.deck, NULL, NULL, &pl2->w, &pl2->h);

    init_game_elements(ball, pl1, pl2);

    pl1->score = 0;
    pl2->score = 0;
    pl1->speed = (SCREEN_HEIGHT / 100) * 3;
    pl2->speed = (SCREEN_HEIGHT / 100) * 3;
}

/**
 * Move player bat UP/DOWN
 */
void player_move(EventType eventType, Player *pl1, Player *pl2) {
    switch (eventType) {
        case Events_LEFT_STICK_MOVE_UP:
        case Events_BUTTON_W:
            if (pl1->y - pl1->speed >= 0) {
                pl1->y -= pl1->speed;
            }
            break;
        case Events_LEFT_STICK_MOVE_DOWN:
        case Events_BUTTON_S:
            if (pl1->y + pl1->speed <= SCREEN_HEIGHT - pl1->h) {
                pl1->y += pl1->speed;
            }
            break;
        case Events_RIGHT_STICK_MOVE_UP:
        case Events_BUTTON_UP:
            if (pl2->y - pl2->speed >= 0) {
                pl2->y -= pl2->speed;
            }
            break;
        case Events_RIGHT_STICK_MOVE_DOWN:
        case Events_BUTTON_DOWN:
            if (pl2->y + pl2->speed <= SCREEN_HEIGHT - pl2->h) {
                pl2->y += pl2->speed;
            }
            break;
        default:
            break;
    };
}

/**
 * Render game on screen
 */
void render_game(SDL_Renderer *ren, Ball ball, Player pl1, Player pl2) {
    SDL_RenderClear(ren);

    Render_ApplyTexture(ren, 0, 0, textures.background);
    Render_ApplyTexture(ren, pl1.x, pl1.y, textures.deck);
    Render_ApplyTexture(ren, pl2.x, pl2.y, textures.deck);

    SDL_Texture *ball_texture = ball.active == true ? textures.ball_active : textures.ball;
    Render_ApplyTexture(ren, ball.x, ball.y, ball_texture);

    sprintf(text_buff, "%d", pl1.score);
    Render_ApplyTextWithColor(ren, fonts.main, text_buff, pl1.w + 10, pl1.w, TEXT_COLOR);
    sprintf(text_buff, "%d", pl2.score);
    Render_ApplyTextWithColor(ren, fonts.main, text_buff, SCREEN_WIDTH - pl2.w - 20, pl2.w, TEXT_COLOR);

    SDL_RenderPresent(ren);
}

/**
 * Render result game on screen
 */
void render_end_game(SDL_Renderer *ren, Player pl1, Player pl2) {
    SDL_RenderClear(ren);

    Render_ApplyTexture(ren, 0, 0, textures.background);

    char *winner;
    if (pl1.score < pl2.score)
        winner = "Player 1";
    else if (pl2.score < pl1.score)
        winner = "Player 2";
    else
        winner = "ALL";

    sprintf(text_buff, "%s win!!! Score: %d/%d", winner, pl1.score, pl2.score);
    Render_ApplyTextWithColor(ren, fonts.main, text_buff, (SCREEN_WIDTH / 2) - 150, SCREEN_HEIGHT / 2, TEXT_COLOR);
    SDL_RenderPresent(ren);
}

/**
 * Main game loop
 */
void Game_Loop(SDL_Renderer *ren) {
    Ball ball;
    Player player1, player2;

    start_new_game(&ball, &player1, &player2);

    bool run = true;
    SDL_Event e;

    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            EventType type = Events_GetEventType(e);
            if (type == Events_BUTTON_ESC || type == Events_QUIT) {
                run = false;
                break;
            }
            player_move(type, &player1, &player2);
        }

        int checkFall = check_fall(ball, player1, player2);
        if (checkFall == 0 || checkFall == 1) {
            if (checkFall)
                player1.score++;
            else
                player2.score++;
            if (player1.score >= MAX_SCORE || player2.score >= MAX_SCORE) {
                run = false;
                break;
            }
            init_game_elements(&ball, &player1, &player2);
            Common_PlayRumble(haptic);
        } else {
            ball_move(&ball, checkFall);
        }

        render_game(ren, ball, player1, player2);

        if (ball.active) {
            ball.active = false;
        }

        if (checkFall == 2) {
            Common_PlaySound(sounds.beep);
            ball.active = true;
        }
        SDL_Delay(100);
    }
    Common_PlayRumble(haptic);
    render_end_game(ren, player1, player2);

    SDL_Delay(5000);
}