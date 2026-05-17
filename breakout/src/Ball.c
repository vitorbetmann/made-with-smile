// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Ball.h"

#include "Constants.h"
#include "Paddle.h"
#include "SoundDict.h"
#include "TextureDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data types
// —————————————————————————————————————————————————————————————————————————————————————————————————

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

Ball ball;
const int BALL_SIZE = 8;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void BallInit(const int skin)
{
    BallReset();
    ball.skin = skin;
}

void BallUpdate(const float dt)
{
    ball.x += ball.dx * dt;
    ball.y += ball.dy * dt;

    if (ball.x <= 0)
    {
        ball.x = 0;
        ball.dx *= -1;
        PlaySound(*sdFind(WALL_HIT));
    }

    if (ball.x >= (float)VIRTUAL_WIDTH - 8)
    {
        ball.x = (float)VIRTUAL_WIDTH - 8;
        ball.dx *= -1;
        PlaySound(*sdFind(WALL_HIT));
    }

    if (ball.y <= 0)
    {
        ball.y = 0;
        ball.dy *= -1;
        PlaySound(*sdFind(WALL_HIT));
    }
}

void BallDraw(void)
{
    const Rectangle dest = {ball.x, ball.y, (float)BALL_SIZE, (float)BALL_SIZE};
    DrawTexturePro(*tdFind(MAIN), GetBallQuad(), dest, (Vector2){0}, 0, WHITE);
}

void BallReset(void)
{
    ball.x = paddle.x + (float)(paddle.width - BALL_SIZE) / 2;
    ball.y = paddle.y - (float)BALL_SIZE;

    ball.dx = (float)GetRandomValue(-200, 200);
    ball.dy = (float)GetRandomValue(-60, -50);
}

Rectangle BallGetRect(void)
{
    return (Rectangle){ball.x, ball.y, (float)BALL_SIZE, (float)BALL_SIZE};
}
