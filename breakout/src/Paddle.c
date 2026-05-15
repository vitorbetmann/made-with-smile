// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <math.h>

#include "Paddle.h"

#include "Constants.h"
#include "TextureDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// static void PaddleInit(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr int PADDLE_SPEED = 200;
Paddle paddle;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Public
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PaddleInit(void)
{
    paddle.x = (float)VIRTUAL_WIDTH / 2 - 32;
    paddle.y = (float)VIRTUAL_HEIGHT - 32;
    paddle.dx = 0;
    paddle.width = 64;
    paddle.height = 16;
    paddle.size = 2;
    paddle.skin = 1;
}

void PaddleUpdate(const float dt)
{
    if (IsKeyDown(KEY_LEFT))
    {
        paddle.dx = -PADDLE_SPEED;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        paddle.dx = PADDLE_SPEED;
    }
    else
    {
        paddle.dx = 0;
    }

    if (paddle.dx < 0)
    {
        paddle.x = fmaxf(0, paddle.x + paddle.dx * dt);
    }
    else
    {
        paddle.x = fminf(paddle.x + paddle.dx * dt, (float)(VIRTUAL_WIDTH - paddle.width));
    }
}

void PaddleDraw(void)
{
    const Rectangle dest = {paddle.x, paddle.y, (float)paddle.width, (float)paddle.height};
    DrawTexturePro(*tdFind(MAIN), GetPaddleQuad(), dest, (Vector2){0}, 0, WHITE);
}

Rectangle PaddleGetRect(void)
{
    return (Rectangle){paddle.x, paddle.y, (float)paddle.width, (float)paddle.height};
}
