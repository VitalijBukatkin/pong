//
// Created by vitalijbukatkin on 29.05.2020.
//

#include "pong.h"
#include "game.h"
#include "common.h"

char TEXT_BUFF[50];

/**
 * Render game on screen
 */
void render_game(SDL_Renderer *ren, Game_Ball ball, Game_Player pl1, Game_Player pl2) {
    SDL_RenderClear(ren);

    Render_ApplyTexture(ren, NULL, NULL, textures.board);
    Render_ApplyTexture(ren, NULL, &pl1.pos, pl1.texture);
    Render_ApplyTexture(ren, NULL, &pl2.pos, pl2.texture);

    SDL_Rect rect = {0, 0, ball.pos.w, ball.pos.h};
    if (ball.active == true) {
        rect.x = rect.w;
    }
    Render_ApplyTexture(ren, &rect, &ball.pos, ball.texture);

    sprintf(TEXT_BUFF, "%d", pl1.score);
    Render_ApplyTextWithColor(ren, fonts.main, TEXT_BUFF, pl1.pos.w + 10, pl1.pos.w, TEXT_COLOR);
    sprintf(TEXT_BUFF, "%d", pl2.score);
    Render_ApplyTextWithColor(ren, fonts.main, TEXT_BUFF, SCREEN_WIDTH - pl2.pos.w - 20, pl2.pos.w, TEXT_COLOR);

    SDL_RenderPresent(ren);
}

/**
 * Render result game on screen
 */
void render_end_game(SDL_Renderer *ren, Game_Player pl1, Game_Player pl2) {
    SDL_RenderClear(ren);

    Render_ApplyTexture(ren, NULL, NULL, textures.board);

    char *winner;
    if (pl1.score < pl2.score)
        winner = "Player 1";
    else if (pl2.score < pl1.score)
        winner = "Player 2";
    else
        winner = "ALL";

    sprintf(TEXT_BUFF, "%s win!!! Score: %d/%d", winner, pl1.score, pl2.score);
    Render_ApplyTextWithColor(ren, fonts.main, TEXT_BUFF, (SCREEN_WIDTH / 2) - 150, SCREEN_HEIGHT / 2, TEXT_COLOR);
    SDL_RenderPresent(ren);
}

/**
 * 1. Check borders for ball and revert direction
 * 2. Move ball
 */
void ball_move(Game_Ball *ball, Game_PlayerStatus playerStatus) {
    if (playerStatus == GAME_CAUGHT) {
        ball->speed_x = -ball->speed_x;
    } else if (ball->pos.y + ball->pos.h + ball->speed_y > SCREEN_HEIGHT
               || ball->pos.y + ball->speed_y < 0) {
        ball->speed_y = -ball->speed_y;
    }

    ball->pos.y += ball->speed_y;
    ball->pos.x += ball->speed_x;
}

/**
 * Check falls ball for players
 */
Game_PlayerStatus check_player_status(Game_Ball ball, Game_Player pl1, Game_Player pl2) {
    if (ball.pos.x + ball.speed_x <= pl1.pos.x + pl1.pos.w) {
        if (ball.pos.y < pl1.pos.y || ball.pos.y > pl1.pos.y + pl1.pos.h)
            return GAME_FALL_PLAYER_1;
        return GAME_CAUGHT;
    }
    if (ball.pos.x + ball.pos.w + ball.speed_x > pl2.pos.x) {
        if (ball.pos.y < pl2.pos.y || ball.pos.y > pl2.pos.y + pl2.pos.h)
            return GAME_FALL_PLAYER_2;
        return GAME_CAUGHT;
    }
    return GAME_OUT_OF;
}

/**
 * Move player bat UP/DOWN
 */
