// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <raylib.h>
#include <SceneManager.h>

#include "Ball.h"
#include "Paddle.h"
#include "Settings.h"

#include "Start.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Defines
// —————————————————————————————————————————————————————————————————————————————————————————————————

typedef enum
{
    START,
    PLAY,
} State;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static bool displayFPS;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void toggleAI(Paddle *p)
{
    p->isAI = !p->isAI;
}

void update(float dt)
{
    // fps
    if (IsKeyPressed(KEY_T))
    {
        displayFPS = !displayFPS;
    }

    if (IsKeyPressed(KEY_ONE))
    {
        toggleAI(&player1.paddle);
    }

    if (IsKeyPressed(KEY_TWO))
    {
        toggleAI(&player2.paddle);
    }

    // player 1
    if (!player1.paddle.isAI)
    {
        if (IsKeyDown(KEY_W))
        {
            paddleUp(&player1.paddle, dt);
        }
        else if (IsKeyDown(KEY_S))
        {
            paddleDown(&player1.paddle, dt);
        }
    }
    else if (ball.dx < 0)
    {
        paddleAI(&player1.paddle, dt);
    }

    // player 2
    if (!player2.paddle.isAI)
    {
        if (IsKeyDown(KEY_UP))
        {
            paddleUp(&player2.paddle, dt);
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            paddleDown(&player2.paddle, dt);
        }
    }
    else if (ball.dx > 0)
    {
        paddleAI(&player2.paddle, dt);
    }

    smUpdate(dt);
}

void drawVWindow(void)
{
    BeginTextureMode(vWindow);
    ClearBackground(COLORBG);

    // fps
    if (displayFPS)
    {
        DrawFPS(10, 10);
    }

    // score
    char buf[32];
    float spacing = FONTLARGE / FONTRAYLIB;
    snprintf(buf, 32, "%d", player1.score);
    DrawTextEx(font, buf,
               (Vector2){VIRTUAL_WIDTH / 2 - 50, VIRTUAL_HEIGHT / 2 - 40},
               FONTLARGE, spacing, WHITE);
    snprintf(buf, 32, "%d", player2.score);
    DrawTextEx(font, buf,
               (Vector2){VIRTUAL_WIDTH / 2 + 30, VIRTUAL_HEIGHT / 2 - 40},
               FONTLARGE, spacing, WHITE);

    paddleDraw(&player1.paddle);
    paddleDraw(&player2.paddle);
    ballDraw();

    smDraw();

    EndTextureMode();
}

void draw(void)
{
    BeginDrawing();
    drawVWindow();
    DrawTexturePro(vWindow.texture,
                   (Rectangle){0, 0, VIRTUAL_WIDTH, -VIRTUAL_HEIGHT},
                   (Rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGTH},
                   (Vector2){0}, 0, WHITE);
    EndDrawing();
}

void unload(void)
{
    UnloadFont(font);

    UnloadSound(paddle_hit);
    UnloadSound(score);
    UnloadSound(wall_hit);

    CloseAudioDevice();

    CloseWindow();
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Main
// —————————————————————————————————————————————————————————————————————————————————————————————————

int main(void)
{
    smStart();
    smCreateScene("start", StartEnter, StartUpdate, StartDraw, nullptr);
    smSetScene("start", nullptr);

    while (!WindowShouldClose())
    {
        update(GetFrameTime());
        draw();
    }
    unload();
}