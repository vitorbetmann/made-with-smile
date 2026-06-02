// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <SceneManager.h>

#include "Serve.h"

#include "Paddle.h"
#include "Ball.h"
#include "LevelMaker.h"
#include "Play.h"
#include "PowerUp.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

constexpr char PLAY_PROMPT[] = "Press Enter to serve!";

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void ServeEnter(void *args)
{
    PowerUpsInit();

    for (int i = 0; i < 3; i++)
    {
        BallInit(&balls[i], GetRandomValue(0, 6));
    }
    gActiveBalls = 1;

    if (!IsLevelActive()) { LevelCreate(gLevel); }
}

void ServeUpdate(const float dt)
{
    const float paddleLastX = paddle.x;
    PaddleUpdate(dt);
    balls[0].x += paddle.x - paddleLastX;

    if (IsKeyPressed(KEY_ENTER))
    {
        if (!smSceneExists("play"))
        {
            smAddScene("play", nullptr, PlayUpdate, PlayDraw, nullptr);
        }
        smSetScene("play", nullptr);
    }
}

void ServeDraw(void)
{
    PaddleDraw();
    LevelDraw();
    BallDraw(&balls[0]);

    // Draw "Level [number]"
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "Level %d", gLevel);
    Vector2 textSize = MeasureTextEx(gFont, buffer, LARGE_FONT, 0);
    Vector2 textPos = {((float)VIRTUAL_WIDTH - textSize.x) / 2,
                       ((float)VIRTUAL_HEIGHT - textSize.y) / 2 - 30};
    DrawTextEx(gFont, buffer, textPos, LARGE_FONT, 0, WHITE);

    // Draw "Press Enter to Serve"
    textSize = MeasureTextEx(gFont, PLAY_PROMPT, MEDIUM_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = ((float)VIRTUAL_HEIGHT - textSize.y) / 2;
    DrawTextEx(gFont, PLAY_PROMPT, textPos, MEDIUM_FONT, 0, WHITE);
}
