// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>
#include <SceneManager.h>

#include "Play.h"

#include "Ball.h"
#include "Dependencies.h"
#include "LevelMaker.h"
#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Defines
// —————————————————————————————————————————————————————————————————————————————————————————————————

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data Types
// —————————————————————————————————————————————————————————————————————————————————————————————————

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static bool isPaused;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PlayEnter(void *args)
{
    PaddleInit();
    BallInit(0);
    LevelCreate();
}

void PlayUpdate(const float dt)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        isPaused = !isPaused;
        PlaySound(*sdFind(PAUSE));
    }

    if (isPaused) { return; }

    PaddleUpdate(dt);
    BallUpdate(dt);

    if (CheckCollisionRecs(BallGetRect(), PaddleGetRect()))
    {
        ball.y = paddle.y + (float)BALL_SIZE;
        ball.dy *= -1;
        PlaySound(*sdFind(PADDLE_HIT));
    }

    LevelCheckBrickCollision();
}

void PlayDraw(void)
{
    PaddleDraw();
    LevelDraw();
    BallDraw();

    if (!isPaused) { return; }

    constexpr float spacing = (float)LARGE_FONT / 10;
    const Vector2 textSize = MeasureTextEx(gFont, "PAUSED", (float)LARGE_FONT, spacing);
    const float textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(gFont, "PAUSED", (Vector2){textX, (float)VIRTUAL_HEIGHT / 2 - 16},
               (float)LARGE_FONT, spacing, WHITE);

}

void PlayExit(void)
{
    LevelUnload();
}