void player_move(Events_EventType eventType, Game_Player *pl1, Game_Player *pl2) {
    switch (eventType) {
        case Events_LEFT_STICK_MOVE_UP:
        case Events_BUTTON_W:
            if (pl1->pos.y - pl1->speed >= 0) {
                pl1->pos.y -= pl1->speed;
            }
            break;
        case Events_LEFT_STICK_MOVE_DOWN:
        case Events_BUTTON_S:
            if (pl1->pos.y + pl1->speed <= SCREEN_HEIGHT - pl1->pos.h) {
                pl1->pos.y += pl1->speed;
            }
            break;
        case Events_RIGHT_STICK_MOVE_UP:
        case Events_BUTTON_UP:
            if (pl2->pos.y - pl2->speed >= 0) {
                pl2->pos.y -= pl2->speed;
            }
            break;
        case Events_RIGHT_STICK_MOVE_DOWN:
        case Events_BUTTON_DOWN:
            if (pl2->pos.y + pl2->speed <= SCREEN_HEIGHT - pl2->pos.h) {
                pl2->pos.y += pl2->speed;
            }
            break;
        default:
            break;
    };
}

/**
 * Refresh game elements
 */
void init_game_elements(Game_Ball *ball, Game_Player *pl1, Game_Player *pl2) {
    ball->pos.x = (SCREEN_WIDTH - ball->pos.w) / 2;
    ball->pos.y = (SCREEN_HEIGHT - ball->pos.h) / 2;
    ball->speed_x = Common_GetRandomInt(0, 1) == 0 ? BALL_SPEED : -BALL_SPEED;
    ball->speed_y = Common_GetRandomInt(0, 1) == 0 ? BALL_SPEED : -BALL_SPEED;

    pl1->pos.x = 0;
    pl1->pos.y = (SCREEN_HEIGHT - pl1->pos.h) / 2;

    pl2->pos.x = SCREEN_WIDTH - pl2->pos.w;
    pl2->pos.y = (SCREEN_HEIGHT - pl2->pos.h) / 2;

    pl1->speed = (SCREEN_HEIGHT / 100) * 3;
    pl2->speed = (SCREEN_HEIGHT / 100) * 3;
}

/**
 * Start new game
 */
void start_new_game(Game_Ball *ball, Game_Player *pl1, Game_Player *pl2) {
    ball->texture = textures.ball;
    pl1->texture = textures.player;
    pl2->texture = textures.player;

    SDL_QueryTexture(textures.ball, NULL, NULL, &ball->pos.w, &ball->pos.h);
    SDL_QueryTexture(textures.player, NULL, NULL, &pl1->pos.w, &pl1->pos.h);
    SDL_QueryTexture(textures.player, NULL, NULL, &pl2->pos.w, &pl2->pos.h);

    //cut off half the texture
    ball->pos.w -= ball->pos.w / 2;

    init_game_elements(ball, pl1, pl2);

    pl1->score = 0;
    pl2->score = 0;
}

/**
 * Main game loop
 */
void Game_Loop(SDL_Renderer *ren) {
    Game_Ball ball;
    Game_Player player1, player2;

    start_new_game(&ball, &player1, &player2);

    bool run = true;
    SDL_Event e;

    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            Events_EventType type = Events_GetEventType(e);
            if (type == Events_BUTTON_ESC || type == Events_QUIT) {
                run = false;
                break;
            }
            player_move(type, &player1, &player2);
        }

        Game_PlayerStatus checkFall = check_player_status(ball, player1, player2);
        if (checkFall == GAME_FALL_PLAYER_1 || checkFall == GAME_FALL_PLAYER_2) {
            if (checkFall)
                player1.score++;
            else
                player2.score++;
            if (player1.score >= MAX_SCORE || player2.score >= MAX_SCORE) {
                run = false;
                break;
            }
            init_game_elements(&ball, &player1, &player2);
            Common_PlaySound(sounds.fall);
            Common_PlayRumble(haptic);
        } else {
            ball_move(&ball, checkFall);
        }

        render_game(ren, ball, player1, player2);

        if (ball.active) {
            ball.active = false;
        }

        if (checkFall == 2) {
            Common_PlaySound(sounds.caught);
            ball.active = true;
        }
        SDL_Delay(100);
    }
    Common_PlayRumble(haptic);
    render_end_game(ren, player1, player2);

    SDL_Delay(5000);
}