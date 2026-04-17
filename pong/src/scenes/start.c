// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <time.h>
#include <raylib.h>
#include <SceneManager.h>
#include <Log.h>

#include "Ball.h"
#include "Paddle.h"
#include "Settings.h"

#include "Start.h"
#include "Serve.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static bool isInit;
static Player server;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void StartEnter(void *args)
{
    if (!isInit)
    {
        // raylib init
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Pong");
        SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

        SetRandomSeed(time(nullptr));

        SetTargetFPS(60);

        vWindow = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

        font = LoadFont("assets/font.ttf");
        SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
        
        InitAudioDevice();

        paddle_hit = LoadSound("assets/paddle_hit.wav");
        score = LoadSound("assets/score.wav");
        wall_hit = LoadSound("assets/wall_hit.wav");

        isInit = true;
    }

    // paddles
    player1 = (Player){(Paddle){10, 10, false}, 1, 0};
    player2 = (Player){(Paddle){VIRTUAL_WIDTH - PADDLE_WIDTH - 10,
                                VIRTUAL_HEIGHT - PADDLE_HEIGHT - 10, false},
                       2, 0};

    // ball
    StartData *d = args;
    server = d ? d->winner : (Player){0};
    if (server.id != 0)
    {
        server = server.id == 2 ? player1 : player2;
        smSetScene("serve", nullptr);
    }

    ballReset(server);
}

void StartUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        if (!smSceneExists("serve"))
        {
            smCreateScene("serve", ServeEnter, ServeUpdate, ServeDraw, nullptr);
        }

        smSetScene("serve", nullptr);
    }
}

void StartDraw(void)
{
    char *txt = "Welcome to Pong!";
    Vector2 txtSize = MeasureTextEx(font, txt, FONTLARGE, FONTLARGE / FONTRAYLIB);
    Vector2 txtPos = {(VIRTUAL_WIDTH - txtSize.x) / 2, 20};
    DrawTextEx(font, txt, txtPos, FONTLARGE, FONTLARGE / FONTRAYLIB, WHITE);

    txt = "Press ENTER to begin!";
    txtSize = MeasureTextEx(font, txt, FONTSMALL, FONTSMALL / FONTRAYLIB);
    txtPos.x = (VIRTUAL_WIDTH - txtSize.x) / 2;
    txtPos.y = 60;
    DrawTextEx(font, txt, txtPos, FONTSMALL, FONTSMALL / FONTRAYLIB, WHITE);
}
